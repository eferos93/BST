
/**
 * bst.hxx file
 * @authors: Eros Fabrici, ... , ....
 **/
#include <iostream>
#include <utility>
#include <memory>

#ifndef BST_HXX__
#define BST_HXX__

template<class KeyType, class ValueType, class CompareType = std::less<KeyType>>
class bst 
{
    private:
        class Node;
        std::unique_ptr<Node> root;
        CompareType comparator;
    public:
        class __iterator;
        using iterator = __iterator<Node>
        using const_iterator = __iterator<const Node>
        /**
         * @brief Default constructor
         */
        bst() {}
        
        /**
         * @brief Constructor with node
         * @param data The root of the bst to be created
         * @param c The instance of the CompareType
         */
        bst(std::pair<KeyType, ValueType>& data, CompareType c = CompareType{}):
                root{new Node{data}}, comparator{c} {}
        
        /**
         * @brief copy constructor
         * @param bst A reference to another bst
         */
        bst(const bst& bst)
        {    
            copy(bst.root);
        }
        /**
         * @brief move constructor
         * @param bst Bst to be moved to the new one
         */
        bst(bst&& bst) noexcept : 
            root{std::move(bst.root)} {}

        iterator begin()
        {
            if(!root)
            {
                return new iterator{nullptr};
            }

            Node * temp = root.get();
            while (temp->left)
            {
                temp = temp->left.get();
            }
            
            return new iterator{temp};
        }

        iterator end() { return new iterator{nullptr}; }

        const_iterator end() { return new const_iterator{nullptr}; }

        const_iterator cbegin() const
        {
            if(!root)
            {
                return new const_iterator{nullptr};
            }
            Node * temp = root.get();
            while (temp->left)
            {
                temp = temp->left.get();
            }
            
            return new const_iterator{temp};
        }

        const_iterator cend() const { return new const_iterator(nullptr); }

        const_iterator begin() const 
        {
            if(!root)
            {
                return new const_iterator{nullptr};
            }
            Node * temp = root.get();
            while (temp->left)
            {
                temp = temp->left.get();
            }
            
            return new const_iterator{temp};
        }
        
        void copy(const std::unique_ptr<Node> node)
        {
            if (node)
            {
                insert(node->data);
                copy(node->left);
                copy(node->right);
            }
        }

        ValueType& operator[](const KeyType& key) noexcept
        {
            Node * temp = root.get();
            while (temp)
            {
                if (comparator(key, temp->data.first))
                {
                    if (!temp->left)
                    {
                        auto pair = new std::pair<KeyType, ValueType>{key, new ValueType{}};
                        temp->left = new Node<KeyType,ValueType,CompareType>{pair, temp};
                        return temp->left.get()->data.right;
                    }
                    else
                    {
                        temp = temp->left.get();
                    }
                } 
                else if(comparator(temp->data.first, key))
                {
                    
                    if (!temp->right)
                    {
                        auto pair = new std::pair<KeyType, ValueType>{key, new ValueType{}};
                        temp->right = new Node<KeyType,ValueType,CompareType>{pair, temp};
                        return temp->right.get()->data.right;
                    }
                    else
                    {
                        temp = temp->right.get();
                    }
                    
                }
                else
                {
                     return temp->data.right;
                }
                
            }
            
        }

        ValueType& operator[](KeyType&& key) noexcept
        {
            Node * temp = root.get();
            while (temp)
            {
                if (comparator(std::forward(key), temp->data.first))
                {
                    if (!temp->left)
                    {
                        auto pair = new std::pair<KeyType, ValueType>{std::forward(key), ValueType{}};
                        temp->left = new Node<KeyType,ValueType,CompareType>{pair, temp};
                        return temp->left.get()->data.right;
                    }
                    else
                    {
                        temp = temp->left.get();
                    }
                } 
                else if(comparator(temp->data.first, std::forward(key)))
                {
                    
                    if (!temp->right)
                    {
                        auto pair = new std::pair<KeyType, ValueType>{std::forward(key), ValueType{}};
                        temp->right = new Node<KeyType,ValueType,CompareType>{pair, temp};
                        return temp->right.get()->data.right;
                    }
                    else
                    {
                        temp = temp->right.get();
                    }
                    
                }
                else
                {
                     return temp->data.right;
                }
                
            }
            
        }

        friend std::ostream& operator<<(std::ostream& os, const bst& x)
        {
            iterator temp = begin();
            iterator end = end();
            while (temp!=end)
            {
                os << (*temp).right << " "
                ++temp;
            }
            return os;
        }
};

#include "node.hxx"
#include "iterator.hxx"

#endif