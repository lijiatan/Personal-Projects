#include "general.h"
#include "user_data.h"
#include "user.h"
#include <iostream>

void general::analyze_plan(User &the_user){
    int total_calories;
    
    std::cout << get_name() << " had view your plan\n";

    for(int i = 0; i < the_user.getData().Get_plan().size(); i++){
        total_calories = 0;
        for(int b = 0; b < the_user.getData().Get_plan().at(i).breakfast.size(); b++){
            total_calories += the_user.getData().Get_plan().at(i).breakfast.at(b)->getCalories();
        }
        for(int b = 0; b < the_user.getData().Get_plan().at(i).lunch.size(); b++){
            total_calories += the_user.getData().Get_plan().at(i).lunch.at(b)->getCalories();
        }
        for(int b = 0; b < the_user.getData().Get_plan().at(i).dinner.size(); b++){
            total_calories += the_user.getData().Get_plan().at(i).dinner.at(b)->getCalories();
        }

        int min = 0, max = 0;
        if(the_user.getGender() == 'M'){
            // Calorie range for men to gain weight
            min = 2200; // Adjusted for surplus from male maintenance (2200-3000)
            max = 3000; 
        }
        else{
            // Calorie range for women to gain weight
            min = 1800; // Adjusted for surplus from female maintenance (1800-2400)
            max = 2400; 
        }
        
        if(total_calories >= min && total_calories <= max){
            std::cout << "Day " << i + 1 << " total calories = " << total_calories << " is good for gaining weight\n";
        }
        else if(total_calories < min){
            std::cout << "Day " << i + 1 << " total calories = " << total_calories << " not enough calories for gaining weight\n";
        }
        else{
            std::cout << "Day " << i + 1 << " total calories = " << total_calories << " too much calories for gaining weight\n";
        }
    }
}