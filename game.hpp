//Coded by Copilot, edited by human
#include "item.hpp"
#include "npc.hpp"
#include "location.hpp"
#include <map>
#include <vector>
#include <functional>
#include <sstream>

#ifndef game_h
#define game_h

class Game {
private:
    int max_weight;
    int required_cals;
    int total_cal;
    int current_weight;
    std::vector<Item> player_items;
    std::vector<Location> world_locations;
    Location current_location;
    bool in_progress;
    std::map<std::string, std::function<void(std::vector<std::string>)>> commands;

public:
    // Constructor for the Game class
    Game();

    // Function to create the world
    void create_world();

    // Function to get a random location from the world
    Location random_location();

    // Getter and setter functions for the required calories
    int get_required_cals();
    void set_required_cals(int cals);

    // Function to start the game
    void play();

    // Function to show the help menu
    void show_help();

    // Functions to interact with NPCs
    void talk(std::vector<std::string> target);
    void meet(std::vector<std::string> target);

    // Functions to interact with items
    void take(std::vector<std::string> target);
    void give(std::vector<std::string> target);

    // Function to move to a different location
    void go(std::vector<std::string> target);

    // Function to show the player's items
    void show_items(std::vector<std::string> target);

    // Function to quit the game
    void quit(std::vector<std::string> target);

    // Function to add a location to the world
    void addtoworld(Location& loc);

    // Function to look around the current location
    void look();

    // Setter function for the maximum weight the player can carry
    void set_max_weight(int weight);

    //A function similar to quit
    void dropout();

    //A function to teleport to a random location, no choices here
    void teleport();


    // Getter function for the world locations
    std::vector<Location> getworld();

    // Function to set up the command map
    std::map<std::string, std::function<void(std::vector<std::string>)>> setup_commands();
};

#endif