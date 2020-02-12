
/**
 * bst.hxx file
 * @authors: Eros Fabrici, ... , ....
 **/
#include <iostream>
#include <memory>

#ifndef BST_H__
#define BST_H__

#include "node.hxx"
#include "iterator.hxx"

template<class KeyType, class ValueType, class CompareType = std::less<KeyType>>
class bst 
{
    private:
        std::unique_ptr<Node> root;
        CompareType comparator;
    public:
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
            copy(bst.getRoot());
        }
        /**
         * @brief move constructor
         * @param bst Bst to be moved to the new one
         */
        bst(bst&& bst) noexcept : 
            root{std::move(bst.getRoot())} {}

        iterator begin();
        iterator end() { return new Iterator{nullptr}; }
        
            //Iterator iterator;
            //ConstIterator const_iterator;
};

#endif