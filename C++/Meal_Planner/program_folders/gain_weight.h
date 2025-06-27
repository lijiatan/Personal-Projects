#ifndef GAIN_WEIGHT_H
#define GAIN_WEIGHT_H

#include "nutritionist.h"
#include <vector>
#include "user_data.h" 


class gain_weight : public Nutritionist{  // inheritance
    private:
    protected:
    public:
        gain_weight(std::string _name, std::string _expertise_in) : Nutritionist(_name, _expertise_in) {};
        ~gain_weight(){};

        void analyze_plan(User &);   // polymorphism // Association
};
#endif


