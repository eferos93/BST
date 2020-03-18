#include <iterator>

template<class Node, class KeyType, class ValueType, bool Const>
class __iterator
{
    //friend class bst;
    public:
        //using Node = typename bst<KeyType, ValueType, CompareType>::Node;
        using pair_type = std::pair<KeyType, ValueType>;
        using value_type = typename std::conditional<Const, const pair_type, pair_type>::type;
        using reference = value_type&;
        using pointer = value_type*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

    private:
        Node * current;
        //value_type data;

    public:
        __iterator() = default;
        explicit __iterator(Node * node) noexcept : current{node}
            //, data{current->getData()}
            {}

        //if Const = true, then value_type is const pair (const iterator)
        // otherwise it is just pair
        

        /**
         * @brief Operator *iter
         * @return A reference to the tuple (keytype, valuetype)
         */
        reference operator*() const noexcept
        {
            return current->get_data();
            //return current->data;
        }

        pointer operator->() const noexcept
        {
            return &(*(*this));
        }

        /**
         * @brief Operator ++iter to advance to the next node, basing on InOrder 
         * traversal
         * @return Iterator& Reference to this iterator with updated state
         */
        __iterator& operator++() noexcept;

        /**
         * @brief it++ for iterating to the next node
         * @return Iterator value before advancing to the next node
         */
        __iterator operator++(int) noexcept
        {
            __iterator it{*this};
            ++(*this);
            return it;
        }
        
        /**
         * @brief Operator == to check equality between two iterators, e.g.
         * if they point to the same node
         * @param left iterator on the left-hand side.
         * @param right iterator on the right-hand side.
         * @return Bool: true if they point to the same node, false otherwise
         */
        friend bool operator==(const __iterator& left, const __iterator& right) noexcept
        {
            return left.current == right.current;
        }


        /**
         * @brief Operator !=, the opposite of ==
         * @param left iterator on the left-hand side.
         * @param right iterator on the right-hand side.
         * @return True if they are not equal, true othersise.
         */
        friend bool operator!=(const __iterator& left, const __iterator& right) noexcept
        {
            return !(left.current == right.current);
        }

        Node * get_node()
        {
            return current;
        }
};

template<class Node, class KeyType, class ValueType, bool Const>
//template<bool Const>
__iterator<Node,KeyType,ValueType,Const>& 
__iterator<Node,KeyType,ValueType,Const>::operator++() noexcept
{
    if (!current)
    {
        return *this;
    }
    else if (current->get_right())
    {
        current = current->get_right().get();
        //current = current->right.get();
        while (current->get_left())
        {
            //current = current->left.get();
            current = current->get_left().get();
        }
    }
    else
    {
        Node *temp{current->get_parent()};
        while (temp && current == temp->get_right().get())
        {
            current = temp;
            temp = temp->get_parent();
        }
        current = temp;
    }
    //data = current->getData();
    return *this;
}