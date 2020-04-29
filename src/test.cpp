#include <iostream>
#include "bst.hxx"

int main() {
    bst<int, int> tree1{};
    for (int i = 0; i < 10; i++)
    {
        tree1.insert(std::pair<const int, int>(i,i));
    }
    
    std::cout << tree1 << std::endl;

    tree1.erase(0);
    std::cout << tree1 << std::endl;

    tree1.erase(3);
    
    std::cout << tree1 << std::endl;

    tree1.erase(6);

std::cout << tree1 << std::endl;

    tree1.balance();
    std::cout << tree1 << std::endl;
    tree1.erase(4);
        std::cout << tree1 << std::endl;

    bst<int, int> tree{};
    tree.emplace(4,4);
    tree.emplace(2,2);
    tree.emplace(1,1);
    tree.emplace(3,3);
    tree.emplace(7,7);
    tree.emplace(9,9);
    tree.emplace(8,8);
    int i = 10;
    int value = tree[i];
    std::cout << "Value is: " << value << std::endl;
    tree.emplace(6,6);
    tree.emplace(5,5);

    std::cout << "Tree:\n" << tree << std::endl;
    
    tree.erase(4);
    std::cout << "After deleteing 4 (root now is: " << tree.getRoot()->get_data().first << "):\n" << tree << std::endl;

    tree.erase(1);
    std::cout << "After deleting 1:\n" << tree << std::endl;

    tree.erase(7);
    std::cout << "After deleting 7:\n" << tree << std::endl;

    tree.emplace(7, 7);
    std::cout << "After emplacing back 7:\n" << tree << std::endl;

    tree.erase(7);
    std::cout << "After deleting 7:\n" << tree << std::endl;

    
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
    
    auto nf = b.find(42); // Meaning of life
    if(nf==b.end())
        std::cout << "\nKey value could not found\n";
    
    //Testing begin and end 
    auto it = b.begin();
    std::cout << "\nKey value of begin " << it->first << ". Value of begin: " << it->second << std::endl; // It should be 0
    
    std::cout << "Testing const iterators" << std::endl;
    for (auto cit = b.cbegin(); cit != b.cend(); ++cit)
    {
        std::cout<< cit->first;
    }
    std::cout << std::endl;
    //++cit;
    //std::cout << "Key value of ++cbegin " << cit->first << " Value of ++cbegin: " << cit->second << std::endl; // It should be 1
    
    //Testing erase
    bst<int, int> b2{};
    b2.emplace(5,5);
    b2.emplace(4,4);
    b2.emplace(6,6);
    std::cout << b2 << std::endl;
    b2.erase(6);
    b2.erase(5);
    std::cout << b2.getRoot()->get_data().first << std::endl;
    std::cout << b2 << std::endl;
    

    std::cout << "\nTesting erase" << std::endl;
    std::cout << b << std::endl;
    b.erase(4);
    std::cout << "4 deleted" << std::endl;
    std::cout << b << std::endl;
    b.balance();
    std::cout << "Balancing done" << std::endl;
    std::cout << b << std::endl;
    b.erase(6);
    std::cout << "6 deleted\nroot: "<< b.getRoot()->get_data().first << "\n" << b << std::endl;
    
    //bool check = !a->get_left() && !a->get_right();
    //std::cout << check << std::endl;
    b.erase(1);
    std::cout << b << std::endl;
    bst<int,int> bst2{};
    bst2.emplace(6,6);
    bst2.emplace(5,5);
    bst2.emplace(9,9);
    bst2.emplace(8,8);
    std::cout << bst2 << std::endl;
    bst2.erase(6);
    std::cout << bst2 << std::endl;

    // Test copy and move constructors
    
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