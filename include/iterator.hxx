


template<class KeyType, class ValueType, class CompareType = std::less<KeyType>>
class iterator 
{

    //bst class will be able to access private fields
    friend class bst;

    private:
        Node * current;

    public:
        iterator(Node * node): current{node} {}

        /**
         * @brief Operator *iter
         * @return A reference to the tuple (keytype, valuetype)
         */
        std::pair<const KeyType, ValueType>& operator*() const 
        {
            //return current.getData();
            return current->data;
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
        iterator operator++() {
            iterator iter{*this};
            ++(*this);
            return iter;
        }
        
        /**
         * @brief Operator == to check equality between two iterators, e.g.
         * if they point to the same node
         * @param rightIt the other iterator, on the right-hand side.
         * @return Bool: true if they point to the same node, false otherwise
         */
        bool opearator==(const iterator& rightIt) 
        {
            return current == rightIt.current;
        }


        /**
         * @brief Operator !=, the opposite of ==
         * @param rightIt Iterator on the right-hand side.
         * @return True if they are not equal, true othersise.
         */
        bool operator!=(const iterator& rightIt)
        {
            return current != rightIt.current;
        }
};

template<class KeyType, class ValueType, class CompareType = std::less<KeyType>>
class const_iterator : iterator
{
    friend class bst;
    
    public:
        const std::pair<const KeyType, ValueType>& operator*() const 
        {
            return Iterator::operator*(); 
        }
}
