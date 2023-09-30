#include <iostream>
#include <vector>
#include <sstream>
#include <functional>
#include <numeric>
#include "game.hpp"
#include "npc.hpp"
#include "location.hpp"
#include "item.hpp"


void Game::talk(std::vector<std::string> target){
    bool found = false;
    std::string input = std::accumulate(target.begin(), target.end(), std::string(" "));
    for (NPC& npc : current_location.get_npcs()) {
        if (npc.getName() == input) {
            std::cout << npc.getMsg() << '\n';
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "NPC not found in this location \n";
    }
}

std::map<std::string, std::function<void(std::vector<std::string>)>> Game::setup_commands(){
    std::map<std::string, std::function<void(std::vector<std::string>)>> new_commands;
    new_commands["talk"] = std::bind(&Game::talk, this, std::placeholders::_1);
    new_commands["go"] = std::bind(&Game::go, this, std::placeholders::_1);
    new_commands["show_help"] = std::bind(&Game::show_help, this);
    new_commands["meet"] = std::bind(&Game::meet, this, std::placeholders::_1);
    new_commands["take"] = std::bind(&Game::take, this, std::placeholders::_1);
    new_commands["give"] = std::bind(&Game::give, this, std::placeholders::_1);
    return new_commands;
}

Location Game::random_location(){
    srand(time(NULL));
    return world_locations[rand() % world_locations.size()];
}

void Game::go(std::vector<std::string> target){
    if(current_weight > max_weight){
        std::cout << "You're too fat to move \n";
        return;
    }
    current_location.set_visited();
    current_location = current_location.getLocations()[target[0]];
}

void show_help(){
    std::cout << "Commands: \n";
    std::cout << " - go <direction> \n";
    std::cout << " - talk <NPC> \n";
    std::cout << " - meet <NPC> \n";
    std::cout << " - take <item> \n";
    std::cout << " - give <item> \n";
    std::cout << " - show_items \n";
    std::cout << " - quit \n";
}

//coded by copilot
void Game::meet(std::vector<std::string> target){
    bool found = false;
    std::string input = std::accumulate(target.begin(), target.end(), std::string(" "));
    for (NPC& npc : current_location.get_npcs()) {
        if (npc.getName() == input) {
            std::cout << npc.getDescription() << '\n';
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "NPC not found in this location \n";
    }
}
void Game::take(std::vector<std::string> target){
    std::string input = std::accumulate(target.begin(), target.end(), std::string(" "));
    for(Item& i : current_location.get_items()){
        if(i.getName() == input){
            player_items.push_back(i);
            current_location.get_items().erase(std::remove(current_location.get_items().begin(), current_location.get_items().end(), i), current_location.get_items().end());
            current_weight += i.getWeight();
            break;
        }
    }
}
void Game::give(std::vector<std::string> target){
    std::string input = std::accumulate(target.begin(), target.end(), std::string(" "));
    for(Item& i : player_items){
        if(i.getName() == input){
            current_location.get_items().push_back(i);
            player_items.erase(std::remove(player_items.begin(), player_items.end(), i), player_items.end());
            current_weight -= i.getWeight();
            if(current_location.get_name() == "Woods"){
                if(i.getCalories() == 0){
                    current_location = random_location();
                }
                else{
                    required_cals -= i.getCalories();
                }
            }
            break;
        }
    }
    
}

void Game::show_items(std::vector<std::string> target){
    std::cout << "Items in your inventory: \n";
    for(Item& i : player_items){
        std::cout << i << "\n";
    }
    std::cout << current_weight;
}

void Game::look(){
    std::cout << current_location;
    if(current_location.get_items().size() > 0){
    std::cout << "Items in this location: \n";
    for(Item& i : current_location.get_items()){
        std::cout << i << "\n";
    }
    }
    else{
        std::cout << "No items in this location \n";
    }

    if(current_location.get_npcs().size() > 0){
    std::cout << "NPC's in this location: \n";
    for(NPC& i : current_location.get_npcs()){
        std::cout << i << "\n";
    }
    }
    else{
        std::cout << "You're alone \n";
    }

}

void Game::quit(std::vector<std::string> target){
    std::cout << "Game has been quit\n";
    in_progress = false;
}


void Game::addtoworld(Location& loc){
    world_locations.push_back(loc);
}

int Game::get_required_cals(){
    return required_cals;
}

void Game::set_required_cals(int cals){
    required_cals = cals;
}

void Game::set_max_weight(int weight){
    max_weight = weight;
}




void create_world(){
Game game;
game.set_required_cals(500);
game.set_max_weight(30);
Location clocktower;
game.addtoworld(clocktower);
clocktower.set_name("Clocktower");
clocktower.set_desc("The clocktower is a tall building with a clock on it");
Location library;
game.addtoworld(library);
library.set_name("Mary Idema Pew Library");
library.set_desc("The library is a building where kids go to study");
Location gym;
game.addtoworld(gym);
gym.set_name("Gym");
gym.set_desc("We go gym");
Location kirkhof;
game.addtoworld(kirkhof);
kirkhof.set_name("Kirkhof");
kirkhof.set_desc("Kirkhof is the heart of campus");
Location mackinac;
game.addtoworld(mackinac);
mackinac.set_name("Mackinac Hall");
mackinac.set_desc("Computer Science kids hiding from the sunlight");
Location zumberge;
game.addtoworld(zumberge);
zumberge.set_name("Zumberge");
zumberge.set_desc("The president sits high in her office");
Location kleiner;
game.addtoworld(kleiner);
kleiner.set_name("Kleiner");
kleiner.set_desc("Freshman scouring for food");
Location Lake_superior;
game.addtoworld(Lake_superior);
Lake_superior.set_name("Lake Superior Hall");
Lake_superior.set_desc("What a great place to relax");
clocktower.add_location("west", library);
clocktower.add_location("south", kirkhof);
clocktower.add_location("north", mackinac);
kirkhof.add_location("north", clocktower);
kirkhof.add_location("east", zumberge);
kirkhof.add_location("west", library);
zumberge.add_location("west", kirkhof);
zumberge.add_location("north", mackinac);
zumberge.add_location("east",Lake_superior);
Lake_superior.add_location("west", zumberge);
mackinac.add_location("south", clocktower);
mackinac.add_location("west", gym);
mackinac.add_location("north", kleiner);
gym.add_location("east", mackinac);
gym.add_location("south", library);

Location woods;
game.addtoworld(woods);
Lake_superior.add_location("east", woods);
woods.set_name("Woods");
woods.set_desc("The woods are dark and scary");
woods.add_location("west", Lake_superior);

//Create items

Item stringcheese("String Cheese","A delicious snack", 20, 1);
Item pandaexpress("Panda Express","A delicious meal", 352, 10);
Item metrxbar("Metrx Bar","bland protein bar", 300, 29);
Item pizza("Pizza","PIZZZZAAAAAAAAAAAAA", 200, 10);
Item gluestick("Glue Stick","snack", 2, 1);
Item calculator("Calculator","A TI-84+", 0, 1);
Item pencil("Pencil","suspicious looing pencil", 0, 1);
Item macbookpro("Macbook Pro","2015 Macbook pro... doesn't support xcode", 0, 5);
Item waterbottle("Water Bottle","Stay hydrated fool", 0, 1);
Item phone("Phone","iPhone 12 Pro Max to shove in your face everywhere you walk", 0, 1);

//add items to locations
//kirkhof will have panda express
kirkhof.add_item(pandaexpress);
mackinac.add_item(gluestick);
mackinac.add_item(metrxbar);
zumberge.add_item(stringcheese);
kleiner.add_item(pizza);
gym.add_item(waterbottle);
gym.add_item(calculator);
Lake_superior.add_item(phone);
clocktower.add_item(macbookpro);
library.add_item(pencil);




//Create NPC's
NPC Rahat("Rahat Rafiq","The goat");
//Generated by Copilot
NPC Pres("The President","Lovin life");
NPC GhostOfBowman("Ghost of Bowman","The ghost of Dr. Bowman");
NPC Seth("Seth","If seen outside of The Den, please return to The Den");
NPC Robert("Robert","Just a weird dude named Robert");
NPC Elf("Elf", "Hungry, hungry, hungry");

mackinac.add_npc(Rahat);
zumberge.add_npc(Pres);
clocktower.add_npc(GhostOfBowman);
kirkhof.add_npc(Seth);
kleiner.add_npc(Robert);




}

void Game::play(){
    std::cout << "Welcome to GVZork, feed the elf to 500 calories to be set free \n";
    commands = setup_commands();
    while(in_progress){
        std::cout << "What is your command";
        std::string command;
        std::string input;
        std::cin >> input;
        std::vector<std::string> tokens;
        std::istringstream iss(input);
        std::string token;
        while (std::getline(iss, token,  ' ')) {
            tokens.push_back(token);
        }

        command = tokens[0];
        tokens.erase(tokens.begin());   
        auto it = commands.find(command);
        if(it != commands.end()){
            it->second(tokens);
        }
        else{
            std::cout << "Command not found \n";
        }

    }
}

int main(){
    create_world();
    Game game;
    game.play();
}