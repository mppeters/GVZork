#ifndef item_h
#define item_h

class Item{
    private:
        std::string name;
        std::string description;
        int calories;
        float weight;

    public:
        Item(std::string n, std::string desc, int cal, float w);
        std::string getName();
        int getCalories();
        float getWeight();

        friend std::ostream& operator<<(std::ostream& os, const Item& obj);
};

#endif