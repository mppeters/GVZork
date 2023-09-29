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

    
    std::string NPC::getMsg(){
        if(msgnum == msgvec.size()){
            msgnum = 0;
        }
        return msgvec[msgnum++];
    }

    void NPC::addMsg(std::vector<std::string> m){
        msgvec = m;
    }
    

    std::ostream& operator<<(std::ostream& os, const NPC& obj){
        os << obj.name;
        return os;
    }

/*int main(){
    NPC steven("bob","just bob");
    std::cout << steven;

}
*/