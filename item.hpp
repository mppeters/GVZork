#ifndef item_h
#define item_h

class Item{
    private:
    std::string name;
    std::string description;
    int calories;
    int weight;
    public:
    Item(std::string n, std::string desc, int cal, float w);

    friend std::ostream& operator<<(std::ostream& os, const Item& obj);
};

#endif