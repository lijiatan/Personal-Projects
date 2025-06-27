#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include "user_data.h"

class User{
    private:
        
        std::string username;
        std::string password;
        char gender;
        User_Data data;

    protected:

    public:

        User(const std::string& _username = "", const char& _gender = ' ', const std::string& _password = "")
            : username(_username), gender(_gender), password(_password), data(){}

        std::string getUsername() const {
            return username;
        }

        char getGender() const {
            return gender;
        }

        std::string getPassword() const {
            return password;
        }

        void setUsername(const std::string &newUsername) {
            username = newUsername;
        }

        void setGender(std::string newGender) {
            gender = newGender.at(0);
        }

        void setPassword(const std::string &newPassword) {
            password = newPassword;
        }

        User_Data& getData() {  // return original vector 
            return data;
        }



        ~User(){};
};



#endif