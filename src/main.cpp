#include <iostream>
#include "bst.hxx"

int main() {
    std::pair<int, int> p{1,1};
    bst<int, int> b{p};
    std::cout << b << std::endl;
    return 0;
}