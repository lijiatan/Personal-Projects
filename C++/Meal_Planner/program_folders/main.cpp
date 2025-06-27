#include <iostream>
#include "mealplanner.h"
#include "system.h"
#include "file_operation.h"
#include <filesystem>
#include "user.h"
#include <ctime>
#include <cstdlib>


int main(){
    
    std::srand(std::time(nullptr)); // a seed for random

    file_operation Files;
    MealPlanner user_interface(&Files);    

    while(true){
        std::string condition = user_interface.Register();
        if(condition == "success"){
            clearScreen();
            user_interface.main_interface();
        } 
        else if(condition == "again"){
            std::cout << "Please register again\n";
            pause();
            clearScreen();
        }
        else if(condition == "exit"){
            break;
        }
        clearScreen();
    }
    return 0;
}
