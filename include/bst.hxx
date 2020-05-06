/**
 * bst.hxx file
 * @author: Eros Fabrici
 * @author: Dogan Can Demirbilek
 * @author: Alessandro Scardoni
 **/
#include <iostream>
#include <utility>
#include <memory>
#include <vector>


#ifndef BST_HXX__
#define BST_HXX__

//pre-declaration needed for the iterator class
template<class KeyType, class ValueType, class CompareType = std::less<KeyType>>
class bst;

#include "iterator.hxx"

template<class KeyType, class ValueType, class CompareType>
class bst 
{
    
    private:
        class Node;
        std::unique_ptr<Node> root;
        using iterator = __iterator<Node,KeyType,ValueType,CompareType,false>;
        using const_iterator = __iterator<Node,KeyType,ValueType,CompareType,true>;

        /**
         * @brief Given a node in a tree, returns its successor
         * @param node A pointer to a node
         * @return Pointer to node's successor
         */
        //Node *successor(Node * node) const;

        /**
         * @brief Given a pointer to a node, find the leftmost element in the sub-tree
         * with node as root
         * @param node Pointer to a node
         * @return Pointer to a node which is the leftmost element of the sub-tree rooted
         * in node
         */
        Node *leftmost(Node * node) const;


        /**
         * @brief Recursive private method to create deep copy of a binary search tree
         * @param node The root node of the tree that should be copied
         */
        void copy(const std::unique_ptr<Node> &node);

        /**
         * @brief Function that swapes the two nodes inside the tree topology
         * @param successor The first node.
         * @param current The second node.
         */
        void swap(Node* successor, Node* current);

        /**
         * @brief Auxiliary recursive function for erasing a node in tree rooted in the node passed
         * @param key The key of the node to be deleted
         * @param node Pointer to the root of the (sub-)tree to search the node in.
         */
        void erase_aux(const KeyType& key, Node* node);

        /**
         * @brief Find the node of given key
         * @param key The key value to be found in bst
         * @param current Pointer to the root of the (sub-)tree to search the node in.
         * @return Iterator to the found node (to nullptr if the node is not found)
         */
        iterator find_aux(const KeyType& key, Node *current);

        /**
         * @brief Find the node of given key
         * @param key The key value to be found in bst
         * @param current Pointer to the root of the (sub-)tree to search the node in.
         * @return Const-iterator to the found node (to nullptr if the node is not found)
         */
        const_iterator find_aux(const KeyType& key, Node *current) const;
    public:
        CompareType comparator;
        
        /**
         * @brief Default constructor
         */
        bst() noexcept = default;
        
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
        
        /**
         * @brief Method that generates an iterator
         * @return An iterator to the first element of the bst
         *         according to the in-order visit
         */
        iterator begin() noexcept
        {
            return iterator{leftmost(root.get())};
        }

        /**
         * @brief Method that generates a const-iterator
         * @return A const-iterator to the first element of the bst
         *         according to the in-order visit
         */
        const_iterator begin() const noexcept
        {
            const_iterator it{leftmost(root.get())};
            return it;
        }

        /**
         * @brief Method that generates a const-iterator
         * @return A const-iterator to the first element of the bst
         *         according to the in-order visit
         */
        const_iterator cbegin() const noexcept
        {
            const_iterator it{leftmost(root.get())};
            return it;
        }

        /**
         * @brief Method that returns an iterator to nullptr
         * @return Iterator to nullptr
         */
        iterator end() noexcept { return iterator{nullptr}; }

        /**
         * @brief Method that returns a const-iterator to nullptr
         * @return Const-iterator to nullptr
         */
        const_iterator end() const noexcept
        {
            const_iterator it{nullptr};
            return it;
        }

        /**
         * @brief Method that returns a const-iterator to nullptr
         * @return Const-iterator to nullptr
         */
        const_iterator cend() const noexcept
        {         
            const_iterator it{nullptr};    
            return it; 
        }

        /**
         *  @brief Insert the node of given key
         *  @param data Pair data to be inserted
         *  @return A pair<iterator, bool>
         */
        std::pair<iterator, bool> insert(const std::pair<const KeyType, ValueType>& data);

        /**
         *  @brief Insert the node of given key
         *  @param data r-value of the pair data to be inserted
         *  @return A pair<iterator, bool>
         */
        std::pair<iterator, bool> insert(std::pair<const KeyType, ValueType>&& data);      

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
        void clear() noexcept { root.reset(); }

        /**
         * @brief Function that searches an element inside the tree and returns an iterator.
         * @param key The key of the node to be searched for.
         * @return If the node is found, an iterator pointing to it, an empty iterator otherwise.
         */
        iterator find(const KeyType& key)
        {
            return find_aux(key, root.get());
        }

        /**
         * @brief Function that searches an element inside the tree and returns a const_iterator.
         * @param key The key of the node to be searched for.
         * @return If the node is found, a const_iterator pointing to it, an empty iterator otherwise.
         */
        const_iterator find(const KeyType& key) const
        {
            return find_aux(key, root.get());
        }

        /**
         * @brief Given a key, find the node and delete the node
         * @param key The key of the node to be found and deleted
         */
        void erase(const KeyType& key)
        {
            erase_aux(key, root.get());
        }

        /**
         * @brief Method to get the root of tree
         * @return Pointer to Node
         */
        Node* getRoot() const
        {
            return root.get();
        }

        /**
         *  @brief Auxiliary recursive function to build a bst
         *  @param nodes Containers of nodes
         *  @param start Beginning position
         *  @param end Ending position
         */ 
        void buildTree(std::vector<std::pair<const KeyType,ValueType>> &nodes, int start, int end);
        
        /**
         * @brief Method to find the height of tree
         * @param node Pointer to tree's root
         * @return The height of the tree
         */
        int height(Node* node); 

        /**
         * @brief Find if tree is balanced
         * @param node Pointer to root node of tree
         * @return 1 if tree is balanced, otherwise 0
         */
        bool isBalanced(Node* node);
        
        /**
         *  @brief function that balance the tree
         */ 
        void balance();

        /**
         * @brief Operator [] that returns the Value contained by the node to be searched.
         * @param key Key to be searched in the tree.
         * @return Value contained by the node with the key passed.
         */
        ValueType& operator[](const KeyType& key) noexcept;

        /**
         * @brief Operator [] that returns the Value contained by the node to be searched.
         * @param key Key to be searched in the tree.
         * @return Value contained by the node with the key passed.
         */
        ValueType& operator[](KeyType&& key) noexcept;
};
/*
template <class KeyType, class ValueType, class CompareType>
typename bst<KeyType,ValueType,CompareType>::Node * bst<KeyType,ValueType,CompareType>::successor(Node * node) const
{
    if (node->right)
    {
        return leftmost(node->right.get());
    }

    Node * p = node->parent;        
    while (p && node == p->right.get())
    {
        node = p;
        p = p->parent;
    }

    return p;
}
*/
template <class KeyType, class ValueType, class CompareType>
typename bst<KeyType,ValueType,CompareType>::Node * bst<KeyType,ValueType,CompareType>::leftmost(Node * node) const
{
    if (node)
    {
        while (node->get_left())
        {
            node = node->get_left().get();
        }
    }

    return node;
}

template <class KeyType, class ValueType, class CompareType>
void bst<KeyType,ValueType,CompareType>::copy(const std::unique_ptr<bst<KeyType,ValueType,CompareType>::Node> &node)
{
    if (node)
    {
        insert(std::forward<const std::pair<const KeyType, ValueType>>(node->get_data()));
        copy(node->get_left());
        copy(node->get_right());
    }
}

template <class KeyType, class ValueType, class CompareType>
std::pair<typename bst<KeyType, ValueType, CompareType>::iterator, bool> 
bst<KeyType, ValueType, CompareType>::insert(const std::pair<const KeyType, ValueType> &data)
{
    // If tree isn't empty, current node will be created
    Node *current = root.get();
    while (current)
    {
        if (comparator(data.first, current->get_data().first))
        {
            if (!current->get_left())
            {
                current->set_left(data);
                iterator it{current->get_left().get()};
                return std::pair<iterator, bool>{it, true};
            }

            current = current->get_left().get();
        }
        else if (comparator(current->get_data().first, data.first))
        {
            if (!current->get_right())
            {
                current->set_right(data);
                iterator it{current->get_right().get()};
                return std::pair<iterator, bool>{it, true};
            }

            current = current->get_right().get();
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
bst<KeyType, ValueType, CompareType>::insert(std::pair<const KeyType, ValueType> &&data)
{
    // If tree isn't empty, cur node will be created
    Node *current = root.get();
    using pair_type = std::pair<const KeyType, ValueType>;

    while (current)
    {
        if (comparator(data.first, current->get_data().first))
        {
            if (!current->get_left())
            {
                //current->left = std::make_unique<Node>(
                //    std::forward<pair_type>(data), current);
                current->set_left(std::forward<pair_type>(data));
                iterator it{current->get_left().get()};
                return std::pair<iterator, bool>{it, true};
            }

            current = current->get_left().get();
        }
        else if (comparator(current->get_data().first, data.first))
        {
            if (!current->get_right())
            {
                //current->right = std::make_unique<Node>(
                //    std::forward<pair_type>(data), current);
                current->set_right(std::forward<pair_type>(data));
                iterator it{current->get_right().get()};
                return std::pair<iterator, bool>{it, true};
            }

            current = current->get_right().get();
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
bst<KeyType, ValueType, CompareType>::find_aux(const KeyType &key, Node *current)
{
    // until current equals to null pointer
    while (current)
    {
        // given key is smaller than current go left
        if (comparator(key, current->get_data().first))
        {
            current = current->get_left().get();
        }
        else if (comparator(current->get_data().first, key))
        {
            current = current->get_right().get();
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
bst<KeyType, ValueType, CompareType>::find_aux(const KeyType &key, Node *current) const
{    
    // until current equals to null pointer
    while (current)
    {
        // given key is smaller than current go left
        if (comparator(key, current->get_data().first))
        {
            current = current->get_left().get();
        }
        else if (comparator(current->get_data().first, key))
        {
            current = current->get_right().get();
        }
        else
        {
            // it is equal return current one
            return const_iterator{current};
        }
    }

    // key does not exist in tree
    return cend();
}

template <class KeyType, class ValueType, class CompareType>
void bst<KeyType, ValueType, CompareType>::swap(Node* successor, Node* current)
{
    Node *succ_left, *succ_right, *succ_parent, *curr_left, *curr_right, *curr_parent;

    //Detach successor's children
    succ_left = successor->detach_left();
    succ_right = successor->detach_right();
    succ_parent = successor->get_parent();

    //detach successor from its parent. If it has no parent (it is root)
    //we release the ownership of root
    if (successor->is_right())
    {
        succ_parent->detach_right();
    }
    else if (successor->is_left())
    {
        succ_parent->detach_left();
    }
    else
    {
        root.release();
    }
    
    //Detach current's children
    curr_left = current->detach_left();
    curr_right = current->detach_right();
    curr_parent = current->get_parent();

    //detach current from its parent. If it has no parent (it is root)
    //we release the ownership of root
    if (current->is_right())
    {
        curr_parent->detach_right();
    }
    else if (current->is_left())
    {
        curr_parent->detach_left();
    }
    else
    {
        root.release();
    }
    
    //used to avoid cycles
    bool is_succ_child_of_current = succ_parent == current;
    
    if (succ_parent)
    {   
        // if there would not be this check, and succ_parent == current
        // then comparator woould compare the node against the node itself
        // returning therefore false and then assigning the right child of 
        // current to current itself
        if (!is_succ_child_of_current)
        {
            if (comparator(current->get_data().first, succ_parent->get_data().first))
            {
                succ_parent->set_left(current);
            }
            else
            {
                succ_parent->set_right(current);
            }
        }
    }
    else
    {
        root.reset(current);
    }
    current->set_left(succ_left);
    current->set_right(succ_right);

    if (curr_parent)
    {
        if (comparator(successor->get_data().first, curr_parent->get_data().first))
        {
            curr_parent->set_left(successor);
        }
        else
        {
            curr_parent->set_right(successor);
        }
    }
    else
    {
        root.reset(successor);
    }
    successor->set_left(curr_left);
    // curr_right would be null if check == true
    successor->set_right(is_succ_child_of_current ? current: curr_right);
}

template <class KeyType, class ValueType, class CompareType>
void bst<KeyType, ValueType, CompareType>::erase_aux(const KeyType &key, Node* node)
{
    
    Node* current = find_aux(key, node).current;
    if (!current)
    {
        return;
    }
    Node* parent = current->get_parent();

    //Case 1: current is a leaf
    if (!current->get_left() && !current->get_right())
    {
        if (current != root.get())
        {
            //if current is left child of its parent
            if (parent->get_left().get() == current)
            {
                parent->destroy_left();
            }
            else
            {
                parent->destroy_right();
            }
            
        }
        //if current is the root
        else
        {
            root.reset();
            return;
        }
    }
    //Case 2: current has both right and left child
    else if (current->get_left() && current->get_right())
    {
        // We get the successor of the current node, which,
        // in the case current has the right child, is the
        // leftmost node in the subtree rooted in the right child
        // of current
        Node* successor = leftmost(current->get_right().get());
        //we swap successor and current
        swap(successor, current);
        //recursively delete current, which now is either a leaf or a node
        //with only one child
        erase_aux(key, current);
    }
    //Case 3: current has only one child
    else
    {
        Node* child = (current->get_left()) ? current->detach_left() : current->detach_right();

        if (current != root.get())
        {
            if (current == parent->get_left().get())
            {
                parent->detach_left();
                parent->set_left(child);
            }
            else
            {
                parent->detach_right();
                parent->set_right(child);
            }
        }
        else
        {
            root.release();
            child->set_parent(nullptr);
            root.reset(child);
        }

        delete current;
    }
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
void bst<KeyType,ValueType,CompareType>::buildTree(std::vector<std::pair<const KeyType, ValueType>> &nodes, int start, int end)
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
    return 1 + std::max(height(node->get_left().get()),
                        height(node->get_right().get()));
}

template <class KeyType, class ValueType, class CompareType>
bool bst<KeyType,ValueType,CompareType>::isBalanced(typename bst<KeyType, ValueType, CompareType>::Node* node)
{
    if (!node)
    {
        return true;
    }

    int lh, rh;

    lh = height(node->get_left().get());
    rh = height(node->get_right().get());

    return abs(lh - rh) <= 1 && isBalanced(node->get_left().get()) && isBalanced(node->get_right().get());
}

template <class KeyType, class ValueType, class CompareType>
void bst<KeyType, ValueType, CompareType>::balance()
{
    std::vector<std::pair<const KeyType, ValueType>> nodes;
    for(auto& node : *this)
    {
        nodes.push_back(node);
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
        if (comparator(key, current->get_data().first))
        {
            if (!current->get_left())
            {
                auto pair = std::pair<const KeyType, ValueType>{key, ValueType{}};
                current->set_left(std::forward<std::pair<const KeyType, ValueType>>(pair));
                return current->get_left()->get_data().second;
            }
            else
            {
                current = current->get_left().get();
            }
        }
        else if (comparator(current->get_data().first, key))
        {

            if (!current->get_right())
            {
                auto pair = std::pair<const KeyType, ValueType>{key, ValueType{}};
                current->set_right(std::forward<std::pair<const KeyType, ValueType>>(pair));
                return current->get_right()->get_data().second;
            }
            else
            {
                current = current->get_right().get();
            }
        }
        else
        {
            return current->get_data().second;
        }
    }

    //root is null
    auto pair = std::pair<const KeyType, ValueType>{key, ValueType{}};
    root = std::make_unique<Node>(std::forward<std::pair<const KeyType, ValueType>>(pair), nullptr);
    return root->get_data().second;
}

template <class KeyType, class ValueType, class CompareType>
ValueType& bst<KeyType,ValueType,CompareType>::operator[](KeyType &&key) noexcept
{
    Node *current = root.get();
    while (current)
    {
        if (comparator(std::forward<KeyType>(key), current->get_data().first))
        {
            if (!current->get_left())
            {
                auto pair = std::pair<const KeyType, ValueType>{
                    std::forward<const KeyType>(key), ValueType{}
                };
                current->set_left(std::forward<std::pair<const KeyType, ValueType>>(pair));
                return current->get_left()->get_data().second;
            }
            else
            {
                current = current->get_left().get();
            }
        }
        else if (comparator(current->get_data().first, std::forward<KeyType>(key)))
        {

            if (!current->get_right())
            {
                auto pair = std::pair<const KeyType, ValueType>{
                    std::forward<const KeyType>(key), ValueType{}
                };
                current->set_right(std::forward<std::pair<const KeyType, ValueType>>(pair));
                return current->get_right()->get_data().second;
            }
            else
            {
                current = current->get_right().get();
            }
        }
        else
        {
            //element found
            return current->get_data().second;
        }
    }

    //root is null
    auto pair = std::pair<const KeyType, ValueType>{std::forward<const KeyType>(key), ValueType{}};
    root = std::make_unique<Node>(std::forward<std::pair<const KeyType, ValueType>>(pair), nullptr);
    return root->get_data().second;
}


#include "node.hxx"

#endif