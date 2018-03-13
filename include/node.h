//
// Created by MacBook on 06.03.2018.
//

#ifndef AVL_TREE_NODE_H
#define AVL_TREE_NODE_H

#include <type_traits>


template<typename U, typename T>
struct node {
    node() = delete;

    explicit node(U key);

    explicit node(U &&key);

    explicit node(U key, T &&value);

    explicit node(U &&key, T &&value);

    explicit node(const U &key, const T &value);

    std::pair<U, T> pair;
    U &key;
    T &value;
    node *left;
    node *right;
    node *parent;
    int bf;

    friend
    bool operator==(const node &__x, const node &__y) { return __x.key == __y.key; }

    friend
    bool operator!=(const node &__x, const node &__y) { return !(__x == __y); }

};

template<typename U, typename T>
node<U, T>::node(U key):pair(key, {}), key(pair.first), value(pair.second), parent(nullptr),
                        left(nullptr), right(nullptr), bf(0) {}

template<typename U, typename T>
node<U, T>::node(U &&key):pair(std::forward(key), {}), key(pair.first), value(pair.second), parent(nullptr),
                          left(nullptr), right(nullptr), bf(0) {}

template<typename U, typename T>
node<U, T>::node(U key, T &&value):pair(key, std::forward(value)), key(pair.first), value(pair.second), parent(nullptr),
                                   left(nullptr), right(nullptr), bf(0) {}

template<typename U, typename T>
node<U, T>::node(U &&key, T &&value):pair(std::forward(key), std::forward(value)), key(pair.first), value(pair.second),
                                     parent(nullptr),
                                     left(nullptr), right(nullptr), bf(0) {}

template<typename U, typename T>
node<U, T>::node(const U &key, const T &value):pair(key, value), key(pair.first), value(pair.second), parent(nullptr),
                                               left(nullptr), right(nullptr), bf(0) {}


#endif //AVL_TREE_NODE_H
