#ifndef MEALPLANNER_H
#define MEALPLANNER_H

#include "file_operation.h"
#include "user.h"
#include "nutritionist.h"
#include <vector>
#include "menuitem.h"

class MealPlanner {
    private:
        User *the_user; // aggregation
        Nutritionist *nutritionist; // aggregation
        
    public:
    
        file_operation *Files; // aggregation
        std::vector<MenuItem*> list_of_drink; // aggregation
        std::vector<MenuItem*> list_of_food; // aggregation

        MealPlanner(file_operation* FilesPtr = nullptr, User *_user = nullptr) {
            this->Files = FilesPtr;  // store the reference (no copy)
            this->the_user = _user;
        }

        MealPlanner(){};
        
        ~MealPlanner() {
            // Delete user if exists
            if (the_user != nullptr) {
                delete the_user;
                the_user = nullptr;
            }
            
            // Free all dynamically allocated MenuItems in drink list
            for (MenuItem* item : list_of_drink) {
                delete item;
            }
            list_of_drink.clear();
            
            // Free all dynamically allocated MenuItems in food list
            for (MenuItem* item : list_of_food) {
                delete item;
            }
            list_of_food.clear();
        }
        
        
        void setUser(User* user) {
            the_user = user;  // store the reference (no copy)
        }   
        
        bool Login();
        bool SignUp();
        std::string Register();
        
        void main_interface();
        void analyze();

        void createNewPlan();
        
        void modifyPreviousPlan();
        
        void initialize_menu();
        void viewExistingPlan();
        void modify();
        void RenamePlan();
        void RemoveDay(); 
        void AddDay(); 

};


#endif