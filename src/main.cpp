#include <iostream>
#include "bst.hxx"

int main() {
    std::pair<int, int> p{1,1};
    std::pair<int, int> p2{4,4};
    std::pair<int, int> p3{3,3};
    bst<int, int> b;
    b.emplace(9,9);
    b[2];
    b.insert(p);
    b.insert(p2);
    b.insert(p3);
    b.insert(std::pair<int, int>{7,7});
    ///int val = b[5];
    bst<int,int> b2{b};
    //b.erase(4);
    std::cout << b << std::endl;
    std::cout << b2 << std::endl;
    //int val = (*b.find(3)).first;
    //iterator it{b.begin()};
    //for(auto it{b.begin()}; it!=b.end(); ++it)
    //{
    //    std::cout << (*it).first << " ";
    //}
    //std::cout << val << std::endl;
    
    return 0;
}