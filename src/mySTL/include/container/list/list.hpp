/*
 * @Copyright(C): Your Company
 * @FileName: 文件名
 * @Author: 作者
 * @Version: 版本
 * @Date: 2022-01-16 17:34:26
 * @Description: 
 * @Others: 
 */
#pragma once

#include "common.hpp"
#include <assert.h>
namespace mySTL {

/**
 * @brief: list - 链表容器
 * @details:  双向链表
 */
template<typename _ValueType>
class list {
    public:
        struct Node;
        using NodePtr = Node*; 
        // 链表节点  
        struct Node
        {
            _ValueType value_;
            NodePtr next_;
            NodePtr prev_;  
        };
        using size_type                        = size_t; 
        using value_type                     = _ValueType;
        using pointer_type                 = _ValueType*;
        using const_pointer_type    = const _ValueType*;
        using reference                        = _ValueType&;
        using const_reference           = const _ValueType&;
        using difference_type            = int;  
        
    private:
        NodePtr Head_;    // 头指针
        size_type size_;  
    public:
        list() : Head_(BuyNode())
        {
        }

        void push_back();
        void push_front();
        void pop_back();
        void pop_front();  
    protected:
        // 生成一个node 
        // Narg 后继参数
        // Parg 前向参数 
        NodePtr BuyNode(NodePtr Narg = nullptr, NodePtr Parg = nullptr)
        {
            NodePtr node = new Node();  
            assert(node != NULL);
            node->next_ = (Narg != nullptr) ? Narg : node;
            node->prev_ = (Parg != nullptr) ? Parg : node; 
            return node;  
        }
};  // class list



}
