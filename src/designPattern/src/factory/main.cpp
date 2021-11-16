#include "common.h"

// 场景设计 : 有一个魔法动物园，可以想看什么动物就看到什么动物
// 动物基类
class Animal {
    public:
        Animal(const std::string &str) : name_(str) {}
        virtual ~Animal() {}
        virtual void See() = 0;      // 动物被看
    protected:
        std::string name_;   
};
// 狮子类   
class Lion : public Animal {
    public:
        Lion() : Animal("Lion") {}
        void See() override {
            std::cout<<" i see a "<< name_ <<std::endl;
            std::cout<<"big and strong"<<std::endl;
        }
};
// 狗类
class Dog : public Animal {
    public:
        Dog() : Animal("Dog") {}
        void See() override {
            std::cout<<" i see a "<< name_ <<std::endl;
            std::cout<<"small and cute"<<std::endl;
        }
};
// 动物工厂
class AnimalFactory {
    public:
        virtual ~AnimalFactory() {}
        virtual boost::shared_ptr<Animal> CreateAnimal() = 0;  
};
// 狮子工厂
class LionFactory : public AnimalFactory {
    public:
        boost::shared_ptr<Animal> CreateAnimal() {
            return boost::make_shared<Lion>();  
        }
};
// 狗工厂
class DogFactory : public AnimalFactory {
    public:
        boost::shared_ptr<Animal> CreateAnimal() {
            return boost::make_shared<Dog>();  
        }
};

class Zoo {
    public:
        Zoo() {
            pFactory_ = nullptr;       // 赋值    
            /**
             *  查看 shared_ptr 的源码可以发现，对赋值进行了重载  
             *  shared_ptr & operator=( boost::detail::sp_nullptr_t ) BOOST_SP_NOEXCEPT
                    {
                        this_type().swap(*this);     // boost中 shared_ptr 会将 内部指针 赋值为 0
                        return *this;
                    }
             */
        }
        void WatchAnimal() {
            // 先由工厂生成一个动物
            if(pFactory_ == nullptr) return;       // Boost重载了shared_ptr的比较运算符 ，这里 == 会检查shared_ptr内部指针是否 == 0
            boost::shared_ptr<Animal> pAnimal_ = pFactory_->CreateAnimal();  
            pAnimal_->See();    
        }
        void set_pFactory_(boost::shared_ptr<AnimalFactory> pFactory) {
            pFactory_ = pFactory;  
        }
    private:
        boost::shared_ptr<AnimalFactory> pFactory_;   
};

int main()
{
    Zoo zoo;  
    zoo.WatchAnimal();
    zoo.set_pFactory_(boost::make_shared<LionFactory>());
    zoo.WatchAnimal();
    zoo.set_pFactory_(boost::make_shared<DogFactory>());
    zoo.WatchAnimal();
    return 0; 
}