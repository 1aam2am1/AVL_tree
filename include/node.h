//
// Created by MacBook on 06.03.2018.
//

#ifndef AVL_TREE_NODE_H
#define AVL_TREE_NODE_H

#include <type_traits>


template<typename T>
struct node {
    node() = default;

    explicit node(T &&value);

    explicit node(const T &value);

    T value;
    node *left;
    node *right;
    node *parent;
    int bf;
};

template<typename T>
node<T>::node(T &&value):value(std::forward(value)), parent(nullptr),
                         left(nullptr), right(nullptr), bf(0) {}

template<typename T>
node<T>::node(const T &value):value(value), parent(nullptr),
                              left(nullptr), right(nullptr), bf(0) {}


#endif //AVL_TREE_NODE_H
