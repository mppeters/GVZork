#include <iostream>

using namespace std;

class Item{
    private:
    std::string& name;
    std::string& description;
    int calories;
    int weight;

    public:
    Item(std::string& n, std::string& desc, int cal, float w){
        if(n.empty()){
            throw std::invalid_argument("Name cannot be blank");
        }
        else{
            name = n;
        }
        if(desc.empty()){
            throw std::invalid_argument("Description cannot be blank");
        }
        else{
        description = desc;
        }
        if(cal < 0 || cal > 1000){
            throw std::invalid_argument("Calories must be between 0 and 1000, get your diet in check");
        }
        else{
            calories = cal;
        }
        if(w < 0 || w > 500){
            throw std::invalid_argument("HMMMMM this weight is funny");
        }
        else{
            weight = w;
        }
    }

    

    friend std::ostream& operator<<(std::ostream& os, const Item& obj){
        os << "Name: " << obj.name << "("<< obj.calories<<" calories)"<<" - "<< obj.weight<<" lb - " << obj.description;
        return os;
    }
};