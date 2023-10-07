#include <map>
#include "npc.hpp"
#include "item.hpp"

#ifndef LOCATION_HPP
#define LOCATION_HPP

// Defining the Location class
class Location{
    private:
        std::string name; // Name of the location
        std::string description; // Description of the location
        bool visited; // Whether the location has been visited by the player
        std::map<std::string, Location> neighbors; // Map of neighboring locations
        std::vector<NPC> locNpc; // Vector of NPCs in the location
        std::vector<Item> locItems; // Vector of items in the location

    public:
        // Function to add a neighboring location
        void add_location(std::string direction, Location& loca);

        // Function to add an NPC to the location
        void add_npc(NPC& npc);

        // Getter function for the neighboring locations
        std::map<std::string, Location> getLocations();

        // Getter function for the NPCs in the location
        std::vector<NPC> get_npcs();

        // Function to add an item to the location
        void add_item(Item item);

        // Function to remove an item from the location
        void remove_item(Item item);

        // Getter function for the items in the location
        std::vector<Item> get_items();

        // Setter function for the visited flag
        void set_visited();

        // Getter function for the visited flag
        bool get_visited();

        // Setter function for the name of the location
        void set_name(std::string n);

        // Setter function for the description of the location
        void set_desc(std::string desc);

        // Getter function for the name of the location
        std::string get_name();

        // Overloading the << operator to print the Location object
        friend std::ostream& operator<<(std::ostream& os, const Location& obj);
};

// End of header guard
#endif