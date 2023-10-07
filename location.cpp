//Coded by Copilot, edited by human
#include <iostream>
#include <map>
#include "location.hpp"
#include "npc.hpp"
#include "item.hpp"


// Function to get the neighboring locations
std::map<std::string, Location> Location::getLocations(){
    return neighbors;
}

// Function to add a neighboring location with a direction
void Location::add_location(std::string direction, Location& loca){
    if(direction.empty()){
        throw std::invalid_argument("Hey man... we use the compass here");
    }
    if(neighbors.find(direction) != neighbors.end()){
        throw std::invalid_argument("Not cool dude");
    }

    neighbors[direction] = loca;
}

// Function to add an NPC to the location
void Location::add_npc(NPC& npc){
    locNpc.push_back(npc);
}

//Function to get the NPCs in the location
std::vector<NPC> Location::get_npcs(){
    return locNpc;
}

// Function to add an item to the location
void Location::add_item(Item item){
    locItems.push_back(item);
}

//Function to remove an item from the location
void Location::remove_item(Item item){
    auto it = std::find_if(locItems.begin(), locItems.end(),
        [&](Item& i) { return i.getName() == item.getName(); });
    if (it != locItems.end()) {
        locItems.erase(it);
    }
}

//Function to get the items in the location
std::vector<Item> Location::get_items(){
    return locItems;
}

//Function to set the visited flag, indicating that the player has visited the location
void Location::set_visited(){
    visited = true;
}

//Function to get whether or not a location has been visited
bool Location::get_visited(){
    return visited;
}

//Setter function for the name of the location taking an input string
void Location::set_name(std::string n){
    name = n;
}

//sets the description of the location taking an input string
void Location::set_desc(std::string desc){
    description = desc;
}

//Getter function for the name of the location
std::string Location::get_name(){
    return name;
}

//Overloading the << operator to print the Location object, printing the name, description, NPCs, items, and neighboring locations
std::ostream& operator<<(std::ostream& os, const Location& obj){
    os << obj.name << " - " << obj.description << '\n' << "After scanning the room, you see the following NPC's \n"; 
    for(const NPC& i : obj.locNpc){os <<" - "<< i << "\n";} os << "You also see some items \n";
    for(const Item& i : obj.locItems){os << i << "\n";} os << "From here you can go to \n";
    for(const auto& i : obj.neighbors){
        os << " - " << i.first << " - " << i.second.name;
        if (i.second.visited == true)
        { os << " (Visited)";}
        os << "\n"
        ;};
    return os;
}
/*int main(){
    Location test;
    test.set_name("Test AHHH");
    test.set_desc("What");
    Location weest;
    weest.set_name("Somewhere to the east");
    weest.set_visited();
    test.add_location("East", weest);
    NPC jerry("Jerry","old man");
    test.add_npc(jerry);
    Item Sword("Exalicur","Cardboard Sword",0,10);
    test.add_item(Sword);

    std::cout << test;
}*/