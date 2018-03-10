//
// Created by MacBook on 10.03.2018.
//

#ifndef AVL_TREE_IN_ORDER_ITERATOR_H
#define AVL_TREE_IN_ORDER_ITERATOR_H

#include <iterator>
#include "node.h"

template<typename T>
class in_order_iterator : std::iterator<std::input_iterator_tag, T> {
public:
    constexpr in_order_iterator() : node(nullptr) {}

    explicit in_order_iterator(node<T> *node) {
        while (node->left) {
            node = node->left;
        }
        this->node = node;
    }

    const T &operator*() const { return node->value; }

    const T *operator->() const { return &node->value; }

    in_order_iterator &operator++() {
        if (node->right) {
            node = node->right;
            while (node->left) {
                node = node->left;
            }
        } else if (node->parent) {
            while (node->parent) {
                if (node->parent->left == node) {
                    node = node->parent;
                    break;
                } else {
                    node = node->parent;
                    if (!node->parent) {
                        node = nullptr;
                        break;
                    }
                }
            }
        }

        return *this;
    }

    in_order_iterator operator++(int) {
        in_order_iterator __t(*this);
        ++(*this);
        return __t;
    }

    friend
    bool operator==(const in_order_iterator &__x, const in_order_iterator &__y) { return __x.node == __y.node; }

    friend
    bool operator!=(const in_order_iterator &__x, const in_order_iterator &__y) { return !(__x == __y); }

private:
    node<T> *node;
};

#endif //AVL_TREE_IN_ORDER_ITERATOR_H
