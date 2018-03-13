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


template<typename T>
class AVL_tree {
public:
    AVL_tree();

    virtual ~AVL_tree();

    void print(const std::function<void(const T &)> & = [](const T &v) -> void {
        std::cout << v;
        std::cout.flush();
    }) const;

    void push(const T &);

    void push(T &&);

    void remove(const T &);

    bool check() const;

    int height() const;

    template<template<typename> class U = in_order_iterator>
    U<T> begin() const { return U<T>(this->root); }

    template<template<typename> class U = in_order_iterator>
    U<T> end() const { return U<T>(); }

private:
    node<T> *root;

    void print(node<T> *, const std::string &, int,
               const std::function<void(const T &)> &) const;

    void push(node<T> *);

    void take_out(node<T> *&);

    void bf_recalculate_down(node<T> *);

    int height(node<T> *) const;

    int how_height(node<T> *) const;

    bool check(node<T> *) const;

    void rr(node<T> *);

    void rl(node<T> *);

    void ll(node<T> *);

    void lr(node<T> *);
};

template<typename T>
AVL_tree<T>::AVL_tree(): root(nullptr) {}


template<typename T>
void AVL_tree<T>::print(const std::function<void(const T &)> &display) const {
    if (this->root) {
        this->print(this->root, "  ", 0, display);
    }
    printf("\n");
}

template<typename T>
void
AVL_tree<T>::print(node<T> *node, const std::string &str, int side,
                   const std::function<void(const T &)> &display) const {

    if (node) {
        std::string s = str;
        if (side == -1) {
            s[s.length() - 2] = ' ';
        }
        this->print(node->left, s + "# ", -1, display);

        s = s.substr(0, str.length() - 2);
        printf("%s##:%i ", s.c_str(), node->bf);
        fflush(stdout);
        display(node->value);
        printf(" - %i\n", this->how_height(node));

        s = str;
        if (side == 1) {
            s[s.length() - 2] = ' ';
        }
        this->print(node->right, s + "# ", 1, display);
    }
}

template<typename T>
void AVL_tree<T>::push(const T &x) {
    auto *node = new ::node<T>(x);

    this->push(node);
}

template<typename T>
void AVL_tree<T>::push(T &&x) {
    auto *node = new ::node<T>(x);

    this->push(node);
}

template<typename T>
void AVL_tree<T>::push(node <T> *node) {
    if (this->root == nullptr) {
        this->root = node;
        return;
    }

    auto *p = this->root;
    do {
        if (p->value > node->value) {
            if (p->left) {
                p = p->left;
            } else {
                p->left = node;
                break;
            }
        } else if (p->value < node->value) {
            if (p->right) {
                p = p->right;
            } else {
                p->right = node;
                break;
            }
        } else {
            delete node;
            return;
        }
    } while (true);
    node->parent = p; //parent

    //bf
    p = node;
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

template<typename T>
void AVL_tree<T>::remove(const T &value) {
    auto *node = this->root;
    while (node) {
        if (node->value == value) {
            take_out(node);
            delete node;
            break;
        } else if (node->value < value) {
            node = node->right;
        } else {
            node = node->left;
        }
    }
}

template<typename T>
void AVL_tree<T>::rr(node <T> *A) {
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

template<typename T>
void AVL_tree<T>::rl(node <T> *A) {
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

template<typename T>
void AVL_tree<T>::ll(node <T> *A) {
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

template<typename T>
void AVL_tree<T>::lr(node <T> *A) {
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

template<typename T>
void AVL_tree<T>::take_out(node <T> *&node) {

    if (node->left && node->right) {
        ::node<T> *take;

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

template<typename T>
AVL_tree<T>::~AVL_tree() {
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
}

template<typename T>
int AVL_tree<T>::height(node <T> *node) const {
    if (node == nullptr) {
        return 0;
    }

    return std::max<int>(height(node->left), height(node->right)) + 1;
}

template<typename T>
bool AVL_tree<T>::check() const {


    return check(this->root) && this->root->parent == nullptr;
}

template<typename T>
int AVL_tree<T>::height() const {
    return height(this->root);
}

template<typename T>
bool AVL_tree<T>::check(node <T> *node) const {
    int bf2 = 0;
    if (node->left) {
        if (node->left->parent != node) {
            printf("Bad parent\n");
            return false;
        }

        if (!check(node->left)) {
            return false;
        }
        bf2 -= height(node->left);
    }
    if (node->right) {
        if (node->right->parent != node) {
            printf("Bad parent\n");
            return false;
        }

        if (!check(node->right)) {
            return false;
        }
        bf2 += height(node->right);
    }
    if (!(node->left || node->right)) {
        if (node->bf != 0) {
            printf("Bad end of bf\n");
            return false;
        }
    }

    if (bf2 != node->bf) {
        printf("Bad bf:%i\n", node->value);
        return false;
    }

    return true;


}

template<typename T>
void AVL_tree<T>::bf_recalculate_down(node <T> *node) {

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

template<typename T>
int AVL_tree<T>::how_height(node <T> *node) const {

    int32_t i = 0;

    while (node->parent) {
        node = node->parent;
        ++i;
    }

    return i;
}


#endif //AVL_TREE_AVL_TREE_H
