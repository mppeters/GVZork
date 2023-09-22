#include <iostream>
#include <map>
#include "npc.cpp"
#include "item.cpp"
#include "location.hpp"

using namespace std;




Location::Location(std::string n, std::string desc):name(n),description(desc){
    if(n.empty()){
        throw std::invalid_argument("Nameless dimensions!? This isn't Minecraft");
    }
    if(desc.empty()){
        throw std::invalid_argument("Just a little hint? Please? What is this place???");
    }
}

std::map<string, Location> getLocations(){
    return neighbors;
}
void add_location(string direction, Location loca){
    if(direction.empty()){
        throw std::invalid_argument("Hey man... we use the compass here");
    }
    if(neighbors.find(direction) == neighbors.end()){
        throw std::invalid_argument("Not cool dude");
    }

    neighbors[direction] = loca;
}

void add_npc(NPC npc){
    locNpc.push_back(npc);
}
std::vector<NPC> get_npcs(){
    return locNpc;
}

void add_item(Item item){
    locItems.push_back(item);
}

std::vector<Item> get_items(){
    return locItems;
}

void set_visited(){
    visited = true;
}

bool get_visited(){
    return visited;
}

friend std::ostream& operator<<(std::ostream& os, const Location& obj){
    os << obj.name << " - " << obj.description << '\n\n' << "After scanning the room, you see the following NPC's \n" << "  - ";
}
