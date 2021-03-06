#pragma once
#include <string>
#include <vector>
#include "Map.h"
#include "Cards.h"

using namespace std;

class Order;

class Player
{
public:
    Player(); // default constructor
    Player(string);
    Player(const Player &);
    Player(const Player &, string);                        // copy constructor
    Player &operator=(const Player &);                     // assignment operator
    friend ostream &operator<<(ostream &, const Player &); // stream insertion operator
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();
    void issueOrder(string);
    string getName() const;
    string toString() const;
    vector<Territory *> getTerritories();
    void addTerritory(Territory *territory);
    void addCards(Hand *hand);
    int *getArmies();
    void addArmies(int armies);
    bool isOwner(Continent *continent);
    bool isOwner(Territory *territory);
    friend class Deploy;
    friend class Advance;
    friend class Airlift;
    friend class Bomb;
    friend class Blockade;
    friend class Negotiate;

private:
    string name;
    vector<Territory *> terrs;
    vector<Card *> cards;
    vector<Order *> orders;
    int *armies;
};
