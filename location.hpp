#include <map>
#include "npc.hpp"
#include "item.hpp"

#ifndef LOCATION_HPP
#define LOCATION_HPP

class Location{
    private:
        std::string name;
        std::string description;
        bool visited;
        std::map<std::string, Location> neighbors;
        std::vector<NPC> locNpc;
        std::vector<Item> locItems;

    public:
        void add_location(std::string direction, Location& loca);
        void add_npc(NPC& npc);
        std::map<std::string, Location> getLocations();
        std::vector<NPC> get_npcs();
        void add_item(Item item);
        void remove_item(Item item);
        std::vector<Item> get_items();
        void set_visited();
        bool get_visited();
        void set_name(std::string n);
        void set_desc(std::string desc);
        std:: string get_name();
        friend std::ostream& operator<<(std::ostream& os, const Location& obj);
};


#endif