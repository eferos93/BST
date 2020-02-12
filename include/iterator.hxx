


template<class KeyType, class ValueType, class CompareType = std::less<KeyType>>
class Iterator {

    //bst class will be able to access private fields
    friend class bst;

    private:
        Node * current;

    public:
        Iterator(Node * node): currentNode{node} {}

        /**
         * @brief Operator *iter
         * @return A reference to the tuple (keytype, valuetype)
         */
        std::pair<const KeyType, ValueType>& operator*() const 
        {
            return current.getData();
        }

        /**
         * @brief Operator ++iter to advance to the next node, basing on InOrder 
         * traversal
         * @return Iterator& Reference to this iterator with updated state
         */
        Iterator& operator++()
        {
            if (!current)
            {
                return *this;
            }
            else if (current.getRight())
            {
                current = current.getRight().get();
                while (current.getLeft())
                {
                    current = current.getLeft().get();
                }
            }
            else
            {
                Node* temp{current.getParent()};
                while (temp && current == temp.getRight().get())
                {
                    current = temp;
                    temp = temp.getParent();
                }
                current = temp;
            }
            return *this;
            
        }

        /**
         * @brief it++ for iterating to the next node
         * @return Iterator value before advancing to the next node
         */
        Iterator operator++() {
            Iterator iter{*this};
            ++(*this);
            return iter;
        }
        
        /**
         * @brief Operator == to check equality between two iterators, e.g.
         * if they point to the same node
         * @param rightIt the other iterator, on the right-hand side.
         * @return Bool: true if they point to the same node, false otherwise
         */
        bool opearator==(const Iterator& rightIt) 
        {
            return current == rightIt.current;
        }


        /**
         * @brief Operator !=, the opposite of ==
         * @param rightIt Iterator on the right-hand side.
         * @return True if they are not equal, true othersise.
         */
        bool operator!=(const Iterator& rightIt)
        {
            return current != rightIt.current;
        }
};