#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include <iostream>
#include <vector>
using namespace std;

class Player {
public:
    Player();       // default constructor
    Player(string);
    Player(Player&, string);        // copy constructor
    Player& operator=(Player&);      // assignment operator
    friend ostream& operator<<(ostream&, const Player&);           // stream insertion operator
    vector<Territory*> toAttack();
    vector<Territory*> toDefend();
    void issueOrder();
    
    string getName();
    
private:
    string name;
    vector<Territory*> terrs;
    vector<Card*> cards;
    vector<Order*> orders;
};
