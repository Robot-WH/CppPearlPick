
#include "common.h"

// 观察者模式   场景设计： 十字路口，汽车、自行车以及行人在观察红绿灯，并根据红绿灯的变化作出不同的反映
// 即汽车、自行车、行人作为观察者 "订阅"  红绿灯的消息 

// 观察者 
template<typename _T>     // 观测的信息类型为模板参数  
class Observer {
    public:
        virtual ~Observer() {}
        virtual void Updata(_T const& message) = 0;      // 观测到信息后的反应
}; // class Observer
// 被观测的信息
template<typename _T>    // 信息类型为模板参数 
class message {
    public:
        message() {
            // std::cout<<"message construct! "<<std::endl;
        }
        virtual ~message() {}
        // 将观察者与该message绑定
        void Attach(boost::shared_ptr<Observer<_T>>  observer) {
            observers_.push_back(observer);  
        }
        // 将观察者与该message解邦
        void detach() {

        }
        // 消息发布
        void Notity(_T const& message) {
            for (auto& it : observers_) {
                it->Updata(message);   
            }
        } 
    private:
        std::vector<boost::shared_ptr<Observer<_T>>> observers_;  
}; // class message
// 红绿灯信号
class TrafficLightMessage : public message<bool> {
    public:
        TrafficLightMessage() {
            // std::cout<<"TrafficLightMessage construct! "<<std::endl;
        }
        bool GetStates() const {
            return states_;
        }
        void SetState(bool const& states) {
            states_ = states; 
            // 通知观察者
            Notity(states);   
        }
    private:
        bool states_;                               // 状态  红灯/绿灯  
}; // class TrafficLightMessage

// 行人观察者  
class WalkerObserver : public Observer<bool> {
    public: 
        /**
         * @brief: 
         * @details: 
         * @param {bool const&} trafficLight
         * @return {*}
         */        
        void Updata(bool const& trafficLight) override {
            if(trafficLight == 1) {
                std::cout<<"red walker stop!!"<<std::endl;
            } else {
                std::cout<<"green walker go!!"<<std::endl;
            }
        }
}; // class WalkerObserver
// 车观察者  
class CarObserver : public Observer<bool> {
    public:
        void Updata(bool const& trafficLight) override {
            if(trafficLight == 1) {
                std::cout<<"red car go!!"<<std::endl;
            } else {
                std::cout<<"green car stop!!"<<std::endl;
            }
        }
}; // class CarObserver

int main()
{
    TrafficLightMessage traffic_light;
    boost::shared_ptr<WalkerObserver> w_o = boost::make_shared<WalkerObserver>();
    boost::shared_ptr<CarObserver> c_o = boost::make_shared<CarObserver>();
    traffic_light.Attach(w_o);  
    traffic_light.Attach(c_o);  
    traffic_light.SetState(1);
    traffic_light.SetState(0);

    return 0; 
}