#include <iostream>
#include "bst.hxx"

int main() {
    
    // Printing the empty BST
    bst<int,int> b{};
    std::cout << "Empty Tree\n" <<  b << std::endl;

    for(int i = 0 ; i < 10; i++){
        if(i!=5)
            b.insert(std::pair<int,int>(i,i));
    }

    std::cout << "Inserted int pairs from 0 to 9\n" << std::endl;

    std::cout << "Tree is balanced?\n"<< (b.isBalanced(b.getRoot()) ? "Yes\n" : "No\n");
    std::cout << "Height of tree: "<< b.height(b.getRoot())<< std::endl;

    b.balance();

    std::cout << "\nTree is balanced?\n"<< (b.isBalanced(b.getRoot()) ? "Yes\n" : "No\n");
    std::cout << "Height of tree: "<< b.height(b.getRoot())<< std::endl;

    std::cout << "\n" <<b << std::endl;

    // Inserting a node with a key already present: expect no change
    b.insert(std::pair<int,int>(3,3)); 
    std::cout << "\nAfter inserting existing key to tree"<< std::endl;
    std::cout << b << std::endl;

    // Emplace a key value 5 to tree
    b.emplace(std::pair<int,int>(5,5)); 
    std::cout << "\nAfter emplacing 5 to tree"<< std::endl;
    std::cout << b << std::endl;

    //  Testing operator[] 
    int key = 5;
    std::cout << "\nThe value associated to key " << key << " is " << b[key] << std::endl;

    //Testing find method
    auto f = b.find(3);
    std::cout << "\n" << f->first << " already exist in tree" << std::endl;

    auto nf = b.find(42); // Meaning of life
    if(nf==b.end())
        std::cout << "\nKey value could not found\n";

    //Testing begin and end 
    auto it = b.begin();
    std::cout << "\nKey value of begin " << it->first << ". Value of begin: " << it->second << std::endl; // It should be 0


    auto cit = b.cbegin();
    ++cit;
    std::cout << "Key value of ++cbegin " << cit->first << " Value of ++cbegin: " << cit->second << std::endl; // It should be 1

   //Testing erase

    b.erase(4);
    b.erase(9);
    std::cout << "\nAfter 4 and 9 deleted" << std::endl;
    std::cout << b << std::endl;

    // Test copy and move constructors

    bst<int,int> copy_bst{b};
    std::cout << "\nCopied tree" << std::endl;
    std::cout << copy_bst << std::endl;


    bst<int,int> move_bst = std::move(b);
    std::cout << "\nMoved tree" << std::endl;
    std::cout << move_bst << std::endl;

    b.clear();
    std::cout << "\nAfter clear" <<  b << std::endl;
    std::cout << b << std::endl;
}