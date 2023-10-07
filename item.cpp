#include <iostream>
#include "item.hpp"
#include "location.hpp"

    //Item constructor, creates an item with a name, description, calories, and weight
    Item::Item(std::string n, std::string desc, int cal, float w) : name(n), description(desc), calories(cal), weight(w){
        if(n.empty()){
            throw std::invalid_argument("Name cannot be blank");
        }
        if(desc.empty()){
            throw std::invalid_argument("Description cannot be blank");
        }
        if(cal < 0 || cal > 1000){
            throw std::invalid_argument("Calories must be between 0 and 1000, get your diet in check");
        }
        if(w < 0 || w > 500){
            throw std::invalid_argument("HMMMMM this weight is funny");
        }
    }

    
    //Overloading the << operator to print the Item object in the desired format
    std::ostream& operator<<(std::ostream& os, const Item& obj){
        os << "Name: " << obj.name << " ("<< obj.calories<<" calories)"<<" - "<< obj.weight<<" lb - " << obj.description<<"\n";
        return os;
    }

    //Getter function for the name
    std::string Item::getName(){
        return name;
    }

    //Getter function for the calories of an Item
    int Item::getCalories(){
        return calories;
    }

    //Getter function for the weight of an Item
    float Item::getWeight(){
        return weight;
    }


/*int main(){
    Item sword("harold","Harold the mighty sword",0,10);

    std::cout << sword;
}
*/