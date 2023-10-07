//Coded by Copilot, edited by human
#include "item.hpp"
#include <string>
#include<vector>

#ifndef npc_h
#define npc_h

// Defining the NPC class
class NPC{
    private:
        std::string name; // Name of the NPC
        std::string description; // Description of the NPC
        int msgnum; // Index of the next message to be displayed
        std::vector<std::string> msgvec; // Vector of messages for the NPC

    public:
        // Constructor for the NPC class
        NPC(std::string n, std::string d);

        // Getter functions for the private member variables
        std::string getName(); // Returns the name of the NPC
        std::string getDescription(); // Returns the description of the NPC

        // Function to get the next message from the NPC's message vector
        std::string getMsg();

        // Function to add messages to the NPC's message vector
        void addMsg(std::vector<std::string> m);

        // Overloading the << operator to print the NPC object
        friend std::ostream& operator<<(std::ostream& os, const NPC& obj);
};

// End of header guard
#endif