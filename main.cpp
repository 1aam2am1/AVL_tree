//
// Created by MacBook on 06.03.2018.
//

#include "AVL_tree.h"

int main() {
    AVL_tree<int> m;

    for (int32_t i = 0; i < 20; ++i) {
        m.push(i);

        if (!m.check()) {
            m.print();
            printf("%i\n", i);
            printf("ERROR");
            return 0;
        }
    }

    m.print();

    for (auto i : m) {
        printf("%i ", i);
    }

    for (int32_t i = 2000; i > 500; i -= 3) {
        m.remove(i);

        if (!m.check()) {
            m.print();
            printf("%i\n", i);
            printf("ERROR");
            return 0;
        }
    }


    return 0;
}