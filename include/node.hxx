
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
    std::pair<KeyType, ValueType> data;
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
         * @brief default constructor
         */
    Node() = default;
    /**
         * @brief construct a new node given a tuple (key,value)
         * @param data Data to be inserted into the node
         */
    Node(std::pair<KeyType, ValueType> data) : data{data}, left{nullptr}, right{nullptr},
                                               parent{nullptr} {}
    /**
         * @brief construct a new node given a tuple (key,value)
         * and a pointer to parent
         * @param data Data to be inserted inot the node
         * @param parent Pointer to parent node
         */
    Node(std::pair<KeyType, ValueType> data, Node *parent) : data{data}, left{nullptr}, right{nullptr},
                                                             parent{parent} {}

    /**
         * @brief construct a new node given a pointer to a node (copy constructor)
         * @param node Reference to the node to be copied
         */
    Node(const Node &node) : data{node.data}, left{nullptr}, right{nullptr},
                             parent{nullptr} {}
    
    
    Node& operator=(Node &&node) noexcept
    {
        data = std::move(node.data);
        left = std::move(node.left);
        right = std::move(node.right);
        parent = std::move(node.parent);
        return *this;
    }
    

    bool operator==(Node *b)
    {
        return &this == b;
    }

    bool operator!=(Node *b)
    {
        return !(&this == b);
    }

    std::pair<KeyType, ValueType> &get_data()
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

    void detach_children() noexcept
    {
        detach_right();
        detach_left();
    }

    void detach_right() noexcept
    {
        if (right)
        {
            right.get()->parent = nullptr;
            right.release();
            right.reset();
        }
    }
    void detach_left() noexcept
    {
        if (left)
        {
            left.get()->parent = nullptr;
            left.release();
            left.reset();
        }
    }
};