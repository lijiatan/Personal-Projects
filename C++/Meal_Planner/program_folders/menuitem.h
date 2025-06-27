#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>

class MenuItem {  //abstract class, virtual function included 
protected:
    std::string name;
    int calories;
    double price;

public:
    MenuItem(std::string _name = "", double _price = 0.0, int _calories = 0) {
        this->name = _name;
        this->calories = _calories;
        this->price = _price;
    }

    virtual ~MenuItem() = default;

    virtual void DisplayInfo() = 0;

    virtual std::string Get_type() const = 0;


    // Getters
    std::string getName() const {
        return name;
    }

    int getCalories() const {
        return calories;
    }

    double getPrice() const {
        return price;
    }
};

#endif
