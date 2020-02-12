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
    public:
        Iterator iterator;
        ConstIterator const_iterator;

        CompareType compare();

    //Methods

    // given the root and pair data, new node will be created if it doesn't exist in tree
    std::pair<iterator, bool> insert(Node* root,std::pair<const KeyType, ValueType> &data){

        // If there tree is empty, new node will be created and pointer to node and true will be returned
        if (root == nullptr){
            root = new Node(std::pair<const KeyType, ValueType> data);
            return std::pair<iterator,bool> x(root, true);
        }
        // If tree isn't empty, cur node will be created
        else{
            Node* cur;
            // keyValue of data is smaller than root so it goes to left side of tree
            if(compare(data.first,root.getData().first)){                   // data.first < root.getData().first
                insert(root.getLeft(), data);
                root.getLeft() = cur;
            }
            // keyValue of data is larger than root so it goes to rigth side of tree
            else if(!compare(data.first,root.getData().first)){             // data.first > root.getData().first
                insert(root.getRight(), data);
                root.getRight() = cur;
            }
            // Key is already presented in tree
            else{                                                           // data.first == root.getData().first                       
                return std::pair<iterator,bool> x(cur, false); 
            }

            return std::pair<iterator,bool> x(cur, true);       
        }
        
    }
    

};

#endif