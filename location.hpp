#include "item.cpp"
#include "npc.cpp"
#include <map>
#ifndef location_h
#define locaation_h

class Location{
private:
std::string name;
std::string description;
bool visited;
std::map<std::string, Location> neighbors;
vector<NPC> locNpc;
vector<Item> locItems;

public:
Location(std::string n, std::string desc);
void add_location(string direction, Location loca);
void add_npc(NPC npc);
std::map<string, Location> getLocations();
};


#endif