//
// Created by MacBook on 10.03.2018.
//

#ifndef AVL_TREE_POST_ORDER_ITERATOR_H
#define AVL_TREE_POST_ORDER_ITERATOR_H

#include <iterator>
#include "node.h"

template<typename U, typename T>
class post_order_iterator : std::iterator<std::input_iterator_tag, T> {
public:
    constexpr post_order_iterator() : node(nullptr) {}

    explicit post_order_iterator(const node<U, T> *node) {
        while (node->left) {
            node = node->left;
        }
        this->node = node;
    }

    const std::pair<U, T> &operator*() const { return node->pair; }

    const std::pair<U, T> *operator->() const { return &node->pair; }

    post_order_iterator &operator++() {
        if (node->parent) {
            if (node->parent->left == node) {
                node = node->parent->right;
                while (node->left) {
                    node = node->left;
                }
                if (node->right) {
                    node = node->right;
                }
            } else {
                node = node->parent;
            }
        } else {
            node = nullptr;
        }

        return *this;
    }

    post_order_iterator operator++(int) {
        post_order_iterator __t(*this);
        ++(*this);
        return __t;
    }

    friend
    bool operator==(const post_order_iterator &__x, const post_order_iterator &__y) { return __x.node == __y.node; }

    friend
    bool operator!=(const post_order_iterator &__x, const post_order_iterator &__y) { return !(__x == __y); }

private:
    const node<U, T> *node;
};

#endif //AVL_TREE_POST_ORDER_ITERATOR_H
