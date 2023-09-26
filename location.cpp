#include <iostream>
#include <map>
#include "location.hpp"
#include "npc.hpp"
#include "item.hpp"



std::map<std::string, Location> Location::getLocations(){
    return neighbors;
}
void Location::add_location(std::string direction, Location& loca){
    if(direction.empty()){
        throw std::invalid_argument("Hey man... we use the compass here");
    }
    if(neighbors.find(direction) != neighbors.end()){
        throw std::invalid_argument("Not cool dude");
    }

    neighbors[direction] = loca;
}

void Location::add_npc(NPC& npc){
    locNpc.push_back(npc);
}
std::vector<NPC> Location::get_npcs(){
    return locNpc;
}

void Location::add_item(Item item){
    locItems.push_back(item);
}

std::vector<Item> Location::get_items(){
    return locItems;
}

void Location::set_visited(){
    visited = true;
}

bool Location::get_visited(){
    return visited;
}

void Location::set_name(std::string n){
    name = n;
}

void Location::set_desc(std::string desc){
    description = desc;
}

std::ostream& operator<<(std::ostream& os, const Location& obj){
    os << obj.name << " - " << obj.description << '\n' << "After scanning the room, you see the following NPC's \n"; 
    for(const NPC& i : obj.locNpc){os <<" - "<< i << "\n";} os << "You also see some items \n";
    for(const Item& i : obj.locItems){os << i << "\n";} os << "From here you can go to \n";
    for(const auto& i : obj.neighbors){
        os << " - " << i.first << " - " << i.second.name;
        if (i.second.visited == true)
        { os << " (Visited)";}
        
        ;};
    return os;
}
int main(){
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
}