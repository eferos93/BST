
/**
 * node.hxx file
 * @author: Eros Fabrici
 * @author: Dogan Can Demirbilek
 * @author: Alessandro Scardoni
 */

#include <cassert> 
#include <exception>
template <class KeyType, class ValueType, class CompareType>
class bst<KeyType, ValueType, CompareType>::Node
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


    // no need of a copy constructor
    Node(const Node& node) = delete;
    
    /**
     * @brief Move constructor.
     * @param node  rvalue reference to a node
     */
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
    Node& operator=(Node &&node) noexcept
    {
        data = std::move(node.data);
        left = std::move(node.left);
        right = std::move(node.right);
        parent = std::move(node.parent);
        return *this;
    }
    
    //We do not need a copy operator
    Node& operator=(const Node&) = delete;

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
    const std::pair<const KeyType, ValueType> &get_data() const noexcept
    {
        return data;
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
     * @brief Getter for left child
     * @return Referece to the left child
     */
    const std::unique_ptr<Node> &get_left() const noexcept
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
     * @brief Getter for right child
     * @return Reference to the right child
     */
    const std::unique_ptr<Node> &get_right() const noexcept
    {
        return right;
    }

    /**
     * @brief Getter for the parent
     * @return Pointer to the parent Node
     */
    Node *get_parent() const noexcept
    {
        return parent;
    }

    /**
     * @brief Setter for the left node
     * @param new_node Pointer to the new_node to be inserted
     * The method will abort if new_node points to the parent of this instance
     * as this would result in creating a cycle between this and new_node.
     * The program is aborted also if left is not null.
     * If new_node is null, then left is freed and set to null.
     */
    void set_left(Node *new_node)
    {
        //avoid creation of cycles
        if (parent && parent == new_node)
        {
            throw std::invalid_argument("Parent is equal to the node it is to be inserted");
        }

        if (new_node)
        {
             //can be setted iff left is null
            if (left)
            {
                throw std::invalid_argument("Left node already exists. It is not possible to attach a new one.");
            }

            left.reset(new_node);
            left->parent = this;
        }
        else
        {
            destroy_left();
        }
        
    }

    /**
     * @brief Setter for the left node by constructing the node in-place
     * @param data The pair to be inserted into the node
     * @throws std::logic_error if left already exists
     */
    void set_left(std::pair<const KeyType, ValueType> &&data)
    {
        if (!left)
        {
            left = std::make_unique<Node>(std::forward<std::pair<const KeyType, ValueType>>(data), this);
        }
        else
        {
            throw std::logic_error("Left node already exists. It is not possible to attach a new one.");
        }
        
    }

    /**
     * @brief Setter for the left node by constructing the node in-place
     * @param data The pair to be inserted into the node
     * @throws std::logic_error if left already exists
     */
    
    void set_left(const std::pair<const KeyType, ValueType> &data)
    {
        if (!left)
        {
            left = std::make_unique<Node>(data, this);
        }
        else
        {
            throw std::logic_error("Left node already exists. It is not possible to attach a new one.");
        }
        
    }
    
    /**
     * @brief Setter for the right node
     * @param new_node Pointer to the new_node to be inserted
     * @throws std::invalid_argument if new_node is equal to the parent of this
     * @throws std::logic_error if right is not null
     * 
     * The method will abort if new_node points to the parent of this instance
     * as this would result in creating a cycle between this and new_node.
     * The program is aborted also if right is not null.
     * If new_node is null, then right is freed and set to null.
     */
    void set_right(Node* new_node)
    {
        //avoid cycle
        if (parent && parent == new_node)
        {
            throw std::invalid_argument("Parent is equal to the node it is to be inserted");
        }

        if (new_node)
        {
            //std::cout << data.first << ": hola" << std::endl;
            if (right)
            {
                throw std::logic_error("Right node already exists. It is not possible to attach a new one.");
            }
            right.reset(new_node);
            right->parent = this;
        }
        else
        {
            destroy_right();
        }
        
    }

    /**
     * @brief Setter for the right node by constructing the node in-place
     * @param data The pair to be inserted into the node
     * @throws std::logic_error if right already exists
     */
    void set_right(std::pair<const KeyType, ValueType> &&data)
    {
        if (!right)
        {
            right = std::make_unique<Node>(std::forward<std::pair<const KeyType, ValueType>>(data), this);
        }
        else
        {
            throw std::logic_error("Right node already exists. It is not possible to attach a new one.");
        }
    }

    /**
     * @brief Setter for the right node by constructing the node in-place
     * @param data The pair to be inserted into the node
     * @throws std::logic_error if right already exists
     */
    
    void set_right(const std::pair<const KeyType, ValueType> &data)
    {
        if (!right)
        {
            right = std::make_unique<Node>(data, this);
        }
        else
        {
            throw std::logic_error("Right node already exists. It is not possible to attach a new one.");
        }
    }
    
    /**
     * @brief Setter for the parent
     * @param node Pointer to the new Node's parent
     */
    void set_parent(Node * node) noexcept
    {
        parent = node;
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
            right->set_parent(nullptr);
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
            left->set_parent(nullptr);
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
};
