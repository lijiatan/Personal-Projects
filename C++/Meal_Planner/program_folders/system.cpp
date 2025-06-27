#include <iostream>


void nextline(){
    std::cout << "\n";
}

void clearScreen() {    
    system("cls");
}

void pause() {
    system("pause");
}

int random(int min, int max) {
    // Generate random number in range [min, max]
    return min + (std::rand() % (max - min + 1));
}