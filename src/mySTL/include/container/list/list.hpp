#pragma once

#include "common.hpp"
#include "../memory.hpp"
#include <assert.h>

namespace mySTL {

/**
 * @brief: list - 链表容器
 * @details:  双向链表
 */
template<typename _ValueType, typename A = Allocator<_ValueType>>
class list {
    public:
        struct Node;
        using NodePtr = Node*; 
        // 链表节点  
        struct Node {
            _ValueType value_;
            NodePtr next_;
            NodePtr prev_;  
        };
        
        struct Acc {
            using pNodeRef = NodePtr&; 
            using vRef = _ValueType&; 
            static pNodeRef Next(pNodeRef p) {
                return (*p).next_;
            }
            static pNodeRef Prev(pNodeRef p) {
                return (*p).prev_;
            }
            static vRef Value(pNodeRef p) {
                return (*p).value_;
            }
        };

        using size_type                        = size_t; 
        using value_type                     = _ValueType;
        using pointer_type                 = _ValueType*;
        using const_pointer_type    = const _ValueType*;
        using reference                        = _ValueType&;
        using const_reference           = const _ValueType&;
        using difference_type            = int;  
        // 迭代器 
        class iterator;
        class const_iterator; 

        class const_iterator {
            // 功能 1、* 2、比较  3、++     4、取值
            public:
                const_iterator() {}
                const_iterator(NodePtr p) : ptr_(p) {}
                const_iterator(iterator const& it) : ptr_(it.MyNode()) {}
                const_iterator(const_iterator const& it) : ptr_(it.ptr_) {}

                const_reference operator*() const {
                    return Acc::Value(ptr_);
                }
                // ++it
                const_iterator operator++() {
                    ptr_ = Acc::Next(ptr_);
                    return *this;
                }
                // it++
                const_iterator operator++(int) {
                    const_iterator tmp = *this; 
                    ++(*this);   // 调用前++
                    return tmp;
                }
                // --it
                const_iterator operator--() {
                    ptr_ = Acc::Prev(ptr_);
                    return *this;
                }
                // it--
                const_iterator operator--(int) {
                    const_iterator tmp = *this; 
                    --(*this);   // 调用前++
                    return tmp;
                }

                bool operator == (const_iterator const& it) const {
                    return ptr_ == it.ptr_; 
                }

                bool operator != (const_iterator const& it) const {
                    return !(*this == it);
                }

            protected:
                NodePtr ptr_;   // 其实就是封装了一个指针
        };

        /**
         * @brief: 迭代器 就是对 指针的封装   
         * @details: 
         * @return {*}
         */        
        class iterator {
            public:
                iterator() {}
                iterator(NodePtr p) : ptr_(p) {}
                iterator(iterator const& it) : ptr_(it.ptr_) {}

                reference operator*() {
                    return Acc::Value(ptr_);
                }

                // ++it
                iterator operator++() {
                    ptr_ = Acc::Next(ptr_);
                    return *this;
                }
                // it++
                iterator operator++(int) {
                    iterator tmp = *this; 
                    ++(*this);   // 调用前++
                    return tmp;
                }
                // --it
                iterator operator--() {
                    ptr_ = Acc::Prev(ptr_);
                    return *this;
                }
                // it--
                iterator operator--(int) {
                    iterator tmp = *this; 
                    --(*this);   // 调用前++
                    return tmp;
                }

                bool operator == (iterator const& it) const {
                    return ptr_ == it.ptr_; 
                }

                bool operator != (iterator const& it) const {
                    return !(*this == it);
                }

                NodePtr MyNode() const {
                    return ptr_; 
                }

             protected:
                NodePtr ptr_;   // 其实就是封装了一个指针
        };
        
        list() : Head_(BuyNode()) {
        }

        iterator begin() {
            return iterator(Acc::Next(Head_));
        }

        // end
        iterator end() {
            return iterator(Head_);    // 尾的下一个即是头指针
        }

        size_type size() const {
            return size_;
        }

        bool empty() {
            return size_ == 0; 
        }

        reference front() {
            return *begin();
        }

        reference back() {
            return *Acc::Prev(Head_);
        }

        void push_back(_ValueType const& v) {
            NodePtr s = BuyNode(Head_, Acc::Prev(Head_));  // (后继，前驱)
            s->value_ = v;
            Acc::Next(Acc::Prev(Head_)) = s; // 尾的后继指向s 
            Acc::Prev(Head_) = s; // 头的前继指向s 
            size_++; 
        }

        void push_front(_ValueType const& v) {
            insert(begin(), v);
        }

        void pop_back() {
            erase(--end());
        }
        
        void pop_front() {
            erase(begin());
        }
        
        // 将value插入到 迭代器的前面一个
        iterator insert(iterator p, const _ValueType &value = _ValueType()) {
            NodePtr curr_node = p.MyNode(); 
            Acc::Prev(curr_node) = BuyNode(curr_node, Acc::Prev(curr_node));
            curr_node = Acc::Prev(curr_node);
            Acc::Next(Acc::Prev(curr_node)) = curr_node;
            Acc::Value(curr_node) = value;
            size_++;
            return iterator(curr_node);
        }

        // 删除 ptr ,并返回ptr的下一个迭代器  
        iterator erase(iterator ptr) {
            NodePtr curr_ptr = (ptr++).MyNode();     // 返回的是ptr加1前的节点，但是ptr自身会++
            Acc::Next(Acc::Prev(curr_ptr)) = Acc::Next(curr_ptr);
            Acc::Prev(Acc::Next(curr_ptr)) = Acc::Prev(curr_ptr);
            --size_; 
            free(curr_ptr);
            return ptr;  
        }

    protected:
        // 生成一个node 
        // Narg 后继参数
        // Parg 前向参数 
        NodePtr BuyNode(NodePtr Narg = nullptr, NodePtr Parg = nullptr) {
            NodePtr node = (NodePtr)malloc(sizeof(Node));  
            assert(node != NULL);
            Acc::Next(node) = (Narg != nullptr) ? Narg : node;
            Acc::Prev(node) = (Parg != nullptr) ? Parg : node; 
            return node;  
        }

    private:
        A allocator_;
        NodePtr Head_;    // 头指针
        size_type size_;  
};  // class list
}
