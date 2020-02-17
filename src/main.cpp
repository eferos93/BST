#include <iostream>
#include "bst.hxx"

int main() {

        std::pair<int, int> pair1{8,8};
        std::pair<int, int> pair2{3,3};
        std::pair<int, int> pair3{10,10};
        std::pair<int, int> pair4{1,1};
        std::pair<int, int> pair5{6,6};
        std::pair<int, int> pair6{4,4};
        std::pair<int, int> pair7{7,7};
        std::pair<int, int> pair8{14,14};
        std::pair<int, int> pair9{13,13};

        std::pair<int, int> pair3_bis{10,3};
        
        // Printing the empty BST
        bst<int,int> b{};
        std::cout << b << std::endl;

        //Testing building-up-tree methods
        b.insert(pair1);
        b.insert(pair2);			
        b.insert(pair3);
        b.insert(pair4);
        b.insert(pair5);
        b.insert(pair6);
        b.insert(pair7);
        b.emplace(pair8);
        b.insert(pair9); 

        std::cout << b << std::endl;

        // Inserting a node with a key already present: expect no change
        b.insert(pair3_bis); 
        std::cout << b << std::endl;

        //  Testing operator[] 
        int key = 13;
        std::cout << "The value associated to key " << key << " is " << b[key] << std::endl;

        // Test copy and move constructors

        bst<int,int> copy_bst{b};
        std::cout << "Copied tree" << std::endl;
        std::cout << copy_bst << std::endl;


        bst<int,int> move_bst = std::move(b);
        std::cout << "Moved tree" << std::endl;
        std::cout << copy_bst << std::endl;

        b.clear();
        std::cout << b << std::endl;





}