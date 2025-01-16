#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <windows.h>

int math_random(int min, int max) {
    if (min > max) std::swap(min, max);  // Ensure min is less than or equal to max
    return min + (rand() % (max - min + 1));
}


void playSound(std::string sound_name, const std::string& alias) {
    // Open and play the sound with a unique alias
    std::string full_path;
    std::string folder_path = "sound";
    if(sound_name == "crack"){
        full_path = folder_path + "\\" + "cracking_effect.wav";
    }
    else if(sound_name == "type_sound"){
        full_path = folder_path + "\\" + "keyboard.wav";
    }
    else if(sound_name == "meow"){
        int random_choice = math_random(1, 3);
        if(random_choice == 1){
            full_path = folder_path + "\\" + "meow1.wav";
        }
        else if(random_choice == 2){
            full_path = folder_path + "\\" + "meow2.wav";
        }
        else{
            full_path = folder_path + "\\" + "meow3.wav";            
        }
    }
    else if(sound_name == "bark"){
        int random_choice = math_random(1, 3);

        if(random_choice == 1){
            full_path = folder_path + "\\" + "bark1.wav";
        }
        else if(random_choice == 2){
            full_path = folder_path + "\\" + "bark2.wav";
        }
        else{
            full_path = folder_path + "\\" + "bark3.wav";            
        }    
    }
    else if(sound_name == "money"){
        full_path = folder_path + "\\" + "money.wav";
    }
    else if(sound_name == "cat_mad"){
        full_path = folder_path + "\\" + "cat_mad.wav";
    }
    else if(sound_name == "dog_mad"){
        full_path = folder_path + "\\" + "dog_mad.wav";
    }
    else if(sound_name == "dogs_attack"){
        full_path = folder_path + "\\" + "group_of_dogs.wav";
    }
    
    std::string openCommand = "open \"" + full_path + "\" type waveaudio alias " + alias;
    std::string playCommand = "play " + alias + " from 0";
    mciSendString(openCommand.c_str(), NULL, 0, NULL);
    mciSendString(playCommand.c_str(), NULL, 0, NULL);
}

void stopSound(const std::string& alias) {
    std::string closeCommand = "close " + alias;
    mciSendString(closeCommand.c_str(), NULL, 0, NULL);
}
void Sound_Time_Position(const std::string& alias, int position) {
    // Seek to the specified position (in milliseconds)
    std::string seekCommand = "seek " + alias + " to " + std::to_string(position);
    mciSendString(seekCommand.c_str(), NULL, 0, NULL);
}

void clear_screen(){
    system("pause");
    system("CLS");
}

void pause(){
    system("pause");
}

void next_line(){
    std::cout << "\n";
}

void Type(const std::string &text) {
    playSound("type_sound", "sound1");
    for (char c : text) {
        std::cout << c;
        ::Sleep(30);  // Adjust for faster or slower typing effect
    }
    stopSound("sound1");
    //std::cout << std::endl;
}
