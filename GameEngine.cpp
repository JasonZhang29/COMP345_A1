#include "GameEngine.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

Subject::Subject() {
    _observers = new list<Observer*>;
}

Subject::~Subject() {
    delete _observers;
}

void Subject::Attach(Observer* o) {
    _observers->push_back(o);
};

void Subject::Detach(Observer* o) {
    _observers->remove(o);
};

void Subject::Notify() {
    list<Observer*>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i)
        (*i)->Update();
};

GameEngine::GameEngine()
{
    // define array for candidate maps
    static const string mapName[] = {"artic", "austria-hungary", "solar"};

    // randomly select a map to open
    gameMap= nullptr;
    MapLoader *ml = new MapLoader();
    while(gameMap==nullptr){
        int mapId=0;
        while(mapId<1||mapId>4) {
            cout << "Please select a map from the list:" << endl;
            cout << "1. Artic" << endl;
            cout << "2. Austria-Hungary" << endl;
            cout << "3. Solar" << endl;
            cin >> mapId;
            if(mapId<1||mapId>3){
                cout<<"Please enter a valid number!"<<endl;
            }
        }
        string mapFileName = "./" + mapName[mapId - 1] + ".map";
        // use Maploader to load selected map
        gameMap = ml->readMap(mapFileName);
    }

    // create a deck of cards and display
    cout<<"--------------"<<endl;
    deck=new Deck();
    cout<<"Deck created:"<<endl;
    for(Card* c:deck->getCards()){
        cout<<*c;
    }
    cout<<"--------------"<<endl;


    // create 2-5 players
    int numOfPlayer=0;
    while(numOfPlayer<2||numOfPlayer>5) {
        cout << "Please enter the number of players (2-5):" << endl;
        cin >> numOfPlayer;
        if(numOfPlayer<2||numOfPlayer>5){
            cout<<"Please enter a valid number!"<<endl;
        }
    }
    //asks user to input name
    for (int i = 0; i < numOfPlayer; ++i)
    {
        string name;
        cout<<"Please enter a name for Player"<<i+1<<":"<<endl;
        cin>>name;
        players.push_back( new Player(name));
        players[i]->setHand(new Hand(players[i],deck));
    }
    //asks user to choose a strategy
    for (int i = 0; i < numOfPlayer; ++i)
    {
        int strategy=0;
        cout<<"Please choose a strategy for Player"<<i+1<<":"<<endl;
        cout<<"1. Human"<<endl;
        cout<<"2. Aggressive"<<endl;
        cout<<"3. Benevolent"<<endl;
        cout<<"4. Neutral"<<endl;
        while(strategy<1||strategy>4) {
            cin >> strategy;
            if(strategy<1||strategy>4){
                cout<<"Please enter a valid number!"<<endl;
            }
        }
        switch(strategy){
            case 1:
                //players[i]->setStrategy(new HumanPlayerStrategy(this,players[i]));
                break;

            case 2:
                //players[i]->setStrategy(new AggressivePlayerStrategy(this,players[i]));
                break;

            case 3:
                players[i]->setStrategy(new BenevolentPlayerStrategy(this,players[i]));
                break;

            case 4:
                //players[i]->setStrategy(new NeutralPlayerStrategy(this,players[i]));
                break;
        }
    }

}

GameEngine::~GameEngine() {

}

string GameEngine::getState() {
    return state;
}

Map* GameEngine::getMap() {
    return gameMap;
}

vector<Player *> GameEngine::getPlayers() {
    return players;
}

void GameEngine::mainGameLoop(){
    while (true)
    {
        this->reinforcementPhase();
        this->issueOrderPhase(1);
        this->executeOrderPhase();
        this->issueOrderPhase(2);
        this->executeOrderPhase();
        //check if a player owns no territories
        for (int i = 0; i < players.size(); i++)
        {
            if (players[i]->getTerritories().size() == 0)
            {
                cout << players[i]->getName() << " has no territories left and is removed from the game!" << endl;
                players.erase(players.begin() + i);
            }
        }
        //checks if a player has won the game
        for (int i = 0; i < players.size(); i++)
        {
            if (players[i]->getTerritories().size() == this->gameMap->getTerritories().size())
            {
                cout << "Congratulations! " << players[i]->getName() << " has won the game!" << endl;
                exit(0);
            }
        }
    }
}

void GameEngine::startupPhase()
{
    this->state="Strat Up Phase";
    Notify();
    //decide the order of play
    shuffle(players.begin(), players.end(), std::mt19937(std::random_device()()));
    cout << "---------------------" << endl;
    cout << "The order of play is:" << endl;
    for (int i = 0; i < players.size(); i++)
    {
        cout << i+1 << " " << players[i]->getName() << endl;
    }
    //randomly assign territories
    cout << "---------------------" << endl;
    cout << "Randomly assigning territories..." << endl;
    int numOfTerri;
    bool luckyFlag;
    //check if each players can get equal number of territories
    if (gameMap->getTerritories().size() % players.size() != 0)
    {
        numOfTerri = gameMap->getTerritories().size() / players.size() + 1;
        luckyFlag = true;
    }
    else
    {
        numOfTerri = gameMap->getTerritories().size() / players.size();
        luckyFlag = false;
    }
    for (int i = 0; i < gameMap->getTerritories().size(); i++)
    {
        int indexOfOwner;
        while (!gameMap->getTerritories()[i]->hasOwner())
        {
            indexOfOwner = rand() % players.size();
            if (players[indexOfOwner]->getTerritories().size() < numOfTerri)
            {
                players[indexOfOwner]->addTerritory(gameMap->getTerritories()[i]);
            }
        }
    }
    for (int i = 0; i < players.size(); i++)
    {
        cout << players[i]->getName() << ":" << endl;
        for (int j = 0; j < players[i]->getTerritories().size(); j++)
        {
            cout << "  " << j +1<< " " << players[i]->getTerritories()[j]->getName() << endl;
        }
        if (luckyFlag && players[i]->getTerritories().size() > numOfTerri-1)
        {
            cout << "You are lucky! You have got one more territory than the others!" << endl;
        }
        if (i < players.size())
        {
            cout << endl;
        }
    }
    //give initial armies
    cout << "---------------------" << endl;
    int numOfIniArmies;
    switch (players.size())
    {
        case 2:
            numOfIniArmies = 40;
            break;

        case 3:
            numOfIniArmies = 35;
            break;

        case 4:
            numOfIniArmies = 30;
            break;

        case 5:
            numOfIniArmies = 25;
            break;
    }
    cout << "Number of initial Armies: " << numOfIniArmies << endl;
    for (int i = 0; i < players.size(); i++)
    {
        players[i]->addArmies(numOfIniArmies);
    }
}

void GameEngine::reinforcementPhase(){
    this->state="Reinforcement Phase";
    Notify();
    cout << "---------------------" << endl;
    cout << "Reinforcement phase starts..." << endl;
    for (int i = 0; i < players.size(); i++)
    {
        int terriArmy = players[i]->getTerritories().size() / 3;
        if (terriArmy < 3)
        {
            terriArmy = 3;
        }
        cout << players[i]->getName() << " got " << terriArmy << " armies from owned territories." << endl;
        int conArmy = 0;
        for (int j = 0; j < gameMap->getContinents().size(); j++)
        {
            if (players[i]->isOwner(gameMap->getContinents()[j]))
            {
                conArmy += *gameMap->getContinents()[j]->getBonus();
            }
        }
        cout << players[i]->getName() << " got " << conArmy << " armies from owned continents." << endl;
        players[i]->addArmies(terriArmy + conArmy);
        cout << "Total: " << terriArmy + conArmy << endl;
    }
    cout << "Reinforcement phase ends..." << endl;
    cout << "---------------------" << endl;
}

void GameEngine::issueOrderPhase(int a){
    this->state="Issue order Phase";
    Notify();
    for(Player* player:players){
        cout << player->getName() << ", it's your turn!" << endl;
        switch(a) {
            case 1:
                player->toDefend(a);//only need to choose a target to put all the in hand armies
                break;
            case 2:
                player->issueOrder();
                player->toAttack();
                player->toDefend(a);//need to choose both source and target(advance)
                break;
        }
    }
}

void GameEngine::executeOrderPhase(){
    this->state="Execute Order Phase";
    Notify();
    cout<<"-------------------"<<endl;
    cout<<"Executing orders..."<<endl;
    for (int i = 0; i < players.size(); i++){
        for(int j=0; j<players[i]->getOrders().size();j++){
            players[i]->getOrders()[j]->execute();
        }
        players[i]->clearOrders();
    }
    cout<<"Orders executed!"<<endl;
    cout<<"-------------------"<<endl;
}