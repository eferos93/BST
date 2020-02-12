


template<class KeyType, class ValueType, class CompareType = std::less<KeyType>>
<<<<<<< HEAD
class Iterator {
=======
class iterator 
{
>>>>>>> c5ec8309b65ec99687abdc22845f607824f6213e

    //bst class will be able to access private fields
    friend class bst;

    private:
        Node * current;

    public:
<<<<<<< HEAD
        Iterator(Node * node): currentNode{node} {}
=======
        iterator(Node * node): current{node} {}
>>>>>>> c5ec8309b65ec99687abdc22845f607824f6213e

        /**
         * @brief Operator *iter
         * @return A reference to the tuple (keytype, valuetype)
         */
        std::pair<const KeyType, ValueType>& operator*() const 
        {
<<<<<<< HEAD
            return current.getData();
=======
            //return current.getData();
            return current->data;
>>>>>>> c5ec8309b65ec99687abdc22845f607824f6213e
        }

        /**
         * @brief Operator ++iter to advance to the next node, basing on InOrder 
         * traversal
         * @return Iterator& Reference to this iterator with updated state
         */
<<<<<<< HEAD
        Iterator& operator++()
=======
        iterator& operator++()
>>>>>>> c5ec8309b65ec99687abdc22845f607824f6213e
        {
            if (!current)
            {
                return *this;
            }
<<<<<<< HEAD
            else if (current.getRight())
            {
                current = current.getRight().get();
                while (current.getLeft())
                {
                    current = current.getLeft().get();
=======
            else if (current->right)
            {
                current = current->right.get();
                while (current->left)
                {
                    current = current->left.get();
>>>>>>> c5ec8309b65ec99687abdc22845f607824f6213e
                }
            }
            else
            {
<<<<<<< HEAD
                Node* temp{current.getParent()};
                while (temp && current == temp.getRight().get())
                {
                    current = temp;
                    temp = temp.getParent();
=======
                Node* temp{current->parent};
                while (temp && current == temp->right.get())
                {
                    current = temp;
                    temp = temp->parent;
>>>>>>> c5ec8309b65ec99687abdc22845f607824f6213e
                }
                current = temp;
            }
            return *this;
            
        }

        /**
         * @brief it++ for iterating to the next node
         * @return Iterator value before advancing to the next node
         */
<<<<<<< HEAD
        Iterator operator++() {
            Iterator iter{*this};
=======
        iterator operator++() {
            iterator iter{*this};
>>>>>>> c5ec8309b65ec99687abdc22845f607824f6213e
            ++(*this);
            return iter;
        }
        
        /**
         * @brief Operator == to check equality between two iterators, e.g.
         * if they point to the same node
         * @param rightIt the other iterator, on the right-hand side.
         * @return Bool: true if they point to the same node, false otherwise
         */
<<<<<<< HEAD
        bool opearator==(const Iterator& rightIt) 
=======
        bool opearator==(const iterator& rightIt) 
>>>>>>> c5ec8309b65ec99687abdc22845f607824f6213e
        {
            return current == rightIt.current;
        }


        /**
         * @brief Operator !=, the opposite of ==
         * @param rightIt Iterator on the right-hand side.
         * @return True if they are not equal, true othersise.
         */
<<<<<<< HEAD
        bool operator!=(const Iterator& rightIt)
        {
            return current != rightIt.current;
        }
};
=======
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
>>>>>>> c5ec8309b65ec99687abdc22845f607824f6213e
