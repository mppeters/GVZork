#ifndef item_h
#define item_h

// Header guard to prevent multiple inclusion of this file

// Defining the Item class
class Item{
    private:
        std::string name; // Name of the item
        std::string description; // Description of the item
        int calories; // Number of calories in the item
        float weight; // Weight of the item in pounds

    public:
        // Constructor for the Item class
        Item(std::string n, std::string desc, int cal, float w);

        // Getter functions for the private member variables
        std::string getName(); // Returns the name of the item
        int getCalories(); // Returns the number of calories in the item
        float getWeight(); // Returns the weight of the item in pounds

        // Overloading the << operator to print the Item object
        friend std::ostream& operator<<(std::ostream& os, const Item& obj);
};

// End of header guard
#endif