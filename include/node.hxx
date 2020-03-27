
/**
 * node.hxx file
 * @authors: Eros Fabrici, ... , ....
 **/
//#include <iostream>
//#include <memory>
#include <cassert> 
template <class KeyType, class ValueType, class CompareType>
class bst<KeyType, ValueType, CompareType>::Node
{
    friend class bst;

private:
    /**
         * tuple containing the key which is an unique identifier for the node
         * and the value
         */
    std::pair<const KeyType, ValueType> data;
    /**
         * pointers to left and right child
         */
    std::unique_ptr<Node> left, right;
    /**
         * pointer to parent node
         */
    Node *parent;

public:
    /**
         * @brief Default constructor
         */
    Node() = default;
    /**
         * @brief Construct a new node given a tuple (key,value)
         * @param data Data to be inserted into the node
         */
    Node(std::pair<const KeyType, ValueType> data) : data{data}, left{nullptr}, right{nullptr},
                                               parent{nullptr} {}
    /**
         * @brief Construct a new node given a tuple (key,value)
         * and a pointer to parent
         * @param data Data to be inserted inot the node
         * @param parent Pointer to parent node
         */
    Node(std::pair<const KeyType, ValueType> data, Node *parent) : data{data}, left{nullptr}, right{nullptr},
                                                             parent{parent} {}

    /**
      * @brief Construct a new node given a pointer to a node (copy constructor)
      * @param node Reference to the node to be copied
      */
    //Node(const Node &node) : data{node.data}, left{nullptr}, right{nullptr},
    //                         parent{nullptr} {}
    Node(const Node& node) = delete;
    
    Node(Node&& node) noexcept :
        data{std::move(node.data)},
        left{std::move(node.left)},
        right{std::move(node.right)},
        parent{std::move(parent)} 
    {}

    /**
     * @brief Move Assignment
     * @param node r-value reference to a Node
     */
    /*Node& operator=(Node &&node) noexcept
    {
        data = std::move(node.data);
        left = std::move(node.left);
        right = std::move(node.right);
        parent = std::move(node.parent);
        return *this;
    }*/
    
    Node& operator=(const Node&) = delete;
    /**
     * @brief equality operator
     * @param b pointer to another node to be checked
     */
    //bool operator==(Node *b)
    //{
    //    return &this == b;
    //}

    /**
     * @brief inequality operator
     * @param b pointer to the node to be checked
     */
    //bool operator!=(Node *b)
    //{
    //    return !(&this == b);
    //}

    /**
     * @brief Method to check if this instance of Node is right child of its parent
     * @return True iff this instance is right child of parent
     *         False otherwise (also when parent is null)
     */
    bool is_right() const noexcept
    {
        return (parent && (parent->right.get() == this));
    }

    /**
     * @brief Method to check if this instance of Node is left child of its parent
     * @return True iff this instance is left child of parent
     *         False otherwise (also when parent is null)
     */
    bool is_left() const noexcept
    {
        return (parent && (parent->left.get() == this));
    }

    /**
     * @brief Method to check if the node is root.
     * @return True if node is root, false otherwise.
     */
    bool is_root() const noexcept
    {
        return !is_left() && !is_right();
    }

    /**
     * @brief Getter for the data
     * @return Reference to the data contained in this instance of Node
     */
    std::pair<const KeyType, ValueType> &get_data() noexcept
    {
        return data;
    }

    /**
     * @brief Getter for left child
     * @return Referece to the left child
     */
    std::unique_ptr<Node> &get_left() noexcept
    {
        return left;
    }

    /**
     * @brief Getter for right child
     * @return Reference to the right child
     */
    std::unique_ptr<Node> &get_right() noexcept
    {
        return right;
    }

    /**
     * @brief Getter for the parent
     * @return Pointer to the parent Node
     */
    Node *get_parent() noexcept
    {
        return parent;
    }

    /**
     * @brief Setter for the data
     * @param data R-value reference to the data to be inserted
     
    void set_data(std::pair<const KeyType, ValueType>&& data)
    {
        //this->data = std::forward<std::pair<const KeyType, ValueType>>(data);
        this->data = data;
    }
    */
    /**
     * @brief Setter for the left node
     * @param new_node Pointer to the new_node to be inserted
     * The method will abort if new_node points to the parent of this instance
     * as this would result in creating a cycle between this and new_node.
     * The program is aborted also if left is not null.
     * If new_node is null, then left is freed and set to null.
     */
    void set_left(Node* new_node)
    {
        //avoid creation of cycles
        assert( !(parent && parent == new_node) );
        if (new_node)
        {
            assert( !left ); //can be setted iff left is null
            left.reset(new_node);
            left->parent = this;
        }
        else
        {
            destroy_left();
        }
        
    }

    /**
     * @brief Setter for the right node
     * @param new_node Pointer to the new_node to be inserted
     * The method will abort if new_node points to the parent of this instance
     * as this would result in creating a cycle between this and new_node.
     * The program is aborted also if right is not null.
     * If new_node is null, then right is freed and set to null.
     */
    void set_right(Node* new_node)
    {
        //avoid cycle
        assert( !parent || parent != new_node );
        if (new_node)
        {
            assert( !right ); //can be setted iff right is null
            right.reset(new_node);
            right->parent = this;
        }
        else
        {
            destroy_right();
        }
        
    }

    /**
     * @brief Method that detaches the right.
     * @return Pointer to the detached node.
     * This method will detach the right child, namely it won't its pointed memory location
     */
    Node* detach_right() noexcept
    {
        Node* ptr = nullptr;
        if (right)
        {
            right->parent = nullptr;
            ptr = right.release();
            right = nullptr;
        }
        return ptr;
    
    }

    /**
     * @brief Method that detaches the left child.
     * @return Pointer to the Node detached.
     * This method will detach the right child, namely it won't its pointed memory location.
     */
    Node* detach_left() noexcept
    {
        Node* ptr = nullptr;
        if (left)
        {
            left->parent = nullptr;
            ptr = left.release();
            left = nullptr;
        }
        return ptr;
    }

    /**
     * @brief Method that detaches both children
     */
    void detach_children() noexcept
    {
        detach_right();
        detach_left();
    }

    /**
     * @brief Method to "destroy" right child (set as null and free the memory)
     */
    void destroy_right() noexcept
    {
        if (right) 
        {
            right.reset();
        }
    }

    /**
     * @brief Method to "destroy" left child (set as null and free the memory)
     */
    void destroy_left() noexcept
    {
        if (left)
        {
            left.reset();
        }
        
    }
    
    /*void swap(Node* other) noexcept
    {
        auto p_other = other->parent;
        auto l_other = other->left.release();
        auto r_other = other->right.release();
        

        auto p_self = parent;
        auto r_self = right.release();
        auto l_self = left.release();

        right.reset(r_other);
        if (right)
        {
            right->parent = this;
        }
        left.reset(l_other);
        if (left)
        {
            left->parent = this;
        }
        
        //seg-fault here---------------------
        parent = p_other;
        std::cout << "here" << (parent == nullptr) <<std::endl;
        if (p_other) 
        {
            if (p_other->right.get() == other)
            {
                p_other->right.release();
                p_other->right.reset(this);
            }
            else
            {
                p_other->left.release();
                p_other->left.reset(this);
            }
        }

        //-------------------------------
        std::cout << "I made it!" << std::endl;
        other->right.reset(r_self);
        if (other->right)
        {
            other->right->parent = other;
        }
        other->left.reset(l_self);
        if (other->left)    
        {
            other->left->parent = other;
        }
        
        other->parent = p_self;
        if (p_self)
        {
            if(p_self->right.get() == this)
            {
                p_self->right.release();
                p_self->right.reset(other);
            }
            else
            {
                p_self->left.release();
                p_self->left.reset(other);
            }
        }
    }*/
};