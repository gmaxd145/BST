#include "BST.h"
#include <iostream>

int main() {
    BST<int, char> bst;
    bst.insert(12, 'g');
    bst.insert(15, 's');
    bst.insert(13, 'f');
    bst.insert(17, 'd');
    bst.insert(14, 'j');
    bst.insert(20, 'l');
    bst.insert(18, 'p');
    bst.insert(16, 'n');

//    bst.remove(15);
//    std::cout << bst._root->right->value << std::endl;

    std::cout << bst.max(12)->value;


    return 0;
}
