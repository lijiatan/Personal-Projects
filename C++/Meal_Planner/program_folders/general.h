#ifndef GENERAL_H
#define GENERAL_H

#include "nutritionist.h"
#include <vector>
#include "mealplan.h"

class general : public Nutritionist {  // inheritance
    private:
    protected:
    public:
        general(std::string _name, std::string _expertise_in) : Nutritionist(_name, _expertise_in) {};
        ~general(){};

        void analyze_plan(User &);   // polymorphism  // Association
};
#endif  