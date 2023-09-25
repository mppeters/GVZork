#include <iostream>
#include <vector>
#include <string>
#include "npc.hpp"

    NPC::NPC(std::string n, std::string d) : name(n), description(d){
        if(n.empty()){
            throw std::invalid_argument("No Name!?");

        }
    }

    std::string NPC::getName(){
        return name;
    }

    std::string NPC::getDescription(){
        return description;
    }

    
//dont think this is right
    std::string NPC::getMsg(){
        return msgvec[msgnum];
        msgnum = msgnum + 1;
    }
    

    std::ostream& operator<<(std::ostream& os, const NPC& obj){
        os << obj.name;
        return os;
    }

