#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    char*** carrot;
    carrot = new char**;
    char** brocoli;
    brocoli = new char*;
    char* tomato;
    tomato = new char;
    *tomato = 'z';
    *brocoli = tomato;
    *carrot = brocoli;
    char radish;
    radish = 'q';
    return 0;
}
