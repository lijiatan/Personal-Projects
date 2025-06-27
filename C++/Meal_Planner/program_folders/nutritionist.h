#ifndef NUTRITIONIST_H
#define NUTRITIONIST_H

#include <string>
#include "user.h" 


class Nutritionist {  // abstract class, virtual function included
private:
    std::string name;
    std::string expertise_in;
    
public:
    Nutritionist(std::string _name, std::string _expertise_in) 
        : name(_name), expertise_in(_expertise_in) {}
    
    virtual ~Nutritionist() = default;  // Add virtual destructor
    
    std::string get_name() const { return name; }
    std::string get_expertise() const { return expertise_in; }

    virtual void analyze_plan(User &) = 0;  // association
};

#endif


