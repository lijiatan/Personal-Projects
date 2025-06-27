#include "drink.h"
#include <iostream>

void Drink::DisplayInfo() {
    std::cout << "----- Drink -----\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Price: " << price << "\n";
    std::cout << "Calories: " << calories << "\n";
    std::cout << "Sugar content (gram): " << sugar_content << "\n";
    std::cout << "volume (ml): " << volume << "\n\n";
}

