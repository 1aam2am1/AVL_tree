//
// Created by MacBook on 06.03.2018.
//

#include "AVL_tree.h"

int main() {
    AVL_tree<int, int> m;

    for (int32_t i = 0; i < 20; ++i) {
        m[i] = i;
    }

    m.print();

    for (auto i : m) {
        printf("%i ", i.first);
    }

    for (int32_t i = 2000; i > 500; i -= 3) {
        m.erase(i);
    }


    return 0;
}