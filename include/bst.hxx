/**
 * bst.hxx file
 * @authors: Eros Fabrici, Dogan Can Demirbilek , ....
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

        /**
         * @brief Given a node in a tree, returns its successor
         * @param node A pointer to a node
         * @return Pointer to node's successor
         */
        Node * successor(Node * node)
        {
            if (node->right)
            {
                return minimun(node->right.get());
            }

            Node * p = node->parent;
            
            while (p && node == p->right.get())
            {
                node = p;
                p = p->parent;
            }

            return p;
        }

        /**
         * @brief Given a pointer to a node, find the minimum in the sub-tree
         * with node as root
         * @param node Pointer to a node
         * @return Pointer to a node which is the minimum of the sub-tree rooted
         * in node
         */
        Node * minimun(Node * node)
        {
            if (node == root.get())
            {
                return begin
            }
            while (node)
            {
                node = node->left.get();
            }
            return node;
        }

        /**
         * @brief Replaces the subtree rooted at node a, with the subtree rooted
         * at node b
         * @param a A pointer to a Node
         * @param b A pointer to a Node
         */
        void transplant(Node * a, Node * b)
        {
            if (!u->parent)
            {
                root.reset(b);
            }
            else if (a == a->parent->left.get())
            {
                a->parent->left.reset(b);
            }
            else
            {
                a->parent->right.reset(b);
            }

            if (b)
            {
                v->parent = u->parent;
            }
        }

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

            Node * current = root.get();
            while (current->left)
            {
                current = current->left.get();
            }
            
            return new iterator{current};
        }

        iterator end() { return new iterator{nullptr}; }

        const_iterator end() { return new const_iterator{nullptr}; }

        const_iterator cbegin() const
        {
            if(!root)
            {
                return new const_iterator{nullptr};
            }
            Node * current = root.get();
            while (current->left)
            {
                current = current->left.get();
            }
            
            return new const_iterator{current};
        }

        const_iterator cend() const { return new const_iterator(nullptr); }

        const_iterator begin() const 
        {
            if(!root)
            {
                return new const_iterator{nullptr};
            }
            Node * current = root.get();
            while (current->left)
            {
                current = current->left.get();
            }
            
            return new const_iterator{current};
        }
        
                //Methods

        /**
         *  @brief Insert the node of given key
         *  @param data Pair data to be inserted
         *  @return a pair<iterator, bool>
         */ 

        std::pair<iterator, bool> insert(const std::pair<const KeyType, ValueType>& data){
            // If tree isn't empty, cur node will be created
            Node * current = root.get();
            
            while(current)
            {
                if (comparator(data.first, current->data.first))
                {
                    if (!current->left)
                    {
                        current->left = std::make_unique<Node>(
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
                        current->right = std::make_unique<Node>(
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

        std::pair<iterator, bool> insert(std::pair<const KeyType, ValueType>&& data)
        {
            // If tree isn't empty, cur node will be created
            Node * current = root.get();
            using pair_type = std::pair<const KeyType, ValueType>;
            while(current)
            {
                if (comparator(data.first, current->data.first))
                {
                    if (!current->left)
                    {
                        current->left = std::make_unique<Node>(
                            new Node{std::forward<pair_type>(data), current}
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
                        current->right = std::make_unique<Node>(
                            new Node{std::forward<pair_type>(data), current}
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
            current = new Node{std::forward<pair_type>(data)};
            iterator it{current};
            return std::pair<iterator, bool>{it, true};
        }      

        /**
        *  @brief emplace given data to tree specified position
        *  @param args The data to be inserted
        *  @return A pair (iterator, bool)
        */
        template<class... Types>
        std::pair<iterator,bool> emplace(Types&&... args)
        {
            return insert(std::pair<const KeyType, ValueType>{std::forward<Types>(args)...});
        }


        /**
         *  @brief Clears all the elements of the tree
         */
        void clear(); { root.reset(); }

        /**
         *  @brief Find the node of given key
         *  @param key The key value to be found in bst
         */
        iterator find(const KeyType& key){
            Node * current = root.get();
            // until current equals to null pointer
            while(current)
            {
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

        const_iterator find(const KeyType& key) const
        {
            Node * current = root.get();
            // until current equals to null pointer
            while(current)
            {
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
                    return const_iterator{current};
                }
                // key does not exist in tree
                return end();
            }
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

        /**
         * @brief given a key, find the node and delete the node
         * @param key The key of the node to be found and deleted
         */
        void erase(const KeyType& key)
        {
            Node * node = find(key).current;
            if (!node->left)
            {
                transplant(node, node->right.get());
            }
            else if (!node->right)
            {
                transplant(node, node->left.get());
            }
            else
            {
                Node * temp = minimum(node->right.get());
                if (temp->parent != node)
                {
                    transplant(temp, temp->right.get());
                    temp->right.reset(node->right.get());
                    temp->right->parent = temp;
                }
                transplant(node, temp);
                temp->left.reset(node->left.get());
                temp->left->parent = temp;
            }
            
        }
        /**
         *  @brief auxiliary recursive function to store nodes
         *  @param nodes vector to store the nodes
         */ 

        void storeBSTNodes(Node* root,std::vector<Node*> &nodes){
            // Base case
            if (root)
            {
                return;
            }
            // Store node inorder
            storeBSTNodes(root->left, nodes);
            nodes.push_back(root);
            storeBSTNodes(root-right, nodes);
            
        }

        /**
         *  @brief auxiliary recursive function to build a bst
         *  @param nodes containers of nodes
         *  @param start beginning position
         *  @param end ending position
         */ 

        void buildTree(std::vector<Node*> &nodes, int start, int end){
            if(start>end)
                return;
            // Get the middle element
            int mid = (start + end) / 2;
            Node *root = nodes[mid];
            
            root->left = buildTree(nodes,start,mid-1);
            root->right = buildTree(nodes, mid+1, end);

            return root;

        }

        /**
         *  @brief 
         */ 

        void balance(){
            std::vector<Node *> nodes;
            storeBSTNodes(root,nodes);

            //Construct BST from nodes
            int n = nodes.size();
            buildTree(nodes,0,n-1);

        }

        ValueType& operator[](const KeyType& key) noexcept
        {
            Node * current = root.get();

            while (current)
            {
                if (comparator(key, current->data.first))
                {
                    if (!current->left)
                    {
                        auto pair = new std::pair<KeyType, ValueType>{key, new ValueType{}};
                        current->left = new Node<KeyType,ValueType,CompareType>{pair, current};
                        return current->left.get()->data.right;
                    }
                    else
                    {
                        current = current->left.get();
                    }
                } 
                else if(comparator(current->data.first, key))
                {
                    
                    if (!current->right)
                    {
                        auto pair = new std::pair<KeyType, ValueType>{key, new ValueType{}};
                        current->right = new Node<KeyType,ValueType,CompareType>{pair, current};
                        return current->right.get()->data.right;
                    }
                    else
                    {
                        current = current->right.get();
                    }
                    
                }
                else
                {
                     return current->data.right;
                }
                
            }
            
        }

        ValueType& operator[](KeyType&& key) noexcept
        {
            Node * current = root.get();
            while (current)
            {
                if (comparator(std::forward<KeyType>(key), current->data.first))
                {
                    if (!current->left)
                    {
                        auto pair = new std::pair<KeyType, ValueType>{
                            std::forward<KeyType>(key), ValueType{}
                        };
                        current->left = std::make_unique<Node>(new Node{pair, current});
                        return current->left.get()->data.right;
                    }
                    else
                    {
                        current = current->left.get();
                    }
                } 
                else if(comparator(current->data.first, std::forward<KeyType>(key)))
                {
                    
                    if (!current->right)
                    {
                        auto pair = new std::pair<KeyType, ValueType>{
                            std::forward<KeyType>(key), ValueType{}
                        };
                        current->right = std::make_unique<Node>(new Node{pair, current});
                        return current->right.get()->data.right;
                    }
                    else
                    {
                        current = current->right.get();
                    }
                    
                }
                else
                {
                    //element found
                     return current->data.right;
                }
                
            }
            
        }

        friend std::ostream& operator<<(std::ostream& os, const bst& x)
        {
            iterator current = begin();
            iterator end = end();
            while (current!=end)
            {
                os << (*current).right << " "
                ++current;
            }
            return os;
        }
};

#include "node.hxx"
#include "iterator.hxx"

#endif
