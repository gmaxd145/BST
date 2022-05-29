#include "BST.h"
#include <iostream>

int main() {
    BinarySearchTree<int, char> bst;
    bst.insert(4, 'g');
    bst.insert(2, 's');
    bst.insert(5, 'f');
    bst.insert(1, 'd');
    bst.insert(3, 'j');
    bst.insert(4, 'l');

//    bst.remove(15);
    std::cout << std::get<1>(bst._root->left->right->right->keyValuePair) << std::endl;

//    error
//    BST<int, char> bst2 = std::move(bst);
//    for (auto it = bst.begin(); it != bst.end();  ++it)
//    {
//        std::cout << it->key << " ";
//    }


//    std::cout << std::get<0>(*bst.begin()++) << std::endl;
//    std::cout << std::get<0>(*bst.begin()) << std::endl;

//    it++;



    return 0;
}
