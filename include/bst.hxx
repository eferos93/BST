/**
 * bst.hxx file
 * @authors: Eros Fabrici, ... , ....
 **/
#include <iostream>
#include <memory>

#ifndef BST_HXX__
#define BST_HXX__

template<class KeyType, class ValueType, class CompareType = std::less<KeyType>>
class bst 
{
    private:
        class Node;
        std::unique_ptr<Node> root;
    public:

        //Methods

        /**
         *  @brief Insert the node of given key
         *  @param data Pair data to be inserted
         *  @return a pair<iterator, bool>
         */ 

        // given the root and pair data, new node will be created if it doesn't exist in tree
        std::pair<iterator, bool> insert(const std::pair<const KeyType, ValueType>& data){
            // If tree isn't empty, cur node will be created
            Node * current = root.get();
            
            while(current)
            {
                if (comparator(data.first, current->data.first))
                {
                    if (!current->left)
                    {
                        current->left.reset(
                            new Node{data, current}
                        );
                        iterator it = new iterator{current->left.get()};
                        return new std::pair<iterator, bool>{it, true};
                    }
                    
                    current = current->left.get();
                }
                else if (comparator(current->data.first, data.first)) 
                {
                    if(!current->right)
                    {
                        current->right.reset(
                            new Node{data, current}
                        );
                        iterator it{current->right.get()};
                        return new std::pair<iterator, bool>{it, true};
                    }
                    
                    current = current->right.get();
                } else {
                    //the key already exists in the tree
                    iterator it{current};
                    return std::pair<iterator, bool>{it, false};
                }
            }
            
            //current is root and it's nullptr
            current = new Node{data};
            iterator it{current};
            return std::pair<iterator, bool>{it, true};
        }      

        /**
        *  @brief emplace given data to tree specified position
        *  @param it Iterator which shows the place that data will be inserted
        *  @param data data will be inserted
        */
        std::pair<iterator,bool> emplace(iterator it,std::pair<const KeyType, ValueType> &data){

            //TO DO
            insert(it, data);
        /*  for emplacing data to tree, we specify the place (by using iterators) and data to be put os it is a inserting operation, 
            if we give the parameters to the insert should it work? Becuase it is a pointer to node (in insert it will be considered as root)
        */
        /*
        	I could not figure out what will happen if I tried to insert a data which doesn't follow the bst logic
        */
        }

        /**
         *  @brief Clears all the elements of the tree
         */
        void clear(); {root.reset();}

        /**
         *  @brief Find the node of given key
         *  @param key The key value to be found in bst
         */
        iterator find(const KeyType& key){
            Node * current = root.get();
            // until current equals to null pointer
            while (current){
                // given key is smaller than current go left
                if(comparator(key, current->data.first))
                {
                    current = current->left.get();
                }
                else if (comparator(current->data.first, key))
                {
                    current = current->right.get();
                }
                else
                {
                    // it is equal return current one
                    return iterator{current};
                }
                // key does not exist in tree
                return end();
            }
        }


    

        CompareType comparator;
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
};

#include "node.hxx"
#include "iterator.hxx"

#endif
