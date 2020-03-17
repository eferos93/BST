#include <iterator>

template<class KeyType, class ValueType, class CompareType, bool Const = true>
class __iterator
{
    //friend class bst;
    using Node = typename bst<KeyType, ValueType, CompareType>::Node;
    using pair_type = std::pair<KeyType, ValueType>;
    private:
        Node * current;

    public:

        __iterator() = default;
        explicit __iterator(Node * node) noexcept : current{node} {}

        //if Const = true, then value_type is const Node (const iterator)
        // otherwise it is just Node
        using value_type = typename std::conditional<Const, const pair_type, pair_type>::type;
        using reference = value_type&;
        using pointer = value_type*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;


        /**
         * @brief Operator *iter
         * @return A reference to the tuple (keytype, valuetype)
         */
        reference operator*() const noexcept
        {
            //return current.getData();
            return current->data;
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
        __iterator& operator++();

        /**
         * @brief it++ for iterating to the next node
         * @return Iterator value before advancing to the next node
         */
        __iterator<Const> operator++(int) noexcept
        {
            iterator iter{*this};
            ++(*this);
            return iter;
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
};

template<class KeyType, class ValueType, class CompareType, bool Const>
//template<bool Const>
__iterator<KeyType,ValueType,CompareType,Const>& 
__iterator<KeyType,ValueType,CompareType,Const>::operator++() noexcept
{
    if (!current)
    {
        return *this;
    }
    else if (current->right)
    {
        current = current->right.get();
        while (current->left)
        {
            current = current->left.get();
        }
    }
    else
    {
        Node *temp{current->parent};
        while (temp && current == temp->right.get())
        {
            current = temp;
            temp = temp->parent;
        }
        current = temp;
    }
    return *this;
}

/*
template<class KeyType, class ValueType, class CompareType>
typename bst<KeyType,ValueType,CompareType>::iterator iterator::operator++(int) noexcept
{
    iterator iter{*this};
    ++(*this);
    return iter;
}
*/
/*
template<class KeyType, class ValueType, class CompareType>
class bst<KeyType,ValueType, CompareType>::const_iterator : 
public bst<KeyType,ValueType, CompareType>::iterator
{
	friend class bst;
	/** Alias to make names shorter and intuitive
	using iterator = bst<KeyType,ValueType, CompareType>::iterator;
private:
	/**
	 * @brief Returns a constant pointer to the node pointed to by the iterator.
	 
	//const Node * getNode() const { return Iterator::getNode(); }
public:
	/** Uses the same method of the base class. 
	using iterator::iterator;
	/**
	 * @brief Operator for deferencing a binary search tree iterator.
	 * @return const std::pair<KeyType, ValueType>& Constant reference to current 
	 * node's data in key, value format.
	 
	const std::pair<const KeyType, ValueType>& operator*() const 
    { 
        return iterator::operator*(); 
    }
};*/
