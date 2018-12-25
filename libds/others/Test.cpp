//
//  Test.cpp
//  libds
//
//  Created by v tta on 12/17/18.
//  Copyright © 2018 vtta. All rights reserved.
//

#include "Test.hpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

namespace libds {
// beginning of namespace libds

void testBinarySearchTree() {
    BinarySearchTree<int> bst_tree;
    std::srand((unsigned int)time(nullptr));
    for (auto i = 0, r = std::rand(); i < 32768; ++i, r = std::rand()) {
        bst_tree.insert(r);
        std::cout << r << std::endl;
        std::cout << bst_tree << std::endl << std::endl;
    }
    std::cout << bst_tree << std::endl;
}

void testCompleteHeap() {
    int               v[] = {1, 8, 4, 5, 6, 9, 2, 3, 7, 10};
    Vector<int>       vec(v, 10);
    CompleteHeap<int> h1(v, 10);
    for (auto i = 0; i < 10; ++i) { std::cout << h1.eraseMax() << std::endl; }
    vec.sort(0, vec.size());
    for (auto i = 0; i < vec.size(); ++i) {
        std::cout << vec.at(i) << std::endl;
    }
}

void testHashTable() {
    BitSet bs(100);
    for (auto i = 0; i < bs.size(); ++i) { std::cout << bs.test(i); }
    std::cout << std::endl;

    HashTable<int, std::string> ht;
    ht.at(0) = std::to_string(0);
    ht.at(1) = std::to_string(1);
    ht.at(2) = std::to_string(2);
    for (auto i = 0; i < 2000; ++i) { ht.at(i) = std::to_string(10 * i); }
    for (auto i = 100; i < 1000; ++i) { ht.erase(i); }
    for (auto i = 0; i < 2000; ++i) { std::cout << ht.at(i) << std::endl; }
    std::cout << std::endl;
}

void testRedBlackTree() {
    RedBlackTree<int> rb_tree;
    std::srand((unsigned int)time(nullptr));
    int v[] = {13, 11, 8, 6, 1, 27, 25, 22, 17, 15};
    for (auto i = 0, r = std::rand() % 100; i < 10;
         ++i, r        = std::rand() % 100) {
        rb_tree.insert(v[i]);
        std::cout << v[i] << std::endl;
        // std::cout << rb_tree << std::endl << std::endl;
    }
    std::cout << rb_tree << std::endl;
}

// end of namespace libds
}
