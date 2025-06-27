#ifndef USER_DATA_H
#define USER_DATA_H

#include "mealplan.h"
#include <vector>
#include <iostream>

class User_Data{
    private:
        std::vector<MealPlan> days_of_plans;  // composition (User_Data :Owner)
    protected:
    
    public: 
        
        std::vector<MealPlan> Get_plan() const {
            return days_of_plans;
        }

        void Add_plan(MealPlan &meal) {

            if (meal.breakfast.empty() && meal.lunch.empty() && meal.dinner.empty()) {
                return;
            }

            days_of_plans.push_back(meal);
        }

        void data_clear() {
            days_of_plans.clear();
        }
};






#endif