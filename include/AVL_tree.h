//
// Created by MacBook on 06.03.2018.
//

#ifndef AVL_TREE_AVL_TREE_H
#define AVL_TREE_AVL_TREE_H

#include <iostream>
#include "node.h"
#include "pre_order_iterator.h"
#include "in_order_iterator.h"
#include "post_order_iterator.h"


template<typename U, typename T>
class AVL_tree {
public:
    AVL_tree();

    virtual ~AVL_tree();

    void print(const std::function<void(const U &, const T &)> & = [](const U &k, const T &v) -> void {
        std::cout << k << " " << v;
        std::cout.flush();
    }) const;

    T &at(const U &key) throw(std::exception);

    const T &at(const U &key) const throw(std::exception);

    T &operator[](const U &key);

    T &operator[](U &&key);

    template<template<typename, typename> class I = in_order_iterator>
    I<U, T> begin() const { return I<U, T>(this->root); }

    template<template<typename, typename> class I = in_order_iterator>
    I<U, T> end() const { return I<U, T>(); }

    bool empty() const;

    int size() const;

    void clear();

    std::size_t erase(const U &key);

    int height() const;

private:
    node<U, T> *root;
    int32_t m_size;

    void print(node<U, T> *, const std::string &, int,
               const std::function<void(const U &, const T &)> &) const;

    void bf(node<U, T> *node);

    void take_out(node<U, T> *&);

    void bf_recalculate_down(node<U, T> *);

    int height(node<U, T> *) const;

    int how_height(node<U, T> *) const;

    void rr(node<U, T> *);

    void rl(node<U, T> *);

    void ll(node<U, T> *);

    void lr(node<U, T> *);

    node<U, T> *find(const U &) const;

};

template<typename U, typename T>
AVL_tree<U, T>::AVL_tree(): root(nullptr), m_size(0) {}


template<typename U, typename T>
void AVL_tree<U, T>::print(const std::function<void(const U &, const T &)> &display) const {
    if (this->root) {
        this->print(this->root, "  ", 0, display);
    }
    printf("\n");
}

template<typename U, typename T>
void
AVL_tree<U, T>::print(node<U, T> *node, const std::string &str, int side,
                      const std::function<void(const U &, const T &)> &display) const {

    if (node) {
        std::string s = str;
        if (side == -1) {
            s[s.length() - 2] = ' ';
        }
        this->print(node->left, s + "# ", -1, display);

        s = s.substr(0, str.length() - 2);
        printf("%s##:%i ", s.c_str(), node->bf);
        fflush(stdout);
        display(node->key, node->value);
        printf(" - %i\n", this->how_height(node));

        s = str;
        if (side == 1) {
            s[s.length() - 2] = ' ';
        }
        this->print(node->right, s + "# ", 1, display);
    }
}

template<typename U, typename T>
void AVL_tree<U, T>::bf(node <U, T> *node) {

    this->m_size += 1;
    if (!node->parent) {
        return;
    }

    auto p = node;
    do {

        if (p->parent->right == p) {
            p->parent->bf += 1;
        } else {
            p->parent->bf -= 1;
        }
        if (p->parent->bf == 0) {
            break;
        }

        p = p->parent;
        if (p->bf == -2) {
            if (p->left->bf == -1 || p->left->bf == 0) {
                ll(p);
            } else {
                lr(p);
            }
            break;
        } else if (p->bf == 2) {
            if (p->right->bf == 1 || p->right->bf == 0) {
                rr(p);
            } else {
                rl(p);
            }
            break;
        }
    } while (p->parent);
}

template<typename U, typename T>
void AVL_tree<U, T>::rr(node <U, T> *A) {
    auto B = A->right;
    auto p = A->parent;

    A->right = B->left;
    if (A->right) {
        A->right->parent = A;
    }
    B->left = A;
    B->parent = p;
    A->parent = B;
    if (p == nullptr) {
        this->root = B;
    } else {
        if (p->left == A) {
            p->left = B;
        } else {
            p->right = B;
        }
    }
    if (B->bf == 1) {
        A->bf = 0;
        B->bf = 0;
    } else {
        A->bf = 1;
        B->bf = -1;
    }
}

template<typename U, typename T>
void AVL_tree<U, T>::rl(node <U, T> *A) {
    auto B = A->right;
    auto C = B->left;
    auto p = A->parent;

    B->left = C->right;
    if (B->left) {
        B->left->parent = B;
    }
    A->right = C->left;
    if (A->right) {
        A->right->parent = A;
    }
    C->left = A;
    C->right = B;
    A->parent = C;
    B->parent = C;
    C->parent = p;
    if (C->parent == nullptr) {
        this->root = C;
    } else {
        if (p->left == A) {
            p->left = C;
        } else {
            p->right = C;
        }
    }
    if (C->bf == -1) {
        B->bf = 1;
    } else {
        B->bf = 0;
    }
    if (C->bf == 1) {
        A->bf = -1;
    } else {
        A->bf = 0;
    }
    C->bf = 0;
}

template<typename U, typename T>
void AVL_tree<U, T>::ll(node <U, T> *A) {
    auto B = A->left;
    auto p = A->parent;

    A->left = B->right;
    if (A->left) {
        A->left->parent = A;
    }
    B->right = A;
    B->parent = p;
    A->parent = B;
    if (p == nullptr) {
        this->root = B;
    } else {
        if (p->left == A) {
            p->left = B;
        } else {
            p->right = B;
        }
    }
    if (B->bf == -1) {
        A->bf = 0;
        B->bf = 0;
    } else {
        A->bf = -1;
        B->bf = 1;
    }
}

template<typename U, typename T>
void AVL_tree<U, T>::lr(node <U, T> *A) {
    auto B = A->left;
    auto C = B->right;
    auto p = A->parent;

    B->right = C->left;
    if (B->right) {
        B->right->parent = B;
    }
    A->left = C->right;
    if (A->left) {
        A->left->parent = A;
    }
    C->right = A;
    C->left = B;
    A->parent = C;
    B->parent = C;
    C->parent = p;
    if (C->parent == nullptr) {
        this->root = C;
    } else {
        if (p->left == A) {
            p->left = C;
        } else {
            p->right = C;
        }
    }
    if (C->bf == -1) {
        A->bf = 1;
    } else {
        A->bf = 0;
    }
    if (C->bf == 1) {
        B->bf = -1;
    } else {
        B->bf = 0;
    }
    C->bf = 0;
}

template<typename U, typename T>
void AVL_tree<U, T>::take_out(node <U, T> *&node) {

    if (node->left && node->right) {
        ::node<U, T> *take;

        take = node->left;
        while (take->right) {
            take = take->right;
        }

        take_out(take);

        take->right = node->right;
        if (take->right) {
            take->right->parent = take;
        }
        take->left = node->left;
        if (take->left) {
            take->left->parent = take;
        }
        take->bf = node->bf;

        if (node->parent) {
            if (node->parent->right == node) {
                node->parent->right = take;
            } else {
                node->parent->left = take;
            }
            take->parent = node->parent;
        } else {
            root = take;
            root->parent = nullptr;
        }

        return;
    }

    bf_recalculate_down(node);

    if (!(node->left || node->right)) {
        if (node->parent) {
            if (node->parent->left == node) {
                node->parent->left = nullptr;
            } else {
                node->parent->right = nullptr;
            }
        } else {
            root = nullptr;
        }

    } else if (node->right) {
        if (node->parent) {
            if (node->parent->right == node) {
                node->parent->right = node->right;
                node->right->parent = node->parent;
            } else {
                node->parent->left = node->right;
                node->right->parent = node->parent;
            }
        } else {
            root = node->right;
            root->parent = nullptr;
        }
    } else { //node->left
        if (node->parent) {
            if (node->parent->right == node) {
                node->parent->right = node->left;
                node->left->parent = node->parent;
            } else {
                node->parent->left = node->left;
                node->left->parent = node->parent;
            }
        } else {
            root = node->left;
            root->parent = nullptr;
        }
    }

    node->parent = nullptr;
}

template<typename U, typename T>
AVL_tree<U, T>::~AVL_tree() {
    this->clear();
}

template<typename U, typename T>
int AVL_tree<U, T>::height(node <U, T> *node) const {
    int32_t height = 0;

    while (node) {
        height += 1;
        if (node->bf <= 0) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    return height;
}

template<typename U, typename T>
int AVL_tree<U, T>::height() const {
    return height(this->root);
}

template<typename U, typename T>
void AVL_tree<U, T>::bf_recalculate_down(node <U, T> *node) {

    auto p = node->parent;

    if (p) {
        if (p->right == node) { //decrement added
            p->bf -= 1;
        } else {
            p->bf += 1;
        }
        if (p->bf == 0) {
            bf_recalculate_down(node->parent); ///!!!???
        } else if (p->bf == -2) {
            if (p->left->bf == -1 || p->left->bf == 0) {
                ll(p);
            } else {
                lr(p);
            }
        } else if (p->bf == 2) {
            if (p->right->bf == 1 || p->right->bf == 0) {
                rr(p);
            } else {
                rl(p);
            }
        }
    }
}

template<typename U, typename T>
int AVL_tree<U, T>::how_height(node <U, T> *node) const {

    int32_t i = 0;

    while (node->parent) {
        node = node->parent;
        ++i;
    }

    return i;
}

template<typename U, typename T>
T &AVL_tree<U, T>::at(const U &key) throw(std::exception) {
    auto node = find(key);
    if (node) {
        return node->value;
    } else {
        throw std::runtime_error("Out of range");
    }
}

template<typename U, typename T>
const T &AVL_tree<U, T>::at(const U &key) const throw(std::exception) {
    auto node = find(key);
    if (node) {
        return node->value;
    } else {
        throw std::runtime_error("Out of range");
    }
}

template<typename U, typename T>
T &AVL_tree<U, T>::operator[](const U &key) {
    auto node = this->root;

    if (!node) {
        this->root = new ::node<U, T>(key);
        bf(this->root);
        return this->root->value;
    }

    while (true) {
        if (node->key > key) {
            if (node->left) {
                node = node->left;
            } else {
                node->left = new ::node<U, T>(key);
                node->left->parent = node;
                bf(node->left);
                return node->left->value;
            }
        } else if (node->key < key) {
            if (node->right) {
                node = node->right;
            } else {
                node->right = new ::node<U, T>(key);
                node->right->parent = node;
                bf(node->right);
                return node->right->value;
            }
        } else {
            return node->value;
        }
    }
}

template<typename U, typename T>
T &AVL_tree<U, T>::operator[](U &&key) {
    auto node = this->root;

    if (!node) {
        this->root = new ::node<U, T>(key);
        bf(this->root);
        return this->root->value;
    }

    while (true) {
        if (node->key > key) {
            if (node->left) {
                node = node->left;
            } else {
                node->left = new ::node<U, T>(key);
                node->left->parent = node;
                bf(node->left);
                return node->left->value;
            }
        } else if (node->key < key) {
            if (node->right) {
                node = node->right;
            } else {
                node->right = new ::node<U, T>(key);
                node->right->parent = node;
                bf(node->right);
                return node->right->value;
            }
        } else {
            return node->value;
        }
    }
}

template<typename U, typename T>
bool AVL_tree<U, T>::empty() const {
    return this->root == nullptr;
}

template<typename U, typename T>
int AVL_tree<U, T>::size() const {
    return this->m_size;
}

template<typename U, typename T>
void AVL_tree<U, T>::clear() {
    while (true) {
        if (this->root->left) {
            this->root = this->root->left;
        } else if (this->root->right) {
            this->root = this->root->right;
        } else {
            if (this->root->parent) {
                auto *p = this->root->parent;
                if (p->left == this->root) {
                    p->left = nullptr;
                } else {
                    p->right = nullptr;
                }
                delete this->root;
                this->root = p;
            } else {
                delete this->root;
                this->root = nullptr;
                break;
            }
        }
    }
    this->root = nullptr;
    this->m_size = 0;
}

template<typename U, typename T>
std::size_t AVL_tree<U, T>::erase(const U &key) {

    auto node = find(key);
    if (node) {
        take_out(node);
        delete node;
        this->m_size -= 1;
        return 1;
    }

    return 0;
}

template<typename U, typename T>
node<U, T> *AVL_tree<U, T>::find(const U &key) const {

    auto node = this->root;
    while (true) {
        if (node->key > key) {
            if (node->left) {
                node = node->left;
            } else {
                break;
            }
        } else if (node->key < key) {
            if (node->right) {
                node = node->right;
            } else {
                break;
            }
        } else {
            return node;
        }
    }

    return nullptr;
}


#endif //AVL_TREE_AVL_TREE_H
