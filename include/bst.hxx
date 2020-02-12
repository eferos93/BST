<<<<<<< HEAD
=======

>>>>>>> c5ec8309b65ec99687abdc22845f607824f6213e
/**
 * bst.hxx file
 * @authors: Eros Fabrici, ... , ....
 **/
#include <iostream>
#include <memory>

<<<<<<< HEAD
#ifndef BST_H__
#define BST_H__
=======
#ifndef BST_HXX__
#define BST_HXX__
>>>>>>> c5ec8309b65ec99687abdc22845f607824f6213e

#include "node.hxx"
#include "iterator.hxx"

template<class KeyType, class ValueType, class CompareType = std::less<KeyType>>
class bst 
{
    private:
        std::unique_ptr<Node> root;
<<<<<<< HEAD
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
    

=======
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
            //TODO
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
>>>>>>> c5ec8309b65ec99687abdc22845f607824f6213e
};

#endif