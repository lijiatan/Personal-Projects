#include <iostream>
#include <vector>
#include <ctime>
#include <typeinfo>
#include "gadget_header.h"
#include "ansi_functions.h" 
#include <windows.h>
#include <limits>

bool game = true;
double dog_food = 2.59;
double cat_food = 1.99;
double currency = 20.0;
int dog_amount = 0;
int cat_amount = 0;

double max_earning = 40.00;
double happiness = 5.0;
const double max_happiness = 10.0;

class animal{
    public:

    std::string name;
    animal(std::string name = "unknown creature"){
        this -> name = name;
    }
    virtual ~animal() {} // Virtual destructor to enable dynamic_cast
};

std::vector<animal*> data;

class dog : public animal{

    public:

    dog(std::string name = " a stay puppy ") : animal(name) {}

};

class cat : public animal{

    public:

    cat(std::string name = " a stray kitten ") : animal(name) {}

};
// uncomplete 
class puppy : public dog{

    public:

    puppy(std::string name = " a child of ");
};

void create_dog(){

    std::string name;

    std::getline(std::cin >> std::ws , name);
    data.push_back(new dog(name));
    dog_amount += 1;
    Type(name + " is now your new pet\n");
    next_line();

}

void create_cat(){

    std::string name;
    std::getline(std::cin >> std::ws , name);
    data.push_back(new cat(name));
    cat_amount += 1;
    Type(name + " is now your new pet\n");
    next_line();

}

void sell_pet(const std::string provided_name) {

    for (auto it = data.begin(); it != data.end(); ) {
        if ((*it)->name == provided_name) {
            // Free memory
            if(dynamic_cast<dog*>(*it)){
                playSound("dog_mad", "sound_dog");
                dog_amount -= 1;
                currency += 20.00;
                playSound("dog_mad", "sound_dog");
                Sleep(500);
                stopSound("dog_mad");
            }
            else if (dynamic_cast<cat*>(*it)){
                playSound("cat_mad", "sound_cat");
                cat_amount -= 1;
                currency += 15.00;
                Sleep(500);
                stopSound("cat_mad");
            }

            delete *it;
            // Remove the pointer from the vector and update the iterator
            it = data.erase(it);  // erase returns the next valid iterator
        } else {
            ++it;  // Only increment if no deletion
        }
    }
}

bool yes_or_no(){
    std::string reply;
    std::cin >> reply;
    if(reply == "yes"){
        return true;
    }
    else{
        return false;
    }
}

void check_happiness_limit(){
    if(happiness > max_happiness){
        happiness = max_happiness;
    }
}

void meet_an_animal(){

    int random_animal = math_random(1, 2);

    if(random_animal == 1){
        Type("you meet a puppy, adopt it ? (" + green_color("yes") + "/" + red_color("no") + "): ");
        if(yes_or_no()){
            next_line();
            Type(italic(yellow_color(("you have decided to adopt it, give it a name:  "))));
            create_dog();
            happiness += 1;
            check_happiness_limit();
        }
        else{
            Type(red_color(faint("you left the puppy alone :(\n")));
            next_line();
        }
        

    }
    else if(random_animal == 2){
        Type("you meet a kitten, adopt it ? (" + green_color("yes") + "/" + red_color("no") + "): ");
        if(yes_or_no()){
            next_line();
            Type(italic(yellow_color(("you have decided to adopt it, give it a name:  "))));
            create_cat();
            happiness += 1;
            check_happiness_limit();

        }
        else{
            Type(red_color(faint("you left the kitten alone :(\n")));
            next_line();
        }

    }

}
void nothing(){
    Type(green_color("you go to the park, but nothing exiting here \n"));
    next_line();
} 

void show_pets() {
    if (data.size() == 0) {
        Type(" you feel empty \n");
        happiness -= 1;
    } else {
        Sleep(200);
        std::cout << "You adopted the following " << cyan_color("animals") << "\n";

        for (int i = 0; i < data.size(); i++) {
            Sleep(100);

            // Generate a unique alias for each loop iteration
            std::string alias = "sound_" + std::to_string(i);

            if (dynamic_cast<dog*>(data[i])) {
                playSound("bark", alias);  // Play a unique "bark" sound
                Sleep(200);
                std::cout << red_color("puppy ");
            } 
            else if (dynamic_cast<cat*>(data[i])) {               
                playSound("meow", alias);  // Play a unique "meow" sound
                Sleep(200);
                std::cout << red_color("kitten ");
            }
            
            std::cout << "-- " << data[i]->name << "\n";
            Sleep(500);
            stopSound(alias);
        }
    }
}


void show_state(){

    for(int i = 0; i < data.size(); i++){
        if(dynamic_cast<dog*>(data[i])){
            std::cout << red_color("puppy "); 
        }
        else if (dynamic_cast<cat*>(data[i])){
            std::cout << red_color("kitten ");
        }

    }

}

void work(){

    Type(faint(red_color("you went to work today, you feel exhausted . . \n")));
    Sleep(500);
    playSound("money", "audio1");
    std::cout << yellow_color("cash earned: ") << italic(green_color((happiness / max_happiness) * 40)) << "\n";
    currency += (happiness / max_happiness) * 40;
    stopSound("money"); 

}

void sick(){
    double medical_fees = 20.00;
    Type("you don't feel well today\n");
    Type("you went to the nearest clinic and paid " + red_color("$ ") + red_color(medical_fees));
    currency -= medical_fees;
}

void being_attacked(){
    int number_pet_lost = math_random(0, data.size());
    int random_index;

    if(data.size() > 0){
        Type("You decide to take all your pets for a walk,\n");
        playSound("dogs_attack", "attack");
        Type(red_color("but you encounter a bunch of aggressive stray dogs!\n"));
        stopSound("dogs_attack");
        Sleep(1000);
        Type("You did your best to protect all your pets, and...\n");
        for(int i = 0; i < number_pet_lost && !data.empty(); ++i){  // amount of pets needs to be delete

            random_index = math_random(0, data.size() - 1);  // random objects get delete
            if(dynamic_cast<dog*>(data[random_index])){
                Type(cyan_color(faint("you lost puppy -- ")));
                dog_amount--;
                happiness -= 2;
            }
            else if (dynamic_cast<cat*>(data[random_index])){
                Type(cyan_color(faint("you lost kitten -- ")));
                cat_amount--;
                happiness -= 2;
            }
            Type(data[random_index] -> name + "\n");
            next_line();
            delete data[random_index];
            data.erase(data.begin() + random_index);
            Sleep(500);
        }
        if(number_pet_lost == 0){
            Type("you returned home safetly with all your pets\n");
        }
        else{
            Type("You returned home with the remaining pets...\n");
        }
    }
    else{
        Type("You went for a walk,\n");
        playSound("dogs_attack", "attack");
        Type(red_color("but you encounter a bunch of aggressive stray dogs!\n"));
        Type("you run away successfully\n");
        stopSound("dogs_attack");
    }
    
}

double calculate_expenses(){
    return dog_amount * dog_food + cat_amount * cat_food;
}

void daily_expenses(){

    if(data.size() == 0){
        return;
    }

    double total_expenses = calculate_expenses();
    currency -= total_expenses;

    Type("it " + red_color( "cost you") + yellow_color(" $") + yellow_color(total_expenses) + cyan_color(" to feed them.\n"));
    
    if(currency < 0){
        //currency += calculate_expenses();
        Type("unfortunately, you can't afford to feed all your pets\n");

        int player_action;

        std::cout << "sell your pet                                 : 1\n";
        Sleep(500);
        std::cout << "skip a meal (feel hungry, you earn less money): 2\n";

        
        std::cin >> player_action;

        if(player_action == 1){
            Type("type the pet name you want to sell\n");
            std::string name;
            std::cin >> name;
            sell_pet(name);
            happiness -= 1;
            next_line();
            daily_expenses(); // check if it's still not enough currencies after deleting a pet

        }
        else if(player_action == 2){
            happiness -= 1;
        }
    }
    if(happiness >= 7){
        Type("you look happy" + blink(yellow_color("     :)\n")));
        return;
    }
    else{
        Type(". . . . . . \n");
        return;
    }
    
}


std::string check_currency(){

    if(currency >= 0){
        return yellow_color("$") + yellow_color(currency);
    }
    else{
        return blink(red_color("$")) + blink(red_color(currency));
    }
}

bool meaning_of_life(int score){
    if(happiness <= 0 || currency <= -50.0){

        Sleep(2000);
        Type(inverse(red_color("you found out life is meaningless . . .  \n")));
        
        Type(magenta_color("you survived ") + blink(score) + magenta_color(" days \n"));
        game = false;
        pause();
        return false;
    }
    else if(happiness > 8 && currency >= 200.00){
        Sleep(2000);
        Type(green_color(blink("you found the meaning of life\n")));
        Type("you live a successfull life\n");
        std::cout << yellow_color(blink(R"(
                               __     ______  _    _   __          _______ _   _ 
                               \ \   / / __ \| |  | |  \ \        / |_   _| \ | |
                                \ \_/ / |  | | |  | |   \ \  /\  / /  | | |  \| |
                                 \   /| |  | | |  | |    \ \/  \/ /   | | | . ` |
                                  | | | |__| | |__| |     \  /\  /   _| |_| |\  |
                                  |_|  \____/ \____/       \/  \/   |_____|_| \_|
                                    )")) << "\n";
        system("pause>nul");
        return false;
    }
    else{
        return true;
    }
}

void surprise(){
    int sold;
    int random_index;
    int count = 0;
    int counting_amount = 0;
    int babies = 0;
    int iscat = 0;
    if(data.size() > 0){
        //birth system
        if(cat_amount >= 2 || dog_amount >= 2){
            if(math_random(1, 100) <= 5){
                Type("This morining ");
                if(cat_amount >= 2){
                    iscat++;
                    Type("Your cats ");
                    for (int i = 0; i < data.size(); i++) {

                        if(dynamic_cast<cat*>(data[i])){
                            std::cout << "-- " << data[i]->name << " "; 
                            counting_amount++;
                        }
                
                        if(counting_amount >= 2){
                            break;
                        }
                        
                    }
                }
                else{
                    Type("Your dogs ");
                    for (int i = 0; i < data.size(); i++) {

                        if (dynamic_cast<dog*>(data[i])){
                            std::cout << "-- " << data[i]->name << " "; 
                            counting_amount++;
                        }
                        if(counting_amount >= 2){
                            break;
                        }
                    }
                }
                babies = math_random(1, 4);
                Type("has given birth ");
                Type(cyan_color(babies));
                Type("babies \n");
                Type("You should name them ! ! \n");

                for(int i = 0; i < babies; i++){
                    (iscat)? create_cat() : create_dog();
                }

            }
        }

        // gift system
        for(int c = 0; c < data.size(); c++){
            if(math_random(1, 100) <= 10){
                if(count == 0){
                    Type("This morning ");
                    count++;
                }
                random_index = math_random(0, data.size() - 1);  // random objects get delete
                if(dynamic_cast<dog*>(data[random_index])){
                    Type(cyan_color("your puppy -- "));
                }
                else if(dynamic_cast<cat*>(data[random_index])){
                    Type(cyan_color("your kitten -- "));
                }
                Type(data[random_index] -> name + "\n");
                Type("brought you back a gift !!!\n");
                sold = math_random(1, 50);
                Type("you sold it for  " + yellow_color(blink("$ "))  + yellow_color(blink(sold)) + "\n");
                currency += sold;
                happiness += 1;
            }
        }
    }
    
}

int move(){
    int player_move;
    while (true) {
        std::cout << "1. go out for a walk: \n";
        std::cout << "2. work:              \n";
        std::cin >> player_move;
        if(std::cin.fail()){
            std::cout << "Invalid input. Please enter a valid number." << std::endl;
            std::cin.clear(); // clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');      
            move();  
        }
        else{
            return player_move;
        }
    }
}

int main(){

    Type("The goal of this game is to survive as long as you can" +  yellow_color(blink(" keep your happiness > 0 ")) + "\n");
    clear_screen();
    int day = 1;
    srand(time(0));

    playSound("crack", "sound2");
    Type(faint("you are depressed :/\n"));
    stopSound("crack");
    Type("what should u do today\n");

    while (game){
        surprise();
        if(!meaning_of_life(day)){
            return 0;
        }
        meaning_of_life(day);
        next_line();
        Sleep(500);
        std::cout << cyan_color("Day ") << cyan_color(day) << yellow_color("          happiness :) = ") << blink(green_color(happiness)) << "         " <<"                    " << check_currency() << "\n";
        std::cout << "-------------------------------------------------------------------------------------------------\n";
        Sleep(1000);

        int player_move = move();

        if(player_move == 1){
            int random = math_random(1, 100);
            next_line();
            if(random <= 40){
                meet_an_animal();
            }
            else if(random <= 80){
                nothing();
            }
            else if(random <= 100){
                being_attacked();
            }
        }
        else if(player_move == 2){
            int random = math_random(1, 10);
            next_line();
            if(random > 1){
                work();
                happiness -= 1;
            }
            else if(random == 1){
                sick();
                happiness -= 1;
            }
        }
        else{
            Type("You felt bored at home . . .\n");
        }
        next_line();
        show_pets();
        next_line();
        daily_expenses();
        next_line();
        clear_screen();
        day++;
    }    
    for (animal* a : data) {
        delete a;  // Frees the memory for each dynamically allocated animal
    }
    data.clear();

    pause();
    return 0;
}


