//
// Created by MacBook on 06.03.2018.
//

#include "AVL_tree.h"

inline std::string wypisz(std::string &str, const char &znak = ' ') {
    std::string result;

    std::size_t found = str.find(znak); //pierwszy znak liczac od 0

    if (found != std::string::npos) {
        result.insert(0, str, 0, found); //na pozycji 0 umieszcza str od 0(liczy od 0) do found(liczy od 1)
        str.erase(0, found + 1);
    } else {
        result = str;
        str.clear();
    }

    return result;
}

int main() {
    AVL_tree<int, int> m;

    while (true) {
        char tab[255];

        scanf("%254[^\n]%*c", tab);
        std::string str = tab;

        std::string command;

        command = wypisz(str);

        if (command == "e") {
            break;
        } else if (command == "a") {
            int i = atoi(str.c_str());

            m[i] = 0;
        } else if (command == "r") {
            int i = atoi(str.c_str());

            m.erase(i);
        } else if (command == "p") {
            m.print();
        } else if (command == "h") {
            printf("%i\n", m.height());
        }
    }


    return 0;
}