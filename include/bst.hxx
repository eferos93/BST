
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
};

#endif