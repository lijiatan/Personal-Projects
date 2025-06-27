#include <filesystem>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "file_operation.h"
#include "mealplanner.h"
#include "drink.h"
#include "food.h"
#include "user.h"

void file_operation::read_plan(std::string path, MealPlan &the_plan){
    std::fstream file(path, std::ios::in);

    // first read budget and calories
    std::string name, line, vitamin, ingredients, type;
    double price = 0;
    int calories = 0, volume = 0, sugar = 0;
    double nutrients[4] = {0}; //initialize the array with 0

    int end_count = 3; // a counting variable to determine when is the end of a meal plan
    
    std::getline(file, line);  // getting the string budget
    price = std::stod(line);   // convert to double
    std::getline(file, line);   // getting the string calories
    calories = std::stoi(line);  // convert to int
    
    the_plan.setbudget(price);  // beware, using same variable for food calories and total calories
    the_plan.setCalories(calories);

    while (end_count != 0) {  // stop when count = 3
        // start to read breakfast, lunch and dinner
        std::getline(file, type);
        if(type == "food"){
            // name
            std::getline(file, name);
            // price
            std::getline(file, line);
            price = std::stod(line);
            // calories 
            std::getline(file, line);
            calories = std::stoi(line);
            // nutrients
            for(int i = 0; i < 4; i++){
                std::getline(file, line);
                nutrients[i] = std::stoi(line);
            }
            std::getline(file, vitamin);
            std::getline(file, ingredients);
            std::getline(file, line); // Skip blank line (separator)

            Food *new_food = new Food(name, price, calories, nutrients, ingredients, vitamin);
            the_plan.getMealListByType().push_back(new_food);

        }
        else if (type == "drink") {
            // name
            std::getline(file, name);

            // price
            std::getline(file, line);
            price = std::stod(line);

            // calories
            std::getline(file, line);
            calories = std::stoi(line);

            // volume
            std::getline(file, line);
            volume = std::stoi(line);

            // sugar
            std::getline(file, line);
            sugar = std::stoi(line);

            std::getline(file, line); // Skip blank line (separator)

            Drink* new_drink = new Drink(name, price, calories, volume, sugar);
            the_plan.getMealListByType().push_back(new_drink);

        }
        
        else{  
            // this statement means that END is meet
            end_count--;
            the_plan.setMealtype(end_count); // change the type of meal, from breakfast vector to lunch vector 
            std::getline(file, line); // Skip reading another blank line (separator)
        }
    }
    file.close();
    the_plan.setMealtype(3);  // do not remove, set it back to normal
}


void file_operation::read_menu(std::string path, std::vector<MenuItem*>& a_list, const std::string &type) {
    // Resolve full file path
    std::string full_path = std::filesystem::current_path().string() + path;

    // open file
    std::fstream file(full_path, std::ios::in);

    std::string name, line, vitamin, ingredients;
    double price = 0;
    int calories = 0, volume = 0, sugar = 0;
    double nutrients[4] = {0}; //initialize the array with 0

    if (type == "drink") {
        while (std::getline(file, name)) {
            std::getline(file, line);
            price = std::stod(line); // Convert string to double

            std::getline(file, line);
            calories = std::stoi(line);

            std::getline(file, line);
            volume = std::stoi(line);

            std::getline(file, line);
            sugar = std::stoi(line);

            std::getline(file, line); // Skip blank line (separator)
            
            a_list.push_back(new Drink(name, price, calories, volume, sugar));  //tips
        }
    }
    else if(type == "food"){
        // fetch the food data
        while (std::getline(file, name)) {
            std::getline(file, line);
            price = std::stod(line);  //double
            
            std::getline(file, line); 
            calories = std::stoi(line); // int

            for(int i = 0; i < 4; i++){
                std::getline(file, line);
                nutrients[i] = std::stoi(line);
            }

            std::getline(file, vitamin);
            std::getline(file, ingredients);
            std::getline(file, line); // Skip blank line (separator)

            //make new food object and put inside the list
            a_list.push_back(new Food(name, price, calories, nutrients, ingredients, vitamin));             
        }

    }
    file.close();
}


void file_operation::read_user_info(User *the_user, std::string path) {
    std::fstream text_file(path, std::ios::in); // Open in read mode
    std::string line;

    int line_count = 0;
    std::getline(text_file, line);
    the_user->setUsername(line);

    std::getline(text_file, line);
    the_user->setPassword(line);

    std::getline(text_file, line);
    the_user->setGender(line);

    text_file.close();
}

bool file_operation::check_exists(std::string remaining_path)
{
    std::filesystem::path user_login_data = std::filesystem::current_path() / remaining_path;

    if (!std::filesystem::exists(user_login_data)){
        return false;
    }
    return true;
}

void file_operation::make_directory(const std::string &path, const std::string &name)
{
    std::string folderName = name;
    std::filesystem::path fullPath = std::filesystem::path(path) / folderName;

    try{
        // even if user deleted .Users folder, we will create it again
        if (!std::filesystem::exists(path))
        {
            std::filesystem::create_directory(path);
        }

        // Create .Users/username directory
        std::filesystem::create_directory(fullPath);
    }
    catch (std::filesystem::filesystem_error &e)
    {
        std::cout << "Filesystem error creating directory: " << e.what() << "\n";
        throw e;  // Re-throw the original exception
    }
}

void file_operation::create_user_folder(std::string &username){
    std::filesystem::path User_directory_path = std::filesystem::current_path() / ".Users";
    make_directory(User_directory_path.string(), username);
}

void file_operation::writeMealItemsToFile(std::ofstream &outFile, std::vector<MenuItem*> &mealList) {
    
    for (MenuItem* item : mealList) {
        
        Food* food_item = dynamic_cast<Food*>(item);
        if (food_item) {
            outFile << "food\n";
            outFile << food_item->getName() << "\n";
            outFile << food_item->getPrice() << "\n";
            outFile << food_item->getCalories() << "\n";

            const double* nutrients = food_item->getNutrients();
            for (int i = 0; i < 4; i++) {
                outFile << nutrients[i] << "\n";
            }

            outFile << food_item->GetVitamin() << "\n";
            outFile << food_item->GetIngredients() << "\n\n";
            continue; // move to next item
        }

        Drink* drink_item = dynamic_cast<Drink*>(item);
        if (drink_item) {
            outFile << "drink\n";
            outFile << drink_item->getName() << "\n";
            outFile << drink_item->getPrice() << "\n";
            outFile << drink_item->getCalories() << "\n";
            outFile << drink_item->getVolume() << "\n";
            outFile << drink_item->getSugarContent() << "\n\n";
        }
    }
    outFile << "END" << "\n";
    outFile << "\n";
}


void file_operation::record_day_plan(const std::string &path, MealPlan* the_plan) {
    std::ofstream outFile(path); // auto create text file if not exit

    outFile << the_plan->getDailybudget() << "\n";
    outFile << the_plan->getDailycalories() << "\n";    
    writeMealItemsToFile(outFile, the_plan->breakfast);
    writeMealItemsToFile(outFile, the_plan->lunch);
    writeMealItemsToFile(outFile, the_plan->dinner);
    outFile.close();                    
}



void file_operation::record_signinInfo(User *the_user, std::string &password){
    std::filesystem::path User_directory_path = std::filesystem::current_path() / ".LoginInfo";

    // incase .LoginInfo get deleted
    if (!std::filesystem::exists(User_directory_path)){
        std::filesystem::create_directory(User_directory_path);
    }

    // Build the full file path
    std::string username = (*the_user).getUsername();

    std::filesystem::path user_file_path = User_directory_path / (username + ".txt");

    // Check if file already exists
    if (std::filesystem::exists(user_file_path)){
        std::cout << "File already exists.\n";
        return;     
    }

    // Create and write to the file
    std::ofstream outFile(user_file_path);

    outFile << username << '\n';
    outFile << password << '\n';
    outFile << the_user->getGender() << '\n';

    outFile.close();
    std::cout << "User registered successfully.\n";
}