#include "food.h"
#include <iostream>

void Food::DisplayInfo() {
    std::cout << "----- Food Info -----\n";
    std::cout << "Name       : " << name << "\n";
    std::cout << "Price      : $" << price << "\n";
    std::cout << "Calories   : " << calories << " kcal\n";
    std::cout << "Ingredients: " << ingredients << "\n";
    std::cout << "Vitamin    : " << vitamin << "\n";

    std::cout << "Nutrients:\n";
    std::cout << "  - Carbohydrates: " << nutrient[0] << " g\n";
    std::cout << "  - Fiber        : " << nutrient[1] << " g\n";
    std::cout << "  - Protein      : " << nutrient[2] << " g\n";
    std::cout << "  - Fat          : " << nutrient[3] << " g\n";

    std::cout << "--------------------------\n";
}
