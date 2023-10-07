//Coded by Copilot, edited by human
#include <iostream>
#include <vector>
#include <string>
#include "npc.hpp"

    //NPC constructor, creates an NPC with a name and description
    NPC::NPC(std::string n, std::string d) : name(n), description(d){
        if(n.empty()){
            throw std::invalid_argument("No Name!?");

        }
    }

    //Getter function for the name
    std::string NPC::getName(){
        return name;
    }

    //Getter function for the description
    std::string NPC::getDescription(){
        return description;
    }

    //Getter function for the message
    std::string NPC::getMsg(){
        if(msgnum == msgvec.size()){
            msgnum = 0;
        }
        return msgvec[msgnum++];
    }

    //Add a message to the NPC's list of messages
    void NPC::addMsg(std::vector<std::string> m){
        msgvec = m;
    }
    
    //Overloading the << operator to print the NPC object in the desired format
    std::ostream& operator<<(std::ostream& os, const NPC& obj){
        os << obj.name;
        return os;
    }

/*int main(){
    NPC steven("bob","just bob");
    std::cout << steven;

}
*/