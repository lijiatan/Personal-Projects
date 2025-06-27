#ifndef MEALPLAN_H
#define MEALPLAN_H

#include <string>
#include <vector>

#include "menuitem.h"

class MealPlan{
    private:
              
        double daily_budget;
        int daily_calories;
        int meal_type;
    
    protected:
    
    public:

        const std::string daysOfWeek[7] = {"monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};

        std::vector<MenuItem*> breakfast;  // aggregation
        std::vector<MenuItem*> lunch; // aggregation
        std::vector<MenuItem*> dinner; // aggregation

        MealPlan(double _daily_budget = 0.0, int _daily_calories = 0)
            : daily_budget(_daily_budget), daily_calories(_daily_calories), meal_type(3), breakfast(),lunch(), dinner() {
        }

        ~MealPlan() {
            breakfast.clear(); 
            lunch.clear();
            dinner.clear();
        }


        double getDailybudget() const{
            return daily_budget;
        }

        void setbudget(const double &new_budget){
            daily_budget = new_budget;
        }

        int getDailycalories() const {
            return daily_calories;
        }

        void setCalories(const int &new_calories){
            daily_calories = new_calories;
        }

        int getMealtype() const {
            return meal_type;
        }

        void setMealtype(const int new_type){
            meal_type = new_type;
        }

        std::vector<MenuItem*>& getMealListByType();

        int planning_ui();

        void Add_Meal(std::vector<MenuItem*> &, std::vector<MenuItem*> &, int);
        void Remove_Meal(std::vector<MenuItem*> &, std::vector<MenuItem*> &, int);
        void Browse_Menu(std::vector<MenuItem*> &list_of_food, std::vector<MenuItem*> &list_of_drink);
        void Shuffle(std::vector<MenuItem*> &list_of_food, std::vector<MenuItem*> &list_of_drink, int meal_count);
        void Continue(std::vector<MenuItem*> &list_of_food, std::vector<MenuItem*> &list_of_drink, int meal_count,  bool shuffle);

};


#endif