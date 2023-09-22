#include "item.cpp"
#include "location.cpp"
#include <string>
#include<vector>

#ifndef npc_h
#define npc_h
class NPC{
    private:
    std::string name;
    std::string description;
    int msgnum;
    vector<std::string> msgvec;

    public:
    NPC(std::string n, std::string d);
    std::string getName();
    std::string getDescription();
    std::string getMsg();
    friend std::ostream& operator<<(std::ostream& os, const NPC& obj);
};
#endif