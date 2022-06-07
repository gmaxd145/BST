#include "BST.h"
#include <iostream>

int main() {
    BinarySearchTree<int, char> bst;
    bst.insert(5, 'g');
    bst.insert(4, 's');
//    bst.insert(4, 'n');
    bst.insert(3, 'p');
    bst.insert(3, 'l');

//    bst.insert(5, 'j');
//    bst.insert(4, 'j');
    bst.insert(2, 't');
    bst.insert(1, 'y');

//    auto [st, sp] = bst.equalRange(3);

//    for (; st != sp;  ++st)
//    {
//        std::cout << st->first << st->second << " ";
//    }
//    std::cout << std::endl;

    std::cout << bst.max(3)->second;
    std::cout << std::endl;


//    std::cout << bst._root->left->left->right->keyValuePair.second;
//    std::cout << std::endl;

//    std::cout << bst.begin()->second;
//        std::cout << std::endl;


//    bst.insert(12, 'g');
//    bst.insert(15, 's');
//    bst.insert(13, 'f');
//    bst.insert(15, 'h');
//    bst.insert(17, 'd');
//    bst.insert(14, 'j');
//    bst.insert(20, 'l');
//    bst.insert(18, 'p');

//    BinarySearchTree<int, char> bst2 = bst;


//    std::cout << bst.size() << std::endl;
//
//    for (auto it = bst.begin(); it != bst.end();  ++it)
//    {
//        std::cout << it->first << it->second << " ";
//    }
//    std::cout << std::endl;


//    bst2.erase(15);
//
//    for (auto it = bst2.begin(); it != bst2.end();  ++it)
//    {
//        std::cout << it->first << it->second << " ";
//    }
//    std::cout << std::endl;

//    std::cout << bst._root->right->left->keyValuePair.first << std::endl;


//    for (auto it = bst.begin(); it != bst.end();  ++it)
//    {
//        std::cout << it->first << it->second << " ";
//    }
//    std::cout << std::endl;


// 



    return 0;
}
