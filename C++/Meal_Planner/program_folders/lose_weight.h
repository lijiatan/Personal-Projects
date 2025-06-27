#ifndef LOSE_WEIGHT_H
#define LOSE_WEIGHT_H

#include "nutritionist.h"
#include <vector>
#include "user.h" 


class lose_weight : public Nutritionist{  // inheritance
    public:

        lose_weight(std::string _name, std::string _expertise_in) : Nutritionist(_name, _expertise_in) {};
        
        ~lose_weight(){};

        void analyze_plan(User &);  //asoociation // polymorphism
};




#endif