#include <iostream>
#include <vector>
#include <iomanip> 
#include "menuitem.h"
#include "mealplan.h"
#include "food.h"
#include "drink.h"
#include "system.h"


std::vector<MenuItem*>& MealPlan::getMealListByType(){
    if(meal_type == 3){return breakfast;} // breakfast is a vector
    else if(meal_type == 2){return lunch;} // lunch is a vector
    else{return dinner;};
}

// this class will only use the amount of meal_count it receives and does not count how much meal can fit it
// it has feature to prevent over calories and budget
void MealPlan::Shuffle(std::vector<MenuItem*> &list_of_food, std::vector<MenuItem*> &list_of_drink, int meal_count){
    // why not just get a copy of the list_of_food and list_of_drink?
    // because copying a list of object food and drink is too much memory
    
    const int max_tries = 100;
    // more tries higher chance to get combination

    bool combination_found = false;

    double budget_in_a_meal = 0;
    int calories_in_a_meal = 0;


    for(int i = 0; i < max_tries; i++){

        int current_food_count = 0;
        int current_drink_count = 0;

        if(meal_count <= 0){
            std::cout << "no plan is choosen\n";
            return;
        }
        
        // reset the list if it's not empty
        getMealListByType().clear();

        // reset the calculated budget and calories from previous meal
        budget_in_a_meal = 0;
        calories_in_a_meal = 0;
        
        int calories = daily_calories / 3;
        double budget = daily_budget / 3;

        int food_varieties = list_of_food.size();
        int drink_varieties = list_of_drink.size();
        
        // Always get a drink
        MenuItem *drink = list_of_drink[rand() % drink_varieties];
        // check if enough budget or reach over calories
        if ((calories - drink->getCalories()) < 0 || (budget - drink->getPrice()) < 0){

        }
        else{

            Drink* drink_ptr = dynamic_cast<Drink*>(drink);
            if (drink_ptr) {
                getMealListByType().push_back(new Drink(*drink_ptr));
                current_drink_count++;
            }
        
            calories -= drink->getCalories();
            calories_in_a_meal += drink->getCalories();
            budget -= drink->getPrice();
            budget_in_a_meal += drink->getPrice();
        }

        for (int i = 0; i < meal_count - 1; i++) {

            // Try adding a food
            MenuItem* food = list_of_food[rand() % food_varieties];
            
            if ((calories - food->getCalories()) < 0 || (budget - food->getPrice()) < 0){
                continue;
            }
            else{

                Food* food_ptr = dynamic_cast<Food*>(food); // make the menuitem become food
                if (food_ptr) {
                    getMealListByType().push_back(new Food(*food_ptr)); //deep copy the food object
                    current_food_count++;
                }
                calories -= food->getCalories();
                calories_in_a_meal += food->getCalories();
                budget -= food->getPrice();
                budget_in_a_meal += food->getPrice();
            }
        }

        // = 0 plan achieve
        // > 0 means drink count or food count is low
        // probably not enough budget or calories
        // < 0 not possible

        if(!(meal_count - current_drink_count - current_food_count == 0)){
            combination_found = false;
        }
        else{
            combination_found = true;
            break;
        }
    }

    std::cout << "Selected Food For ";

    if(meal_type == 3) std::cout << "breakfast\n";
    else if(meal_type == 2) std::cout << "lunch\n";
    else if(meal_type == 1) std::cout << "dinner\n";

    for (MenuItem* item : getMealListByType()) {
        std::cout << "- " << item->getName() <<"\n";
    }

    std::cout << "Total Calories: " << calories_in_a_meal << "\n";
    std::cout << "Total Price: " << budget_in_a_meal << "\n\n";
    
    if(!combination_found){
        std::cout << "Your budget or calories is not enough for " << meal_count << " of food, consider to remove a food item (enter option 2)\n";
    }
}

void MealPlan::Add_Meal(std::vector<MenuItem*> &list_of_food, std::vector<MenuItem*> &list_of_drink, int meal_count){
    Shuffle(list_of_food, list_of_drink, meal_count);
};
void MealPlan::Remove_Meal(std::vector<MenuItem*> &list_of_food, std::vector<MenuItem*> &list_of_drink, int meal_count){
    Shuffle(list_of_food, list_of_drink, meal_count);
}; 


void MealPlan::Browse_Menu(std::vector<MenuItem*> &list_of_food, std::vector<MenuItem*> &list_of_drink) {

    bool quit = false;
    std::cout << "=========== \033[33mAvailable Menu Items\033[0m ===========\n\n";
    std::cout << std::left << std::setw(44) << "\033[36m-- Drinks --\033[0m"
              << "\033[31m-- Foods --\033[0m" << "\n";

    int max_size = std::max(list_of_drink.size(), list_of_food.size());

    for (int i = 0; i < max_size; ++i) { // loop count depends on the larger list, prevent any object didn't get printed

        if (i < list_of_drink.size()) {  // only print when the size is smaller, prevent out of range index fetching
            std::cout << "\033[36m" << std::setw(3) << (i + 1) << ". " 
                      << std::setw(30) << list_of_drink[i]->getName() << "\033[0m";
        } else {
            std::cout << std::setw(35) << " ";  // empty column
        }

        if (i < list_of_food.size()) {
            std::cout << "\033[31m" << std::setw(3) << (i + 1) << ". " 
                      << list_of_food[i]->getName() << "\033[0m";
        }

        std::cout << "\n";
    }
    std::cout << "\n=========================================\n";

    while (!quit) {
        int main_choice;
        int index;
        std::cout << "\nWhat would you like to do?\n";
        std::cout << "1. Browse drink\n";
        std::cout << "2. Browse food\n";
        std::cout << "3. Quit\n";
        std::cout << "Enter your choice: ";
        std::cin >> main_choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }


        switch (main_choice) {
            case 1: 
                std::cout << "Enter the index of the drink: ";
                std::cin >> index;
                nextline();
                if (std::cin.fail() || index < 1 || index > list_of_drink.size()) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << "Invalid index.\n";
                } else {
                    list_of_drink[index - 1]->DisplayInfo(); // index - 1 because vector starts from 0
                }
                break;
            case 2: 
                std::cout << "Enter the index of the food: ";
                std::cin >> index;
                nextline();

                if (std::cin.fail() || index < 1 || index > list_of_food.size()) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << "Invalid index.\n";
                } else {
                    list_of_food[index - 1]->DisplayInfo();
                }
                break;

            case 3:
                quit = true;
                std::cout << "Exiting browse menu.\n";
                break;
            
            default:
                std::cout << "Please enter a valid option (1-3).\n";
                break;
        }
    }
}

void MealPlan::Continue(std::vector<MenuItem*> &list_of_food, std::vector<MenuItem*> &list_of_drink, int meal_count, bool shuffle){

    this->meal_type -= 1;
    if(shuffle){
        Shuffle(list_of_food, list_of_drink, meal_count);
    }
};

int MealPlan::planning_ui(){
    int choice = 0;
    std::cout << "1. Add Meal" << "\n";     // done
    std::cout << "2. Remove Meal" << "\n";  // done
    std::cout << "3. Browse Menu" << "\n"; // done
    std::cout << "4. Shuffle" << "\n";    // done
    std::cout << "5. continue" << "\n\n";  // done
    std::cin >> choice;
    clearScreen();    
    return choice;
}