
/**
 * node.hxx file
 * @authors: Eros Fabrici, ... , ....
 **/
//#include <iostream>
//#include <memory>

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
    Node(const Node &node) : data{node.data}, left{nullptr}, right{nullptr},
                             parent{nullptr} {}
    
    /**
     * @brief Move Assignment
     * @param node r-value reference to a Node
     */
    Node& operator=(Node &&node) noexcept
    {
        data = std::move(node.data);
        left = std::move(node.left);
        right = std::move(node.right);
        parent = std::move(node.parent);
        return *this;
    }
    
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

    std::pair<const KeyType, ValueType> &get_data()
    {
        return data;
    }

    std::unique_ptr<Node> &get_left()
    {
        return left;
    }

    std::unique_ptr<Node> &get_right()
    {
        return right;
    }

    Node *get_parent()
    {
        return parent;
    }

    /**
     * @brief method that deletes the right child
     */
    void detach_right() noexcept
    {
        if (right)
        {
            right.get()->parent = nullptr;
            right.release();
            right.reset();
        }
    }

    /**
     * @brief Method that deletes the left child
     */
    void detach_left() noexcept
    {
        if (left)
        {
            left.get()->parent = nullptr;
            left.release();
            left.reset();
        }
    }

    void swap(Node* other) noexcept
    {
        auto p_other = other->parent;
        auto l_other = other->left.get();
        other->left.release();
        auto r_other = other->right.get();
        other->right.release();

        auto p_self = parent;
        auto r_self = right.get();
        right.release();
        auto l_self = left.get();
        left.release();

        other->left.release();
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
        
        parent = p_other;
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
};