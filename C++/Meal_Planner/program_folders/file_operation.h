#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H

#include "user.h"
#include "menuitem.h"
#include "mealplan.h"
#include <string>
#include <iostream>
#include <vector>


class file_operation {
    private:
    protected:
    public:

        void make_directory(const std::string &path, const std::string &username);
        void create_user_folder(std::string& username);
        void record_signinInfo(User* the_user, std::string& password);  // Association
        bool check_exists(std::string path);
        void read_user_info(User *the_user, std::string path); // Association
        void read_menu(std::string path, std::vector<MenuItem*>& a_list, const std::string &types); // Association
        void record_day_plan(const std::string &path,MealPlan* the_plan); // Association
        void writeMealItemsToFile(std::ofstream &outFile, std::vector<MenuItem*> &mealList); // Association
        void read_plan(std::string path, MealPlan &the_plan); // Association

};


#endif


