 #include <iostream>
#include <filesystem>
#include <fstream>
#include <map>
#include "system.h"
#include "mealplanner.h"
#include "file_operation.h"
#include "mealplan.h"
#include "gain_weight.h"
#include "lose_weight.h"
#include "general.h"

void MealPlanner::initialize_menu(){
    //fecth food and drink into the vector
    std::string path_drink = "./.Menu/drink.txt";
    std::string path_food ="./.Menu/food.txt";
    list_of_drink.clear();
    list_of_food.clear();
    Files->read_menu(path_drink, list_of_drink, "drink");
    Files->read_menu(path_food, list_of_food, "food");
}

void MealPlanner::analyze(){

    std::vector<std::string> plan_name;
    std::vector<std::string> a_list_of_plan;

    int directory_index;

    int choice = 0;

    // user path
    std::filesystem::path current_path = std::filesystem::current_path() / ".Users" / the_user->getUsername();

    // put all the file name inside a list

    std::cout << "Your existing plan:\n";

    int count = 1;
    for (const auto& folder : std::filesystem::directory_iterator(current_path)) {
        if (folder.is_directory()) {
            std::string folder_name = folder.path().filename().string();
            plan_name.push_back(folder_name);
            std::cout << count << ") " << folder_name << "\n";
            count++;
        }
    }

    std::cout << "Type the index to analyze: ";
    std::cin >> directory_index;

    if (directory_index <= 0 || directory_index > plan_name.size()) {
        std::cout << "Invalid index\n";
        pause();
        clearScreen();
        return; // Exit the function early
    }
    clearScreen();

    current_path = std::filesystem::current_path() / ".Users" / the_user->getUsername() / plan_name.at(directory_index - 1);
    
    for (const auto& folder : std::filesystem::directory_iterator(current_path)) {
        if (folder.path().extension() == ".txt") {
            a_list_of_plan.push_back(folder.path().filename().string());
        }
    }
    //user_data can be initialize here
    for(int i = 0; i < a_list_of_plan.size(); i++){
        
        current_path = std::filesystem::current_path()
            / ".Users"
            / the_user->getUsername()
            / plan_name.at(directory_index - 1)
            / (a_list_of_plan.at(i));
        
        MealPlan temp;

        Files->read_plan(current_path.string(), temp); // pass in a temp plan to be read

        the_user->getData().Add_plan(temp);
    }
    // std::cout << "initialize done\n\n\n";
        
    std::cout << "What is your goal ?\n";
    std::cout << "1. General\n";
    std::cout << "2. Lose Weight\n";
    std::cout << "3. Gain Weight\n";

    std::cin >> choice;
    clearScreen();


    switch (choice) {
        case 1:
            nutritionist = new general("Dr. Evans", "General");
            break;
        case 2:
            nutritionist = new lose_weight("Dr. Chen", "lose weight");
            // lose weight
            break;
        case 3:
            nutritionist = new gain_weight("Dr. Rodriguez", "gain weight");
            // gain weight
            break;
        default:
            std::cout << "Invalid index\n";
            pause();
            clearScreen();
            return;
    }
    std::cout << nutritionist->get_name() << "is analyzing your plan [" << plan_name.at(directory_index - 1) << "]\n"; 
    nutritionist->analyze_plan(*the_user);
    pause();
    clearScreen();
    delete nutritionist;
    nutritionist = nullptr;
}

void MealPlanner::createNewPlan(){

    MealPlan *new_plan;
    std::string plan_name;        
    std::string folder_path;    

    int choice = 0;
    int budget = 0;
    int calories = 0;
    int days = 0;
    bool allValid;
    bool found_combination;
    int total_budget = 0;

    while (!allValid) {
        std::cout << "Please enter:\n";
        std::cout << "Please give a name for your plan (no space): ";
        std::cin >> plan_name;

        std::cout << "1. Your budget in a day: ";
        std::cin >> budget;

        std::cout << "2. Your daily calories intake: ";
        std::cin >> calories;

        std::cout << "3. How many days you want to plan (1-7): ";
        std::cin >> days;

        std::cin.ignore(); // Clear input buffer just in case   

        // Validate
        bool budgetValid = budget > 0;
        bool caloriesValid = calories > 0;
        bool daysValid = (days >= 1) && (days <= 7);
        bool nameValid = !plan_name.empty();

        if (!budgetValid) std::cout << "Invalid budget (must be positive)\n";
        if (!caloriesValid) std::cout << "Invalid calories (must be positive)\n";
        if (!daysValid) std::cout << "Invalid days (must be 1-7)\n";
        if (!nameValid) std::cout << "Name cannot be empty\n";

        allValid = budgetValid && caloriesValid && daysValid && nameValid;

        if (!allValid) {
            std::cout << "Please correct the errors and try again.\n\n";
        }
    }

    // to be modified better
    int max_food_count = (calories / 329) / 3;  //estimating breakfast, lunch or dinner is 329 calories

    //the first path is to make the directory, only create once
    folder_path = (std::filesystem::current_path() / ".Users" / the_user->getUsername()).string();
    try{
        Files->make_directory(folder_path, plan_name);
    }
    catch(std::filesystem::filesystem_error &e){
        throw e;
    }
    clearScreen();
    std::cout << "Your plan name is: " << plan_name << "\n\n";

    for(int i = 0; i < days; i++){
        // note, once the plan is done, new_plan can be clean up
        new_plan = new MealPlan(budget, calories);

        // this second path is state where the day path should be
        folder_path = (std::filesystem::current_path() / ".Users" / the_user->getUsername() / plan_name /"").string();
        // now the path 
        

        new_plan->Shuffle(list_of_food, list_of_drink, max_food_count); 
        // now that the price is for one day, but all were used in one list
        // the calories is for one day too, but all were used in one list

        do{
            choice = new_plan->planning_ui();  // this display the interface of add meal, remove meal . . .
            switch (choice){
                case 1:        
                    new_plan->Add_Meal(list_of_food, list_of_drink, ++max_food_count);        
                    break;
                case 2:
                    new_plan->Remove_Meal(list_of_food, list_of_drink, --max_food_count);
                    break;
                case 3:
                    new_plan->Browse_Menu(list_of_food, list_of_drink);
                    break;
                case 4:
                    // need to use number to determine to shuffel breakfast lunch, or dinner
                    // if shuffle again, the budget need to be reset
                    new_plan->Shuffle(list_of_food, list_of_drink, max_food_count);
                
                    break;
                case 5:                
                    new_plan->Continue(list_of_food, list_of_drink, max_food_count, true);
                    break;
                default:
                    std::cout << "Invalid choice, please choose again\n";
                    break;
            }
        } while (new_plan->getMealtype() > 0);

        clearScreen();
        // the whole path Meal_Planner\.Users\bob\money_saving\monday.txt
        std::filesystem::path day_file_path = std::filesystem::current_path() / ".Users" / the_user->getUsername() / plan_name / (new_plan->daysOfWeek[i] + ".txt");
        Files->record_day_plan(day_file_path.string(), new_plan);
        delete new_plan;
        new_plan = nullptr;
    }   
}

void MealPlanner::modifyPreviousPlan(){

    std::vector<std::string> plan_name;
    std::vector<std::string> a_list_of_plan;

    int directory_index;
    int day_index;

    int choice = 0;

    // user path
    std::filesystem::path current_path = std::filesystem::current_path() / ".Users" / the_user->getUsername();

    // put all the file name inside a list

    std::cout << "Your existing plan:\n";

    int count = 1;
    for (const auto& folder : std::filesystem::directory_iterator(current_path)) {
        if (folder.is_directory()) {
            std::string folder_name = folder.path().filename().string();
            plan_name.push_back(folder_name);
            std::cout << count << ") " << folder_name << "\n";
            count++;
        }
    }

    std::cout << "Type the index to modify: ";
    std::cin >> directory_index;
    

    if (directory_index <= 0 || directory_index > plan_name.size()) {
        std::cout << "Invalid index\n";
        pause();
        clearScreen();
        return; // Exit the function early
    }

    clearScreen();

    // get user plan path
    current_path = std::filesystem::current_path() / ".Users" / the_user->getUsername() / plan_name.at(directory_index - 1);
    
    count = 1;
    for (const auto& folder : std::filesystem::directory_iterator(current_path)) {
        if (folder.path().extension() == ".txt") {
            std::cout << count << ")" << folder.path().filename().string() << "\n";
            a_list_of_plan.push_back(folder.path().filename().string());
            count++;
        }
    }

    std::cout << "Type the index to modified: ";
    std::cin >> day_index;

    if (day_index <= 0 || day_index > a_list_of_plan.size()){
        std::cout << "Invalid index\n";
        pause();
        clearScreen();

        return;
    }
    clearScreen();
    current_path = std::filesystem::current_path()
               / ".Users"
               / the_user->getUsername()
               / plan_name.at(directory_index - 1)
               / (a_list_of_plan.at(day_index - 1));

    // read the budget and colories first
    MealPlan *new_plan = new MealPlan();
    Files->read_plan(current_path.string(), *new_plan); // pass in the original plan
    
    int max_food_count = (new_plan->getDailycalories() / 329) / 3;

    do{
        int calories_in_a_meal = 0;
        double budget_in_a_meal = 0;
        std::cout << "Your previous plan for ";

        if(new_plan->getMealtype() == 3) std::cout << "breakfast\n";
        else if(new_plan->getMealtype() == 2) std::cout << "lunch\n";
        else if(new_plan->getMealtype() == 1) std::cout << "dinner\n";

        
        for (MenuItem* item : new_plan->getMealListByType()) {
            std::cout << "- " << item->getName() <<"\n";
            calories_in_a_meal += item->getCalories();
            budget_in_a_meal += item->getPrice();
        }

        std::cout << "Total Calories: " << calories_in_a_meal << "\n";
        std::cout << "Total Price: " << budget_in_a_meal << "\n\n";

        choice = new_plan->planning_ui();  // this display the interface of add meal, remove meal . . .

        switch (choice){
            case 1:        
                new_plan->Add_Meal(list_of_food, list_of_drink, ++max_food_count);        
                break;
            case 2:
                new_plan->Remove_Meal(list_of_food, list_of_drink, --max_food_count);
                break;
            case 3:
                new_plan->Browse_Menu(list_of_food, list_of_drink);
                break;
            case 4:
                // need to use number to determine to shuffel breakfast lunch, or dinner
                // if shuffle again, the budget need to be reset
                new_plan->Shuffle(list_of_food, list_of_drink, max_food_count);
            
                break;
            case 5:                
                new_plan->Continue(list_of_food, list_of_drink, max_food_count, false);
                break;
            default:
                std::cout << "Invalid choice, please choose again\n";
                break;
        }
    } while (new_plan->getMealtype() > 0);
  
    Files->record_day_plan(current_path.string(), new_plan);

    delete new_plan;
    new_plan = nullptr;
}

void MealPlanner::RenamePlan(){
    // print all the folder inside the directory
    std::vector<std::string> plan_name;
    int directory_index;
    int choice = 0;
    // user path
    std::filesystem::path current_path = std::filesystem::current_path() / ".Users" / the_user->getUsername();
    // put all the file name inside a list
    std::cout << "Your existing plan:\n";

    int count = 1;
    for (const auto& folder : std::filesystem::directory_iterator(current_path)) {
        if (folder.is_directory()) {
            std::string folder_name = folder.path().filename().string();
            plan_name.push_back(folder_name);
            std::cout << count << ") " << folder_name << "\n";
            count++;
        }
    }
    std::string new_name;
    std::cout << "Choose the folder index to rename: ";
    std::cin >> directory_index;

    if(directory_index - 1 > plan_name.size() || (directory_index - 1) < 0){
        std::cout << "Invalid Index\n";
        return;
    }

    std::cout << "Enter new name for the plan: ";
    std::cin >> new_name;

    std::string old_name = plan_name.at(directory_index - 1);

    std::filesystem::path old_path = std::filesystem::current_path() / ".Users" / the_user->getUsername() / plan_name.at(directory_index - 1);
    std::filesystem::path new_path = std::filesystem::current_path() / ".Users" / the_user->getUsername() / new_name;

    try {
        // Rename the folder
        std::filesystem::rename(old_path, new_path);
        std::cout << "Successfully renamed '" << old_name << "' to '" << new_name << "'\n";
    } catch (std::filesystem::filesystem_error& e) {
        std::cerr << "Error renaming folder: " << e.what() << "\n";
        throw e;
    }
    pause();
}

void MealPlanner::AddDay(){
    clearScreen();
    //check which day isn't created yet
    //create it with number
    std::vector<std::string> plan_name;
    std::vector<std::string> a_list_of_plan;

    int directory_index;
    int day_index;

    int choice = 0;

    // user path
    std::filesystem::path current_path = std::filesystem::current_path() / ".Users" / the_user->getUsername();

    // put all the file name inside a list

    std::cout << "Your existing plan:\n";

    int count = 1;
    for (const auto& folder : std::filesystem::directory_iterator(current_path)) {
        if (folder.is_directory()) {
            std::string folder_name = folder.path().filename().string();
            plan_name.push_back(folder_name);
            std::cout << count << ") " << folder_name << "\n";
            count++;
        }
    }

    std::cout << "Type the index to add: ";
    std::cin >> directory_index;
    clearScreen();

    if (directory_index <= 0 || directory_index > plan_name.size()) {
        std::cout << "Invalid index\n";
        pause();
        clearScreen();
        return; // Exit the function early
    }

    // get user plan path
    current_path = std::filesystem::current_path() / ".Users" / the_user->getUsername() / plan_name.at(directory_index - 1);
    
    bool daysFound[7] = {false};

    std::map<std::string, int> dayMap = {
        {"monday.txt", 0},
        {"tuesday.txt", 1},
        {"wednesday.txt", 2},
        {"thursday.txt", 3},
        {"friday.txt", 4},
        {"saturday.txt", 5},
        {"sunday.txt", 6}
    };

    // a logic to check which file does not exists
    std::cout << "Files inside your " << plan_name.at(directory_index - 1) << "\n\n";
    for (const auto& folder : std::filesystem::directory_iterator(current_path)) {
        if (folder.path().extension() == ".txt") {
            auto it = dayMap.find(folder.path().filename().string());
            if (it != dayMap.end()) {
                std::cout << it->first <<" plan found\n";
                daysFound[(*it).second] = true;  // Mark this day as found
            }
        }
    }
    nextline();

    bool allPresent = true;
    for(int i = 0; i < 7; i++) {
        if(!daysFound[i]) {  // if find one of the days is not exists, the program continue
            allPresent = false;
            break;
        }
    }

    if(allPresent) {
        std::cout << "This plan has reach maximum days (cannot add more days)!\n";
        pause();
        clearScreen();
        return;
    } else {
        std::cout << "Missing days:\n";
        for(int i = 0; i < 7; i++) {
            if(!daysFound[i]) {
                // Find the day name with value == i
                for(const auto& [day, value] : dayMap) {   // like for key, value in pairs
                    if(value == i) {
                        std::cout << i + 1 << ") " << day << "\n";
                        break;
                    }
                }
            }
        }
    }

    std::cout << "Type the index to add: ";
    std::cin >> day_index;

    if(daysFound[day_index - 1]){
        std::cout << "Day already exists\n";
        pause();
        clearScreen();
        return;
    }
    clearScreen();

    // Find the day name with value == day_index - 1
    for(const auto& [day, value] : dayMap) {
        if(value == day_index - 1) {
            current_path = std::filesystem::current_path()
                       / ".Users"
                       / the_user->getUsername()
                       / plan_name.at(directory_index - 1)
                       / day;
        }
    }
    //create the file and ask the budget and calories
    double budget;
    std::cout << "1. Your budget in a day: ";
    std::cin >> budget;
    int calories;
    std::cout << "2. Your daily calories intake: ";
    std::cin >> calories;   
    MealPlan *a_temp_plan = new MealPlan();
    a_temp_plan->setbudget(budget);
    a_temp_plan->setCalories(calories);
    Files->record_day_plan(current_path.string(), a_temp_plan);
    std::cout << "your day successfully created, remember to modify it\n";
    pause();
    clearScreen();
    delete a_temp_plan;
    a_temp_plan = nullptr;
}

void MealPlanner::RemoveDay(){
    std::vector<std::string> plan_name;
    std::vector<std::string> a_list_of_plan;

    int directory_index;
    int day_index;

    int choice = 0;

    // user path
    std::filesystem::path current_path = std::filesystem::current_path() / ".Users" / the_user->getUsername();

    // put all the file name inside a list

    std::cout << "Your existing plan:\n";

    int count = 1;
    for (const auto& folder : std::filesystem::directory_iterator(current_path)) {
        if (folder.is_directory()) {
            std::string folder_name = folder.path().filename().string();
            plan_name.push_back(folder_name);
            std::cout << count << ") " << folder_name << "\n";
            count++;
        }
    }

    std::cout << "Type the index to modify: ";
    std::cin >> directory_index;

    if (directory_index <= 0 || directory_index > plan_name.size()) {
        std::cout << "Invalid index\n";
        pause();
        clearScreen();
        return; // Exit the function early
    }

    clearScreen();
    // get user plan path
    current_path = std::filesystem::current_path() / ".Users" / the_user->getUsername() / plan_name.at(directory_index - 1);
    
    count = 1;
    for (const auto& folder : std::filesystem::directory_iterator(current_path)) {
        if (folder.path().extension() == ".txt") {
            std::cout << count << ")" << folder.path().filename().string() << "\n";
            a_list_of_plan.push_back(folder.path().filename().string());
            count++;
        }
    }

    std::cout << "Type the index to delete: ";
    std::cin >> day_index;

    if (day_index <= 0 || day_index > a_list_of_plan.size()){
        std::cout << "Ivalid index\n";
        return;
    }

    current_path = std::filesystem::current_path()
               / ".Users"
               / the_user->getUsername()
               / plan_name.at(directory_index - 1)
               / (a_list_of_plan.at(day_index - 1));

    std::filesystem::remove(current_path);
    std::cout << "successfully removed\n";
}

void MealPlanner::modify(){
    int choice;

    while(true){ // Loop indefinitely until the user chooses to exit
        std::cout << "--- Modify Meal Plan ---\n"; // Added a heading for clarity
        std::cout << "1. Rename Plan\n";
        std::cout << "2. Remove day\n";
        std::cout << "3. Add day\n";
        std::cout << "4. Modify existing plan\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: "; // Prompt for user input
        std::cin >> choice;
        clearScreen();
        if(choice == 1){
            try{
                RenamePlan();
            }
            catch(std::filesystem::filesystem_error &e){
                std::cout << "\nThis name has been used for other file, use another name instead\n";
                return;
            }
        } else if (choice == 2){
            RemoveDay(); 
        } else if (choice == 3){
            AddDay(); 
        } else if (choice == 4){
            modifyPreviousPlan();
        } else if (choice == 5){
            std::cout << "Exiting modification menu.\n";
            break; 
        }
        clearScreen();
    }
}

void MealPlanner::viewExistingPlan(){
    // print all the days in the plan
    // ask user for which plan
    std::vector<std::string> plan_name;
    std::vector<std::string> a_list_of_plan;

    int directory_index;
    int choice = 0;

    // user path
    std::filesystem::path current_path = std::filesystem::current_path() / ".Users" / the_user->getUsername();

    // put all the file name inside a list
    std::cout << "Your existing plan:\n";

    int count = 1;
    for (const auto& folder : std::filesystem::directory_iterator(current_path)) {
        if (folder.is_directory()) {
            std::string folder_name = folder.path().filename().string();
            plan_name.push_back(folder_name);
            std::cout << count << ") " << folder_name << "\n";
            count++;
        }
    }

    std::cout << "Type the index to view: ";
    std::cin >> directory_index;
    clearScreen();


    if (directory_index <= 0 || directory_index > plan_name.size()) {
        std::cout << "Invalid index\n";
        return; // Exit the function early
    }

    // get user plan path
    current_path = std::filesystem::current_path() / ".Users" / the_user->getUsername() / plan_name.at(directory_index - 1);
    
    for (const auto& folder : std::filesystem::directory_iterator(current_path)) {
        if (folder.path().extension() == ".txt") {
            a_list_of_plan.push_back(folder.path().filename().string());
        }
    }

    for(int i = 0; i < a_list_of_plan.size(); i++){
        double price = 0;
        int calories = 0;
        //read
        MealPlan *temp = new MealPlan();
        Files->read_plan((current_path / a_list_of_plan.at(i)).string(), *temp);
        //print
        std::cout << "\nDay " << i + 1 << "\n";
        std::cout << "-- Breakfast --\n\n";
        for(int i = 0; i < temp->breakfast.size(); i++){
            std::cout << temp->breakfast.at(i)->getName() << "\n";
            price += temp->breakfast.at(i)->getPrice();
            calories += temp->breakfast.at(i)->getCalories();
        }
        std::cout << "Price: RM" << price << "\n";
        std::cout << "Total Calories: " << calories << "\n";
        price = 0;
        calories = 0;
        std::cout << "\n\n-- Lunch --\n\n";
        for(int i = 0; i < temp->lunch.size(); i++){
            std::cout << temp->lunch.at(i)->getName() << "\n";
            price += temp->lunch.at(i)->getPrice();
            calories += temp->lunch.at(i)->getCalories();
        }
        std::cout << "Price: RM" << price << "\n";
        std::cout << "Total Calories: " << calories << "\n";
        price = 0;
        calories = 0;
        std::cout << "\n\n-- Dinner --\n\n";
        for(int i = 0; i < temp->dinner.size(); i++){
            std::cout << temp->dinner.at(i)->getName() << "\n";
            price += temp->dinner.at(i)->getPrice();
            calories += temp->dinner.at(i)->getCalories();
        }
        std::cout << "Price: RM" << price << "\n";
        std::cout << "Total Calories: " << calories << "\n";
        price = 0;
        calories = 0;
        std::cout << "\n\n";
        pause();
        clearScreen();
        delete temp;
        temp = nullptr;
    }
}



void MealPlanner::main_interface(){
    int choice;
    std::cout << "initializing menu, please wait\n"; // create menuitem object to the program so that it can get the combination
    initialize_menu();
    clearScreen();
    while (true) {
        std::cout << "\n==============================\n";
        std::cout << "        Hello user " << the_user->getUsername() << "        \n";
        std::cout << "==============================\n";
        std::cout << "1. Create a New Meal Plan\n";
        std::cout << "2. Modify\n";
        std::cout << "3. View Existing Plan\n";
        std::cout << "4. Analyze Plan\n";
        std::cout << "5. Exit\n";
        std::cout << "------------------------------\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            clearScreen();
            try{
                createNewPlan();
            }
            catch(std::filesystem::filesystem_error &e){
                std::cout << "Plan already exists\n";
                return;
            }
        } 
        else if (choice == 2) {
            clearScreen();
            modify();
        }
        else if(choice == 3) {
            clearScreen();
            viewExistingPlan();
        }
        else if (choice == 4) {
            clearScreen();
            analyze();
            break;
        }
        else if (choice == 5) {
            break;
        } else {
            std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
            pause();
            clearScreen();
        }
    }
}

bool MealPlanner::Login(){
    
    std::string username;
    std::string password;

    std::cout << "Please enter your username: ";
    std::cin >> username;
    
    std::string path =".LoginInfo/" + username + ".txt";
    if(!(Files->check_exists(path))){
        std::cout << "User not found, please try again\n";
        return false;
    }

    //now the user login file is found, start to construct the user object to the mealplanner
    the_user = new User(); 
    Files->read_user_info(the_user, path);  // because the user must be a pointer, must create a new user and assign for it

    std::cout << "Plase enter your password: ";
    std::cin >> password;

    if(the_user->getPassword() == password){
        std::cout << "welcome back " << the_user->getUsername() << "\n";
    }
    else{
        std::cout << "wrong password\n";
        return false;
    }
    return true;
}

bool MealPlanner::SignUp(){
    std::string username;
    std::string password;
    char gender;
    std::cout << "Please enter your username (no space): ";
    std::cin >> username;
    std::cout << "Please enter your gender [M/F]: ";
    std::cin >> gender;
    std::cout << "Plase enter your password (no space): ";
    std::cin >> password;
    the_user = new User(username, gender, password); 
    try{
        Files->create_user_folder(username);  // try and catch in here
    }
    catch(std::runtime_error &e){
        std::cout << "User already exists, please try another username\n";
        return false;
    }
    Files->record_signinInfo(the_user, password);

    return true;
}

std::string MealPlanner::Register() {
    int choice;
    std::cout << "\n\n\n==============================\n";
    std::cout << "   Welcome to Meal Planner  \n";
    std::cout << "==============================\n\n";
    std::cout << "1. Sign Up (Create new account)\n\n";
    std::cout << "2. Log In (Access existing account)\n\n";
    std::cout << "3. Exit\n";
    std::cout << "------------------------------\n";
    std::cout << "Enter your choice (1, 2, or 3): ";
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "\n";
        if(!SignUp()){
            return "again";
        }
        return "success";
    } else if (choice == 2) {
        std::cout << "\n";
        if(!(Login())){
            return "again";
        }
        return "success";
    } else if (choice == 3) {
        std::cout << "Goodbye!\n";
        return "exit";
    }

    std::cout << "Invalid input. Please enter 1, 2, or 3.\n";
    pause();
    clearScreen();
    return "again";
}