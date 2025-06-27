#ifndef FOOD_H
#define FOOD_H

#include "menuitem.h"
#include <string>
#include <iostream>

class Food : public MenuItem {  // inheritance
    private:
        
        std::string ingredients;
        std::string type;
        std::string vitamin;
        double nutrient[4];


    public:

        Food(std::string _name, double _price, int _calories, double _nutrient[4], std::string _ingredients, std::string _vitamin)
            : MenuItem(_name, _price, _calories), ingredients(_ingredients), vitamin(_vitamin), type("food") {
            for(int i = 0; i < 4; i++){
                nutrient[i] = _nutrient[i];
            }
        }

            // Copy constructor
        Food(const Food& other) : MenuItem(other) {
            for (int i = 0; i < 4; i++) nutrient[i] = other.nutrient[i];
            vitamin = other.vitamin;
            ingredients = other.ingredients;
        }

        ~Food(){}

        std::string Get_type() const {
            return type;
        }

        std::string getName() const {
            return name;
        }

        const double* getNutrients() const {
            return nutrient; // returns pointer to the array
        }

        std::string GetVitamin() const {
            return vitamin;
        }

        std::string GetIngredients() const {
            return ingredients;
        }

        void DisplayInfo();  // polymorphism

    };

#endif