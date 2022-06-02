#include "BST.h"
#include <iostream>

int main() {
    BinarySearchTree<int, char> bst;
//    bst.insert(5, 'g');
//    bst.insert(4, 's');
////    bst.insert(3, 'j');
//    bst.insert(3, 'p');
//    bst.insert(2, 'l');
//    bst.insert(1, 'l');
//    BinarySearchTree<int, char> bst2 = bst;

    bst.insert(12, 'g');
    bst.insert(15, 's');
    bst.insert(13, 'f');
    bst.insert(15, 'h');
    bst.insert(17, 'd');
    bst.insert(14, 'j');
    bst.insert(20, 'l');
    bst.insert(18, 'p');

//    std::cout << bst.size() << std::endl;
//
    for (auto it = bst.begin(); it != bst.end();  ++it)
    {
        std::cout << it->first << it->second << " ";
    }
    std::cout << std::endl;


    bst.erase(15);

    for (auto it = bst.begin(); it != bst.end();  ++it)
    {
        std::cout << it->first << it->second << " ";
    }
    std::cout << std::endl;

//    std::cout << bst._root->right->left->keyValuePair.first << std::endl;


//    for (auto it = bst.begin(); it != bst.end();  ++it)
//    {
//        std::cout << it->first << it->second << " ";
//    }
//    std::cout << std::endl;


//    std::cout << std::endl;
////
//    auto it = BinarySearchTree<int, char>::Iterator(bst._root);
//    std::cout << it->first << it->second << " ";
//    --it;
//    std::cout << it->first << it->second << " ";
//    --it;
//    std::cout << it->first << it->second << " ";
//    --it;
//    std::cout << it->first << it->second << " ";
//    --it;
//    std::cout << it->first << it->second << " ";
//    --it;
//    std::cout << it->first << it->second << " ";
//    --it;
//    std::cout << it->first << it->second << " ";



    return 0;
}
