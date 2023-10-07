#include <iostream>
#include <vector>
#include <sstream>
#include <functional>
#include <numeric>
#include <string>
#include "game.hpp"
#include "npc.hpp"
#include "location.hpp"
#include "item.hpp"

// methood to talk to an NPC
void Game::talk(std::vector<std::string> target){
    bool found = false;
     std::string input = std::accumulate(
        target.begin(), target.end(), std::string(""),
        [](const std::string& a, const std::string& b) {
            return a + " " + b;
        }
    );
    std::cout << input << '\n';
    for (NPC& npc : current_location.get_npcs()) {
        std::cout << npc.getName() << '\n';
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

// method to setup the commands, maps strings to call the functions in the game class
std::map<std::string, std::function<void(std::vector<std::string>)>> Game::setup_commands(){
    std::map<std::string, std::function<void(std::vector<std::string>)>> new_commands;
    new_commands["talk"] = std::bind(&Game::talk, this, std::placeholders::_1);
    new_commands["go"] = std::bind(&Game::go, this, std::placeholders::_1);
    new_commands["show_help"] = std::bind(&Game::show_help, this);
    new_commands["meet"] = std::bind(&Game::meet, this, std::placeholders::_1);
    new_commands["take"] = std::bind(&Game::take, this, std::placeholders::_1);
    new_commands["give"] = std::bind(&Game::give, this, std::placeholders::_1);
    new_commands["quit"] = std::bind(&Game::quit, this, std::placeholders::_1);
    new_commands["look"] = std::bind(&Game::look, this);
    return new_commands;
}

//function to get a random location from the world
Location Game::random_location(){
    srand(time(NULL));
    return world_locations[rand() % world_locations.size()];
}

//function to move to a different location
void Game::go(std::vector<std::string> target) {
    if (current_weight > max_weight) {
        std::cout << "You're too fat to move\n";
        return;
    }
    current_location.set_visited();
    current_location = current_location.getLocations()[target[0]];
}


// functiion that outputs available commands
void Game::show_help(){
    std::cout << "Commands: \n";
    std::cout << " - go <direction> \n";
    std::cout << " - talk <NPC> \n";
    std::cout << " - meet <NPC> \n";
    std::cout << " - take <item> \n";
    std::cout << " - give <item> \n";
    std::cout << " - show_items \n";
    std::cout << " - quit \n";
    std::cout << " - look \n";
}

//function to talk to an npc, prints out the npc's message
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

//function to take an item from a location
void Game::take(std::vector<std::string> target){
    std::string input = std::accumulate(target.begin(), target.end(), std::string(),
        [](const std::string& a, const std::string& b) { return a + " " + b; });
    for(Item& i : current_location.get_items()){
        if(i.getName() == input){
            player_items.push_back(i);
            current_weight += i.getWeight();
            current_location.remove_item(i);
            break;
        }
    }
    
}

//function to give an item to an npc
void Game::give(const std::vector<std::string> target) {
    std::string input = std::accumulate(target.begin(), target.end(), std::string(""));
    auto it = std::find_if(player_items.begin(), player_items.end(),
        [&](Item& i) { return i.getName() == input; });
    if (it != player_items.end()) {
        current_location.get_items().push_back(*it);
        player_items.erase(it);
        current_weight -= it->getWeight();
        if (current_location.get_name() == "Woods") {
            if (it->getCalories() == 0) {
                current_location = random_location();
            } else {
                required_cals -= it->getCalories();
            }
        }
    } else {
        std::cout << "Item not found in inventory\n";
    }
}

//function to show the items in the players inventory
void Game::show_items(std::vector<std::string> target){
    std::cout << "Items in your inventory: \n";
    for(Item& i : player_items){
        std::cout << i << "\n";
    }
    std::cout << current_weight;
}

//function to look around the room/area the player is in
void Game::look(){
    std::cout << current_location;

}

//function to quit the game
void Game::quit(std::vector<std::string> target){
    std::cout << "Game has been quit\n";
    in_progress = false;
}

//add a location to the world
void Game::addtoworld(Location& loc){
    world_locations.push_back(loc);
}

//returns the required calories to win
int Game::get_required_cals(){
    return required_cals;
}

//sets the required calories to win
void Game::set_required_cals(int cals){
    required_cals = cals;
}
//sets the maximum weight the player can carry
void Game::set_max_weight(int weight){
    max_weight = weight;
}

//Drops out of college, try welding
void Game::dropout(){
    std::cout << "You have dropped out of college, you are now a failure stuck in Allendale Michigan forever \n";
    in_progress = false;
}

//teleports to a random location, it could help, it could hurt
void Game::teleport(){
    current_location = random_location();
}



//creates the game world, sets the required calories, maximum weight, creates and add locations,items, and npc's to the game
void Game::create_world(){

    set_required_cals(500);
    set_max_weight(30);
    Location clocktower;
    addtoworld(clocktower);
    clocktower.set_name("Clocktower");
    clocktower.set_desc("The clocktower is a tall building with a clock on it");
    Location library;
    addtoworld(library);
    library.set_name("Mary Idema Pew Library");
    library.set_desc("The library is a building where kids go to study");
    Location gym;
    addtoworld(gym);
    gym.set_name("Gym");
    gym.set_desc("We go gym");
    Location kirkhof;
    addtoworld(kirkhof);
    kirkhof.set_name("Kirkhof");
    kirkhof.set_desc("Kirkhof is the heart of campus");
    Location mackinac;
    addtoworld(mackinac);
    mackinac.set_name("Mackinac Hall");
    mackinac.set_desc("Computer Science kids hiding from the sunlight");
    Location zumberge;
    addtoworld(zumberge);
    zumberge.set_name("Zumberge");
    zumberge.set_desc("The president sits high in her office");
    Location kleiner;
    addtoworld(kleiner);
    kleiner.set_name("Kleiner");
    kleiner.set_desc("Freshman scouring for food");
    Location Lake_superior;
    addtoworld(Lake_superior);
    Lake_superior.set_name("Lake Superior Hall");
    Lake_superior.set_desc("What a great place to relax");
 

    Location woods;
    addtoworld(woods);
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
    NPC Pres("The President","Lovin life");
    NPC GhostOfBowman("Ghost of Bowman","The ghost of Dr. Bowman");
    NPC Seth("Seth","If seen outside of The Den, please return to The Den");
    NPC Robert("Robert","Just a weird dude named Robert");
    NPC Elf("Elf", "Hungry, hungry, hungry");


    std::vector<std::string> Bowmsg;
    Bowmsg.push_back("Hello, I am the ghost of Dr. Bowman");
    Bowmsg.push_back("I am here to tell you that you are trapped in GVZork");
    Bowmsg.push_back("I finally escaped this land though");
    Bowmsg.push_back("Build me an adder");
    GhostOfBowman.addMsg(Bowmsg);

    mackinac.add_npc(Rahat);
    zumberge.add_npc(Pres);
    clocktower.add_npc(GhostOfBowman);
    kirkhof.add_npc(Seth);
    kleiner.add_npc(Robert);

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

    current_location = clocktower;


}


//Main game loop, sets uup the commands and consistently waits for input from the user to call the input command
void Game::play(){
    std::cout << "Welcome to GVZork, feed the elf to 500 calories to be set free \n";
    commands = setup_commands();
    in_progress = true;
    while(in_progress){
        std::cout << "What is your command\n";
        std::string command;
        std::string input;
        std::getline(std::cin, input);
        std::vector<std::string> tokens;
        std::istringstream iss(input);
        std::string token;
        while (iss >> token) {
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
    Game game;
    game.create_world();
    game.play();

}