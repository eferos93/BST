/**
 * bst.hxx file
 * @authors: Eros Fabrici, Dogan Can Demirbilek , ....
 **/
#include <iostream>
#include <utility>
#include <memory>
#include <vector>

#ifndef BST_HXX__
#define BST_HXX__

template<class KeyType, class ValueType, class CompareType = std::less<KeyType>>
class bst 
{
    private:
        class Node;
        std::unique_ptr<Node> root;
        /**
         * @brief Given a node in a tree, returns its successor
         * @param node A pointer to a node
         * @return Pointer to node's successor
         */
        Node * successor(Node * node);

        /**
         * @brief Given a pointer to a node, find the left_most element in the sub-tree
         * with node as root
         * @param node Pointer to a node
         * @return Pointer to a node which is the left_most element of the sub-tree rooted
         * in node
         */
        Node * left_most(Node * node);


        /**
         * @brief Recursive private method to create deep copy of a binary search tree
         * @param node The root node of the tree that should be copied
         */
        void copy(const std::unique_ptr<Node> &node);

    public:
        CompareType comparator;
        class iterator;
        class const_iterator;

        /**
         * @brief Default constructor
         */
        bst() {}
        
        /**
         * @brief Constructor with node
         * @param data The root of the bst to be created
         * @param c The instance of the CompareType
         */
        bst(std::pair<KeyType, ValueType> data, CompareType c = CompareType{}):
            root{std::make_unique<Node>(data)}, comparator{c} {}

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

        iterator begin() const;
        iterator end() const { return iterator{nullptr}; }

        //const_iterator end() const { return const_iterator{nullptr}; }
        
        const_iterator cbegin() const;

        const_iterator cend() const { return const_iterator(nullptr); }
        /*
        const_iterator begin() const 
        {
            if(!root)
            {
                return const_iterator{nullptr};
            }
            Node * current = root.get();
            while (current->left)
            {
                current = current->left.get();
            }
            
            return const_iterator{current};
        }
        */
                //Methods

        /**
         *  @brief Insert the node of given key
         *  @param data Pair data to be inserted
         *  @return a pair<iterator, bool>
         */
        std::pair<iterator, bool> insert(const std::pair<KeyType, ValueType>& data); 
        std::pair<iterator, bool> insert(std::pair<KeyType, ValueType>&& data);      

        /**
        *  @brief emplace given data to tree specified position
        *  @param args The data to be inserted
        *  @return A pair (iterator, bool)
        */
        template<class... Types>
        std::pair<iterator,bool> emplace(Types&&... args)
        {
            return insert(std::pair<KeyType, ValueType>{std::forward<Types>(args)...});
        }


        /**
         *  @brief Clears all the elements of the tree
         */
        void clear() { root.reset(); }

        /**
         *  @brief Find the node of given key
         *  @param key The key value to be found in bst
         */
        iterator find(const KeyType& key);
        const_iterator find(const KeyType& key) const;

        /**
         * @brief given a key, find the node and delete the node
         * @param key The key of the node to be found and deleted
         */
        void erase(const KeyType& key);

        /**
         * @brief method to get the root of tree
         */
        Node* getRoot() 
        {
            return root.get();
        }

        /**
         *  @brief auxiliary recursive function to build a bst
         *  @param nodes containers of nodes
         *  @param start beginning position
         *  @param end ending position
         */ 
        void buildTree(std::vector<std::pair<KeyType,ValueType>> &nodes, int start, int end);
        
        /**
         * @brief find the height of tree
         * @param node pointer to root node of tree
         */
        int height(Node* node); 

        /**
         * @brief find if tree is balanced
         * @param node pointer to root node of tree
         * @return 1 if tree is balanced, otherwise 0
         */
        bool isBalanced(Node* node);
        
        /**
         *  @brief function that balance the tree
         */ 
        void balance();

        ValueType& operator[](const KeyType& key) noexcept;
        ValueType& operator[](KeyType&& key) noexcept;
};

template <class KeyType, class ValueType, class CompareType>
typename bst<KeyType,ValueType,CompareType>::Node * bst<KeyType,ValueType,CompareType>::successor(Node * node)
{
    if (node->right)
    {
        return left_most(node->right.get());
    }

    Node * p = node->parent;        
    while (p && node == p->right.get())
    {
        node = p;
        p = p->parent;
    }

    return p;
}

template <class KeyType, class ValueType, class CompareType>
typename bst<KeyType,ValueType,CompareType>::Node * bst<KeyType,ValueType,CompareType>::left_most(Node * node)
{
    if (node == root.get())
    {
        return begin().current;
    }
    while (node->left)
    {
        node = node->left.get();
    }
    return node;
}

template <class KeyType, class ValueType, class CompareType>
void bst<KeyType,ValueType,CompareType>::copy(const std::unique_ptr<bst<KeyType,ValueType,CompareType>::Node> &node)
{
    if (node)
    {
        insert(node->data);
        copy(node->left);
        copy(node->right);
    }
}

template <class KeyType, class ValueType, class CompareType>
typename bst<KeyType, ValueType, CompareType>::iterator bst<KeyType, ValueType, CompareType>::begin() const
{
    if(!root)
    {
        return iterator{nullptr};
    }

    Node * current = root.get();
    while (current->left)
    {
        current = current->left.get();
    }
            
    return iterator{current};
}

template <class KeyType, class ValueType, class CompareType>
typename bst<KeyType, ValueType, CompareType>::const_iterator bst<KeyType, ValueType, CompareType>::cbegin() const
{
    if (!root)
    {
        return const_iterator{nullptr};
    }
    Node *current = root.get();
    while (current->left)
    {
        current = current->left.get();
    }

    return const_iterator{current};
}

template <class KeyType, class ValueType, class CompareType>
std::pair<typename bst<KeyType, ValueType, CompareType>::iterator, bool> 
bst<KeyType, ValueType, CompareType>::insert(const std::pair<KeyType, ValueType> &data)
{
    // If tree isn't empty, cur node will be created
    Node *current = root.get();

    while (current)
    {
        if (comparator(data.first, current->data.first))
        {
            if (!current->left)
            {
                current->left = std::make_unique<Node>(
                    data, current);
                iterator it = iterator{current->left.get()};
                return std::pair<iterator, bool>{it, true};
            }

            current = current->left.get();
        }
        else if (comparator(current->data.first, data.first))
        {
            if (!current->right)
            {
                current->right = std::make_unique<Node>(
                    data, current);
                iterator it{current->right.get()};
                return std::pair<iterator, bool>{it, true};
            }

            current = current->right.get();
        }
        else
        {
            //the key already exists in the tree
            iterator it{current};
            return std::pair<iterator, bool>{it, false};
        }
    }

    //current is root and it's nullptr
    root = std::make_unique<Node>(data);
    iterator it{root.get()};
    return std::pair<iterator, bool>{it, true};
}

template <class KeyType, class ValueType, class CompareType>
std::pair<typename bst<KeyType, ValueType, CompareType>::iterator, bool> 
bst<KeyType, ValueType, CompareType>::insert(std::pair<KeyType, ValueType> &&data)
{
    // If tree isn't empty, cur node will be created
    Node *current = root.get();
    using pair_type = std::pair<KeyType, ValueType>;
    while (current)
    {
        if (comparator(data.first, current->data.first))
        {
            if (!current->left)
            {
                current->left = std::make_unique<Node>(
                    std::forward<pair_type>(data), current);
                iterator it = iterator{current->left.get()};
                return std::pair<iterator, bool>{it, true};
            }

            current = current->left.get();
        }
        else if (comparator(current->data.first, data.first))
        {
            if (!current->right)
            {
                current->right = std::make_unique<Node>(
                    std::forward<pair_type>(data), current);
                iterator it{current->right.get()};
                return std::pair<iterator, bool>{it, true};
            }

            current = current->right.get();
        }
        else
        {
            //the key already exists in the tree
            iterator it{current};
            return std::pair<iterator, bool>{it, false};
        }
    }

    //current is root and it's nullptr
    root = std::make_unique<Node>(std::forward<pair_type>(data));
    iterator it{root.get()};
    return std::pair<iterator, bool>{it, true};
}

template <class KeyType, class ValueType, class CompareType>
typename bst<KeyType, ValueType, CompareType>::iterator 
bst<KeyType, ValueType, CompareType>::find(const KeyType &key)
{
    Node *current = root.get();
    // until current equals to null pointer
    while (current)
    {
        // given key is smaller than current go left
        if (comparator(key, current->data.first))
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
    }

    // key does not exist in tree
    return end();
}

template <class KeyType, class ValueType, class CompareType>
typename bst<KeyType, ValueType, CompareType>::const_iterator
bst<KeyType, ValueType, CompareType>::find(const KeyType &key) const
{
    Node *current = root.get();
    // until current equals to null pointer
    while (current)
    {
        // given key is smaller than current go left
        if (comparator(key, current->data.first))
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
    }

    // key does not exist in tree
    return end();
}

template <class KeyType, class ValueType, class CompareType>
void bst<KeyType, ValueType, CompareType>::erase(const KeyType &key)
{
    Node* p = find(key).current;
    if (!p)
    {
        return;
    }

    Node* node;
    Node* subtree_root;

    if (p->left && p->right)
    {
        node = successor(p);
    }
    else
    {
        node = p;
    }

    if (node->left)
    {
        subtree_root = node->left.get();
    }
    else
    {
        subtree_root = node->right.get();
    }

    if (subtree_root)
    {
        subtree_root->parent = node->parent;
    }

    if (!node->parent)
    {
        if (node != p)
        {
            p->data.first = node->data.first;
            p->data.second = node->data.second;
        }
        root.release();
        root.reset(subtree_root);
    }
    else if (node == node->parent->left.get())
    {
        if (node != p)
        {
            p->data.first = node->data.first;
            p->data.second = node->data.second;
        }
        node->parent->left.release();
        node->parent->left.reset(subtree_root);
    }
    else
    {
        if (node != p)
        {
            p->data.first = node->data.first;
            p->data.second = node->data.second;
        }
        node->parent->right.release();
        node->parent->right.reset(subtree_root);
    }
    delete node;
    delete subtree_root;
}

template <class KeyType, class ValueType, class CompareType>
std::ostream &operator<<(std::ostream &os, const bst<KeyType,ValueType,CompareType> &x)
{
    for (auto &node : x)
    {
        os << "(" << node.first << ", " << node.second << ")";
    }
    return os;
}

template <class KeyType, class ValueType, class CompareType>
void bst<KeyType,ValueType,CompareType>::buildTree(std::vector<std::pair<KeyType, ValueType>> &nodes, int start, int end)
{
    if (start > end)
        return;

    if (start == end)
    {
        insert(nodes[start]);
        return;
    }
    // Get the middle element
    int mid = (start + end) / 2;
    insert(nodes[mid]);

    buildTree(nodes, start, mid - 1);
    buildTree(nodes, mid + 1, end);
}

template <class KeyType, class ValueType, class CompareType>
int bst<KeyType, ValueType, CompareType>::height(typename bst<KeyType, ValueType, CompareType>::Node* node)
{
    if (!node)
    {
        return 0;
    }
    return 1 + std::max(height(node->left.get()),
                        height(node->right.get()));
}

template <class KeyType, class ValueType, class CompareType>
bool bst<KeyType,ValueType,CompareType>::isBalanced(typename bst<KeyType, ValueType, CompareType>::Node* node)
{
    if (!node)
    {
        return true;
    }

    int lh, rh;

    lh = height(node->left.get());
    rh = height(node->right.get());

    return abs(lh - rh) <= 1 && isBalanced(node->left.get()) && isBalanced(node->right.get());
    //if(abs(lh-rh) <= 1 && isBalanced(node->left.get()) && isBalanced(node->right.get()))
    //    return true;
    //return false;
}

template <class KeyType, class ValueType, class CompareType>
void bst<KeyType, ValueType, CompareType>::balance()
{
    std::vector<std::pair<KeyType, ValueType>> nodes;

    for (auto it = begin(); it != end(); ++it)
    {
        nodes.push_back(*it);
    }

    clear();

    buildTree(nodes, 0, nodes.size() - 1);
}

template <class KeyType, class ValueType, class CompareType>
ValueType& bst<KeyType,ValueType,CompareType>::operator[](const KeyType &key) noexcept
{
    Node *current = root.get();

    while (current)
    {
        if (comparator(key, current->data.first))
        {
            if (!current->left)
            {
                auto pair = std::pair<KeyType, ValueType>{key, ValueType{}};
                current->left = std::make_unique<Node>(pair, current);
                return current->left->data.second;
            }
            else
            {
                current = current->left.get();
            }
        }
        else if (comparator(current->data.first, key))
        {

            if (!current->right)
            {
                auto pair = std::pair<KeyType, ValueType>{key, ValueType{}};
                current->right = std::make_unique<Node>(pair, current);
                return current->right->data.second;
            }
            else
            {
                current = current->right.get();
            }
        }
        else
        {
            return current->data.second;
        }
    }

    //root is null
    auto pair = std::pair<KeyType, ValueType>{key, ValueType{}};
    root = std::make_unique<Node>(pair, nullptr);
    return root->data.second;
}

template <class KeyType, class ValueType, class CompareType>
ValueType& bst<KeyType,ValueType,CompareType>::operator[](KeyType &&key) noexcept
{
    Node *current = root.get();
    while (current)
    {
        if (comparator(std::forward<KeyType>(key), current->data.first))
        {
            if (!current->left)
            {
                auto pair = std::pair<KeyType, ValueType>{
                    std::forward<KeyType>(key), ValueType{}};
                current->left = std::make_unique<Node>(pair, current);
                return current->left->data.second;
            }
            else
            {
                current = current->left.get();
            }
        }
        else if (comparator(current->data.first, std::forward<KeyType>(key)))
        {

            if (!current->right)
            {
                auto pair = std::pair<KeyType, ValueType>{
                    std::forward<KeyType>(key), ValueType{}};
                current->right = std::make_unique<Node>(pair, current);
                return current->right->data.second;
            }
            else
            {
                current = current->right.get();
            }
        }
        else
        {
            //element found
            return current->data.second;
        }
    }

    //root is null
    auto pair = std::pair<KeyType, ValueType>{std::forward<KeyType>(key), ValueType{}};
    root = std::make_unique<Node>(pair, nullptr);
    return root->data.second;
}

#include "node.hxx"
#include "iterator.hxx"

#endif