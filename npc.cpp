#include <iostream>
#include <vector>
#include <string>
using namespace std;

class NPC{

    private:
    std::string name;
    std::string description;
    int msgnum;
    vector<std::string> msgvec;

    public:
    NPC(std::string n, std::string d) : name(n), description(d){
        if(n.empty()){
            throw std::invalid_argument("No Name!?");

        }
    }

    std::string getName(){
        return name;
    }

    std::string getDescription(){
        return description;
    }

    // Need to finish this bad boy up
/*
    std::string getMsg(){
        return 
    }
    */

    friend std::ostream& operator<<(std::ostream& os, const NPC& obj){
        os << obj.name;
        return os;
    }


};