#include <iostream>
#include "item.hpp"

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

    

    std::ostream& operator<<(std::ostream& os, const Item& obj){
        os << "Name: " << obj.name << " ("<< obj.calories<<" calories)"<<" - "<< obj.weight<<" lb - " << obj.description<<"\n";
        return os;
    }


/*int main(){
    Item sword("harold","Harold the mighty sword",0,10);

    std::cout << sword;
}
*/