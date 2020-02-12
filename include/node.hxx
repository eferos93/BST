
/**
 * node.hxx file
 * @authors: Eros Fabrici, ... , ....
 **/
#include <iostream>
#include <memory>

template<class KeyType, class ValueType, class CompareType = std::less<KeyType>>
class Node 
{   
    private:
        /**
         * tuple containing the key which is an unique identifier for the node
         * and the value
         */
        std::pair<const KeyType, ValueType> data;
        /**
         * pointers to left and right child
         */
        std:unique_ptr<Node> left, right;
        /**
         * pointer to parent node
         */
        Node * parent;
    public:
        /**
         * @brief default constructor
         */ 
        Node() {}
        /**
         * @brief construct a new node given a tuple (key,value)
         * @param data Data to be inserted into the node
         */
        Node(std::pair<KeyType, ValueType> data): 
            data{data}, left{nullptr}, right{nullptr},
            parent{nullptr} {}
        /**
         * @brief construct a new node given a tuple (key,value)
         * and a pointer to parent
         * @param data Data to be inserted inot the node
         * @param parent Pointer to parent node
         */
        Node(std::pair<KeyType, ValueType> data, Node * parent): 
            data{data}, left{nullptr}, right{nullptr},
            parent{parent} {}

        /**
         * @brief construct a new node given a pointer to a node (copy constructor)
         * @param node Reference to the node to be copied
         */
        Node(const Node& node): 
            data{node.getData()}, left{nullptr}, right{nullptr},
            parent{nullptr} {}

        /**
         * @brief getter for data
         */
        std::pair<const KeyType, ValueType> getData() 
        {
            return data;
        }

        /**
         * @brief getter for left child
         */
        std:unique_ptr<Node> getLeft() 
        {
            return left;
        }
        
        /**
         * @brief getter for right child
         */
        std::unique_ptr<Node> getRight() 
        {
            return right;
        }
        /**
         * @brief getter for parent
         */
        Node* getParent() {
            return parent;
        }
};