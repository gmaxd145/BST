#include "BST.h"
#include <iostream>

int main() {
    BinarySearchTree<int, char> bst;
//    bst.insert(6, 'g');
//    bst.insert(7, 's');
//    bst.insert(3, 'f');
//    bst.insert(2, 'd');
//    bst.insert(4, 'j');
//    bst.insert(1, 'p');
//    bst.insert(5, 'l');
//    test

    for (auto it = bst.begin(); it != bst.end();  ++it)
    {
        std::cout << it->first << it->second << " ";
    }

    std::cout << std::endl;

//    auto it = BinarySearchTree<int, char>::Iterator(bst._root->left->right->right);
//    --it;
//    std::cout << it->first << it->second << " ";
//    --it;
//    std::cout << it->first << it->second << " ";
//    --it;
//    std::cout << it->first << it->second << " ";


    return 0;
}
