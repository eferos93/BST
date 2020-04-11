#include <iostream>
#include "bst.hxx"

int main() {
    
    // Printing the empty BST
    bst<int,int> b{};
    std::cout << "Empty Tree\n" <<  b << std::endl;
    
    for(int i = 1 ; i < 10; i++)
    {
        if(i!=5)
            b.insert(std::pair<int,int>(i,i));
    }
    
    std::cout << "Inserted int pairs from 1 to 9\n" << std::endl;
    std::cout << b << std::endl;

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
    int key2 = 5;
    std::cout << "\nThe value associated to key " << key2 << " is " << b[key2] << std::endl;
    std::cout << b[10] << std::endl;
    std::cout << b << std::endl;
    
    //Testing find method
    auto f = b.find(3);
    std::cout << "\n" << f->first << " already exist in tree" << std::endl;
    
    auto nf = b.find(42);
    if(nf==b.end())
        std::cout << "\nKey value could not found\n";
    
    //Testing begin and end 
    auto it = b.begin();
    std::cout << "\nKey value of begin " << it->first << ". Value of begin: " << it->second << std::endl;

    /*
    std::cout << "Testing const iterators" << std::endl;
    for (auto cit = b.cbegin(); cit != b.cend(); ++cit)
    {
        std::cout<< cit->first;
    }
    std::cout << std::endl;*/

    //++cit;
    //std::cout << "Key value of ++cbegin " << cit->first << " Value of ++cbegin: " << cit->second << std::endl; // It should be 1
    
   //Testing erase
    /*bst<int, int> b2{};
    b2.emplace(5,5);
    b2.emplace(4,4);
    b2.emplace(6,6);
    std::cout << b2 << std::endl;
    b2.erase(6);
    b2.erase(5);
    std::cout << b2.getRoot()->get_data().first << std::endl;
    std::cout << b2 << std::endl;*/
    

    std::cout << "\nTesting erase" << std::endl;
    std::cout << b << std::endl;

    //Base scenerio erase leaf

    std::cout << "First element of tree b is " << b.begin()->first << std::endl;
    b.erase(1);
    std::cout << "First element of tree b is " << b.begin()->first << std::endl; // must be 2

    // First scenerio deleting root, root must be changed
    std::cout << "Root of tree b is " << b.getRoot()->get_data().first << std::endl;
    b.erase(4);
    std::cout << "Root of tree b is " << b.getRoot()->get_data().first << std::endl;
    std::cout << b << std::endl;

    //Scenerio delete a node with two children
    b.erase(7);
    std::cout << b << std::endl;

    //Scenerio delete a node with one child
    b.erase(6);
    std::cout << b << std::endl;

    // Scnerio delete a node added with [] operator
    b.erase(10);
    std::cout << b << std::endl;

    // Scenerio delete a node which doesn't exist in tree
    b.erase(69);
    std::cout << b << std::endl;

    //Delete a node which is emplaced
    b.emplace(4,4);
    b.emplace(6,6);
    b.emplace(9,9);
    std::cout << b << std::endl;
    b.erase(4);
    b.erase(9);
    std::cout << b << std::endl;

        //Delete a node which is inserted
    b.insert(std::pair<int,int>(4,4));
    b.insert(std::pair<int,int>(11,11));
    b.insert(std::pair<int,int>(6,6));
    std::cout << b << std::endl;
    b.erase(6);
    b.erase(11);
    std::cout << b << std::endl;


    //Test copy and move constructors
    
    bst<int,int> copy_bst{b};
    std::cout << "original Tree\n" << b << std::endl; 
    std::cout << "\nCopied tree" << std::endl;
    std::cout << copy_bst << std::endl;


    bst<int,int> move_bst = std::move(b);
    std::cout << "\nMoved tree" << std::endl;
    std::cout << move_bst << std::endl;

    b.clear();
    std::cout << "\nAfter clear" <<  b << std::endl;
    std::cout << b << std::endl;
    
}