

template<class KeyType, class ValueType, class CompareType>
class bst<KeyType, ValueType, CompareType>::iterator 
{
    friend class bst;
    using Node = bst<KeyType, ValueType, CompareType>::Node;

    private:
        Node * current;

    public:

        explicit iterator(Node * node): current{node} {}

        /**
         * @brief Operator *iter
         * @return A reference to the tuple (keytype, valuetype)
         */
        std::pair<const KeyType, ValueType>& operator*() const noexcept
        {
            //return current.getData();
            return current->data;
        }

        std::pair<KeyType, ValueType>* operator->() const noexcept
        {
            return &(*(*this));
        }

        /**
         * @brief Operator ++iter to advance to the next node, basing on InOrder 
         * traversal
         * @return Iterator& Reference to this iterator with updated state
         */
        iterator& operator++()
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
                Node* temp{current->parent};
                while (temp && current == temp->right.get())
                {
                    current = temp;
                    temp = temp->parent;
                }
                current = temp;
            }
            return *this;
            
        }

        /**
         * @brief it++ for iterating to the next node
         * @return Iterator value before advancing to the next node
         */
        iterator operator++(int) noexcept
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
        friend bool operator==(const iterator& left, const iterator& right) noexcept
        {
            return left.current == right.current;
        }


        /**
         * @brief Operator !=, the opposite of ==
         * @param left iterator on the left-hand side.
         * @param right iterator on the right-hand side.
         * @return True if they are not equal, true othersise.
         */
        friend bool operator!=(const iterator& left, const iterator& right) noexcept
        {
            return left.current != right.current;
        }
};

template<class KeyType, class ValueType, class CompareType>
class bst<KeyType,ValueType, CompareType>::const_iterator : 
public bst<KeyType,ValueType, CompareType>::iterator
{
	/** Used to give access to getNode method */
	friend class bst;
	/** Alias to make names shorter and intuitive*/
	using iterator = bst<KeyType,ValueType, CompareType>::iterator;
private:
	/**
	 * @brief Returns a constant pointer to the node pointed to by the iterator.
	 */
	//const Node * getNode() const { return Iterator::getNode(); }
public:
	/** Uses the same method of the base class. */
	using iterator::iterator;
	/**
	 * @brief Operator it() for deferencing a binary search tree iterator.
	 * @return const std::pair<TKey, TValue>& Constant reference to current 
	 * node's data in key, value format.
	 */
	const std::pair<const KeyType, ValueType>& operator*() const 
    { 
        return iterator::operator*(); 
    }
};
