
#include <iterator>

template<class KeyType, class ValueType, class CompareType>
class bst<KeyType, ValueType, CompareType>::__iterator 
{
    using Node = typename bst<KeyType, ValueType, CompareType>::Node;
    Node * current;

    public:
        //using value_type = V;
        using difference_type = std::ptrdiff_t;
        using iterator_type = std::forward_iterator_tag;
        //using reference = value_type&;
        //using pointer = value_type*;

        explicit __iterator(Node * node): current{node} {}

        /**
         * @brief Operator *iter
         * @return A reference to the tuple (keytype, valuetype)
         */
        std::pair<KeyType, ValueType>& operator*() const noexcept
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
        __iterator& operator++()
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
        __iterator operator++() noexcept
        {
            __iterator iter{*this};
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
            return left.current != right.current;
        }
};
