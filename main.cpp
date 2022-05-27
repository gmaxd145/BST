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

//    bst.remove(15);
//    std::cout << bst._root->right->value << std::endl;

//    error
//    BST<int, char> bst2 = std::move(bst);
    std::cout << bst.find(12)->key << std::endl;
    BST<int, char>::Iterator it(bst.find(12));
    ++it;
    std::cout << std::get<0>(*it) << std::endl;
//    std::cout << std::get<0>(*bst.begin()++) << std::endl;
//    std::cout << std::get<0>(*bst.begin()) << std::endl;

//    it++;



    return 0;
}
