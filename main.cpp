#include "BST.h"
#include <iostream>

int main() {
    BinarySearchTree<int, char> bst;

//    bst.insert(10, 'g');
//    bst.insert(5, 'q');
//    bst.insert(5, 'h');
//    bst.insert(2, 'b');
//    bst.insert(4, 'm');
//    bst.insert(3, 'f');
//
//
//    for (auto it = bst.begin(); it != bst.end(); ++it)
//    {
//        std::cout << it->first<< it->second << " ";
//    }
//    std::cout << std::endl;
//    bst.erase(5);
//    for (auto it = bst.begin(); it != bst.end(); ++it)
//    {
//        std::cout << it->first<< it->second << " ";
//    }
//    std::cout << std::endl;

    bst.insert(10, 'g');
    bst.insert(5, 'q');
    bst.insert(5, 'h');
    bst.insert(4, 'b');
    bst.insert(8, 'm');
    bst.insert(9, 'f');
    bst.insert(7, 'f');
    bst.insert(3, 'f');


    for (auto it = bst.begin(); it != bst.end(); ++it)
    {
        std::cout << it->first<< it->second << " ";
    }
    std::cout << std::endl;
    bst.erase(5);
    for (auto it = bst.begin(); it != bst.end(); ++it)
    {
        std::cout << it->first<< it->second << " ";
    }
    std::cout << std::endl;

    return 0;
}
