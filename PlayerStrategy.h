#pragma once
#include <iostream>
#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "Orders.h"
#include "GameEngine.h"
using namespace std;

class PlayerStrategy {
protected:
    GameEngine* game;
    Player* player;
public:
    PlayerStrategy();
    PlayerStrategy(GameEngine* game, Player* player);
    ~PlayerStrategy();
    virtual void issueOrder() = 0;
    virtual void toAttack() = 0;
    virtual void toDefend(int i) = 0;
};

//class HumanPlayerStrategy:public PlayerStrategy{
//public:
//    HumanPlayerStrategy();
//    HumanPlayerStrategy(GameEngine* game, Player* player);
//    ~HumanPlayerStrategy();
//    void issueOrder();
//    void toAttack();
//    void toDefend(int i);
//};

//class AggressivePlayerStrategy:public PlayerStrategy{
//public:
//    AggressivePlayerStrategy();
//    AggressivePlayerStrategy(GameEngine* game, Player* player);
//    ~AggressivePlayerStrategy();
//    void issueOrder();
//    void toAttack();
//    void toDefend(int i);
//};

class BenevolentPlayerStrategy:public PlayerStrategy{
public:
    BenevolentPlayerStrategy();
    BenevolentPlayerStrategy(GameEngine* game, Player* player);
    ~BenevolentPlayerStrategy();
    void issueOrder();
    void toAttack();
    void toDefend(int i);
};

class NeutralPlayerStrategy:public PlayerStrategy{
public:
    NeutralPlayerStrategy();
    NeutralPlayerStrategy(GameEngine* game, Player* player);
    ~NeutralPlayerStrategy();
    void issueOrder();
    void toAttack();
    void toDefend(int i);
};