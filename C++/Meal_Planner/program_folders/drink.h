#ifndef DRINK_H
#define DRINK_H

#include "menuitem.h"
#include <iostream>

class Drink : public MenuItem {  // inheritance
    private:
        int volume;        
        int sugar_content;  
        std::string type;        
    public:    
        Drink(std::string _name, double _price, int _calories, int _volume, int _sugar_content) 
            : MenuItem(_name, _price, _calories), volume(_volume), sugar_content(_sugar_content), type("drink") { }
        Drink(const Drink& other) : MenuItem(other) {            
            volume = other.volume;
            sugar_content = other.sugar_content;
            type = other.type;
        }
        ~Drink() {}
        std::string Get_type() const {
            return type;
        }
        std::string getName() const {
            return name;
        }
        int getVolume() const {
            return volume;
        }
        int getSugarContent() const {
            return sugar_content;
        }
        void DisplayInfo();  // polymorphism
};
#endif