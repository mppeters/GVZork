#include "item.hpp"
#include "npc.hpp"
#include "location.hpp"
#include <map>
#include <vector>
#include <functional>
#include <sstream>



#ifndef game_h
#define game_h

class Game{
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
        void create_world();
        Location random_location();
        int get_required_cals();
        void set_required_cals(int cals);
        void play();
        void show_help();
        void talk(std::vector<std::string> target);
        void meet(std::vector<std::string> target);
        void take(std::vector<std::string> target);
        void give(std::vector<std::string> target);
        void go(std::vector<std::string> target);
        void show_items(std::vector<std::string> target);
        void quit(std::vector<std::string> target);
        void addtoworld(Location& loc);
        void look();
        void set_max_weight(int weight);
        std::vector<Location> getworld();
        std::map<std::string, std::function<void(std::vector<std::string>)>> setup_commands();
        
};

#endif