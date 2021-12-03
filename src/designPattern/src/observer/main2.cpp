
/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2021-11-18 13:33:54
 * @Description: 
 * @Others: 
 */
#ifndef USLAM_VIRTUAL_SENSOR2_H
#define USLAM_VIRTUAL_SENSOR2_H

#include "sensor_base.h"
#include "ulog/ulog.h"
#include "usensor_driver/sensorData.h"
#include "sensor_type/LaserScan.h"
#include <sensor_type/Range.h>

/**
 * @brief:  虚拟驱动原型模板  
 * @details: 
 * @param __sensor_type 该虚拟驱动接收的全部传感器数据类型   
 */
template<typename ... __sensor_type>
class VirtualSensor2 {};  

/**
 * @brief: VirtualSensor2 的特化
 * @details: 
 * @param __sensor_this_type 本虚拟驱动接收传感器数据的型别   
 * @param __sensor_other_type 剩余其他传感器型别  
 */
template<typename __sensor_this_type, typename ... __sensor_other_type>
class VirtualSensor2<__sensor_this_type, __sensor_other_type ...> : public VirtualSensor2<__sensor_other_type ...>
{
public:
    virtual ~VirtualSensor2() {}

    /**
     * @brief 传入引起回调的数据
     * @details 实际上这里面完成的是信息通知的作用
     * @param input 
     * @return void
     */    
    virtual void registerDataInput(const boost::shared_ptr<__sensor_this_type> &input) = 0;

}; // class VirtualSensor2<__sensor_this_type, __sensor_other_type ...>


/**
 * @brief: VirtualSensor2 的特化
 * @details: 
 * @param __sensor_this_type 本虚拟驱动接收传感器数据的型别   
 */
template<typename __sensor_this_type>
class VirtualSensor2<__sensor_this_type> : public SensorBase 
{
public:
    VirtualSensor2() : SensorBase("") {}
    virtual ~VirtualSensor2() {}

    /**
     * @brief 传入引起回调的数据
     * @details 实际上这里面完成的是信息通知的作用
     * @param input 
     * @return 
     */    
    virtual void registerDataInput(const boost::shared_ptr<__sensor_this_type> &input) = 0;

protected:
    std::atomic<bool> enabled_;
}; // class VirtualSensor2<__sensor_this_type>

#endif  // USLAM_VIRTUAL_SENSOR_H


/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2021-11-18 16:37:01
 * @Description: 
 * @Others: 
 */

#ifndef SENSOR_BASE_H
#define SENSOR_BASE_H

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <unordered_map>
#include <atomic>
#include "callback_base.h"

typedef CallbackBase::CallbackHandler CallbackHandler;

/**
 * @brief Wrap the boost::shared_ptr<DataType> into void* , this is for another use, more details in example/demo_another_use.cpp
 * @tparam DataType
 * @param data[in]
 * @return data[out] ouput data, type is void*
 */
template <class DataType>
void *wrapData(const boost::shared_ptr<DataType> &data)
{
    return static_cast<void *>(data.get());
}

/**
 * @brief:  
 * @details:  主要负责传感器驱动的初始化，启动和停止
 *                        回调函数的注册以及调用     
 */
class SensorBase
{
public:
    SensorBase(const std::string &name = "") : name_(name) {}
    virtual ~SensorBase() = default;

    /**
     * @brief The api to start the driver.
     */
    virtual bool start() = 0;

    /**
     * @brief The api to stop the driver.
     */
    virtual bool stop() = 0;

    /**
     * @brief The api to do some init.
     * @param config[in] The path of the config file.
     */
    virtual bool init(const std::string &config = "") = 0;

public:
    // define the function pointer
    typedef void (SensorBase::*emitVoid)(void *, const std::string &);
    // this is for the another use, more details in example/demo_another_use.cpp
    emitVoid emitVoidFunc = &SensorBase::emit;

    /**
     * @brief The api for another task to register its callback into this driver.
     * @tparam T dataType
     * @param topic[in] we search the topic in std::unordered_map, if not foud, just create one, else we just connect the callback.
     * @param callback[in] the callback from another task.
     * @return std::unique_ptr<CallbackHandler> return the callbackHandler to control this connection.
     */
    template <class T>
    std::unique_ptr<CallbackHandler> registerCallback(const boost::function<void(const boost::shared_ptr<T> &)> &callback,
                                                      const std::string &topic = "")
    {
        std::lock_guard<std::mutex> lock(callback_table_mutex_);
        auto it = callback_table_.find(topic);
        if (it != callback_table_.end()) {
            // 数据类型 与 回调函数类型检查
            if (typeid(T) != it->second->getType()) {
                printf("The Callback Data type (%s) wrong, need (%s)", typeid(T).name(), it->second->getType().name());
                return nullptr;
            }
            std::shared_ptr<CallbackBuffer<T>> ptr = std::dynamic_pointer_cast<CallbackBuffer<T>>(it->second);
            return ptr->connect(callback);  //返回句柄
        } else {
            printf("Topic [%s] Not Existed! \n", topic.c_str());
            createPipe(std::make_pair(topic, T()));
            std::shared_ptr<CallbackBuffer<T>> ptr = std::dynamic_pointer_cast<CallbackBuffer<T>>(callback_table_[topic]);
            return ptr->connect(callback);
        }
    }

protected:
    /**
     * @brief When the HardDriver data comes, just trigger this with the data, then excute the callback we registered.
     * @tparam T dataType
     * @param topic[in] the data belong to, in other words, send the data to the topic.
     * @param data[in] the data from HardDriver.
     */
    template <class T>
    void emit(const boost::shared_ptr<T> &data, const std::string &topic = "")
    {
        std::lock_guard<std::mutex> lock(callback_table_mutex_);
        auto it = callback_table_.find(topic);
        if (it != callback_table_.end()) {
            // 数据类型 与 回调函数类型检查
            //            if(typeid (T) != it->second->getType()){
            //                printf("Data[in] type (%s) wrong, need (%s)",typeid
            //                (T).name(),it->second->getType().name()); return;
            //            }

            // 将回调转换成指定类型
            std::shared_ptr<CallbackBuffer<T>> ptr = std::dynamic_pointer_cast<CallbackBuffer<T>>(it->second);
            ptr->emit(data);
        } else {
            printf("Topic [%s] Not Existed! \n", topic.c_str());
        }
    }

    /**
     * @brief This is for the another use, more details in example/demo_another_use.cpp
     * @param topic
     * @param data
     */
    void emit(void *data, const std::string &topic = "")
    {
        std::lock_guard<std::mutex> lock(callback_table_mutex_);
        auto it = callback_table_.find(topic);
        if (it != callback_table_.end()) {
            it->second->emit(data);
        } else {
            printf("Topic [%s] Not Existed! \n", topic.c_str());
        }
    }

private:
    /**
     * @breif Create the key and value mapping into std::unordered_map.
     * @tparam T std::pair of <std::string, std::shared_ptr<CallbackBase>>
     * @param last
     */
    template <class T>
    void createPipe(T last)
    {
        createPipeImpl(last);
    }

    /**
     * @brief Create the key and value mapping into std::unordered_map.
     * @tparam T std::pair of <std::string, std::shared_ptr<CallbackBase>>
     * @tparam Args
     * @param first
     * @param rest
     */
    template <class T, class... Args>
    void createPipe(T first, Args... rest)
    {
        createPipeImpl(first);
        createPipe(rest...);
    }

    /**
     * @brief std::pair of <std::string, std::shared_ptr<CallbackBase>>
     * @tparam T std::pair of <std::string, std::shared_ptr<CallbackBase>>
     * @param input
     */
    template <class T>
    void createPipeImpl(T input)
    {
        auto it = callback_table_.find(input.first);
        if (it == callback_table_.end()) {
            std::shared_ptr<CallbackBase> ptr = std::make_shared<CallbackBuffer<decltype(input.second)>>();
            callback_table_[input.first] = std::move(ptr);
            printf("Create topic [%s], type[%s]\n", input.first.c_str(), typeid(decltype(input.second)).name());
        } else {
            printf("The topic [%s] is existed.", input.first.c_str());
        }
    }

private:
    const std::string name_;                                                         ///< sensor name
    std::mutex callback_table_mutex_;                                                ///< mutex for callback_table_
    std::unordered_map<std::string, std::shared_ptr<CallbackBase>> callback_table_;  ///< callback table
};

#endif