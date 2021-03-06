//
// Created by MacBook on 10.03.2018.
//

#ifndef AVL_TREE_PRE_ORDER_ITERATOR_H
#define AVL_TREE_PRE_ORDER_ITERATOR_H

#include <iterator>
#include "node.h"

template<typename U, typename T>
class pre_order_iterator : std::iterator<std::input_iterator_tag, T> {
public:
    constexpr pre_order_iterator() : node(nullptr) {}

    explicit pre_order_iterator(const node<U, T> *node) : node(node) {}

    const std::pair<U, T> &operator*() const { return node->pair; }

    const std::pair<U, T> *operator->() const { return &node->pair; }

    pre_order_iterator &operator++() {
        if (node->left) {
            node = node->left;
        } else if (node->right) {
            node = node->right;
        } else if (node->parent) {
            while (node->parent) {
                if (node->parent->left == node) {
                    if (node->parent->right) {
                        node = node->parent->right;
                        break;
                    } else {
                        node = node->parent;
                    }
                } else { //node->parent->right
                    node = node->parent;
                }
            }
            if (!node->parent) {
                node = nullptr;
            }
        } else {
            node = nullptr;
        }

        return *this;
    }

    pre_order_iterator operator++(int) {
        pre_order_iterator __t(*this);
        ++(*this);
        return __t;
    }

    friend
    bool operator==(const pre_order_iterator &__x, const pre_order_iterator &__y) { return __x.node == __y.node; }

    friend
    bool operator!=(const pre_order_iterator &__x, const pre_order_iterator &__y) { return !(__x == __y); }

private:
    const node<U, T> *node;
};

#endif //AVL_TREE_PRE_ORDER_ITERATOR_H
