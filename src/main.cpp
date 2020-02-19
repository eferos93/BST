#include <iostream>
#include "bst.hxx"

int main() {
    
    // Printing the empty BST
    bst<int,int> b{};
    std::cout << b << std::endl;

    for(int i = 0 ; i < 10; i++){
        if(i!=5)
            b.insert(std::pair<int,int>(i,i));
    }

    std::cout << "Tree is balanced?\n"<< b.isBalanced(b.getRoot())<< std::endl;
    std::cout << "Height\n"<< b.height(b.getRoot())<< std::endl;

    b.balance();

    std::cout << "Tree is balanced?\n"<< b.isBalanced(b.getRoot())<< std::endl;
    std::cout << "Height\n"<< b.height(b.getRoot())<< std::endl;

    std::cout << b << std::endl;

    // Inserting a node with a key already present: expect no change
    b.insert(std::pair<int,int>(3,3)); 
    std::cout << b << std::endl;

    // Inserting a node with a key already present: expect no change
    b.emplace(std::pair<int,int>(5,5)); 
    std::cout << b << std::endl;

    //  Testing operator[] 
    int key = 5;
    std::cout << "The value associated to key " << key << " is " << b[key] << std::endl;

    //Testing find method
    int val = (*b.find(3)).second;
    std::cout << val << " exist in tree" << std::endl;

    // Test copy and move constructors

    bst<int,int> copy_bst{b};
    std::cout << "Copied tree" << std::endl;
    std::cout << copy_bst << std::endl;


    bst<int,int> move_bst = std::move(b);
    std::cout << "Moved tree" << std::endl;
    std::cout << move_bst << std::endl;

    b.clear();
    std::cout << b << std::endl;
}