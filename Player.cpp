#include "Player.h"
#include <vector>
using namespace std;

Player::Player()
{
}

Player::Player(const Player &p)
{
    this->name = p.name;
}

Player::Player(string pName)
{
    this->name = new string(pName);
    armies=new int(0);
}

Player::Player(const Player &p, string pName)
{
    for (auto it = p.terrs.begin(); it != p.terrs.end(); ++it)
    {
        this->terrs.push_back(*it);
    }
    this->name = new string(pName);
}

Player &Player::operator=(const Player &p)
{
    Player *p1 = new Player(p);
    Player &pCopy = *p1;
    return pCopy;
}

ostream &operator<<(ostream &out, const Player &p)
{
    out << p.toString();
    out << endl;
    return out;
}

string Player::toString() const
{
    string pInfo = "";
    pInfo += "Player " + this->getName() + "\'s info: \n";
    pInfo += "\tTerritory owned: \n";
    for (auto it = this->terrs.begin(); it != this->terrs.end(); ++it)
    {
        pInfo += (*it)->getName() + ", ";
    }
    pInfo += "\n\tCards owned: \n";
    for (auto it = this->hand->getCardsVector().begin(); it != this->hand->getCardsVector().end(); ++it)
    {
        pInfo += (*it)->getType() + ", ";
    }
    pInfo += "\n";
    return pInfo;
}

string Player::getName() const
{
    return *name;
}

vector<Territory*> Player::getTerritories() {
    return terrs;
}

void Player::addTerritory(Territory *territory) {
    territory->setOwner(this);
    this->terrs.push_back(territory);
}

int* Player::getArmies() {
    return armies;
}

void Player::addArmies(int armies) {
    *this->armies+=armies;
}

void Player::addCards(Hand* hand)
{
    vector<Card*> tempCardsVector = hand->getCardsVector();
    while (!tempCardsVector.empty()) {
        Card* tempCard = tempCardsVector.back();
        tempCardsVector.pop_back();
        hand->getCardsVector().push_back(tempCard);
    }
    
}

bool Player::isOwner(Continent *continent){
    for(Territory* t:continent->getTerritories()){
        if(!this->isOwner(t)){
            return false;
        }
    }
    return true;
}

bool Player::isOwner(Territory *territory) {
    for(int i=0; i<this->terrs.size();i++){
        if(territory==terrs[i]){
            return true;
        }
    }
    return false;
}

vector<Order *> Player::getOrders() {
    return orders;
}

Hand* Player::getHand() {
    return hand;
}

void Player::setHand(Hand* hand) {
    this->hand=hand;
}

Player::~Player(){

}

void Player::clearOrders() {
    orders.erase(orders.begin(),orders.end());
}

//vector<Territory *> Player::toAttack(Territory* source)
//{
//    vector<Territory *> terrAttack;
//    vector<Territory*> neighbours=source->getNeighbours();
//    cout<<"Please choose a list of countries you would like to attack:"<<endl;
//    for(int i=1;i<=neighbours.size();i++){
//        cout<<i<<". "<<neighbours[i-1]->getName()<<endl;
//    }
//    cout<<neighbours.size()+1<<". Exit"<<endl;
//    bool firstFlag=true;
//    int firstIndex;
//    while(firstFlag) {
//        cin>>firstIndex;
//        if (firstIndex == neighbours.size()+1) {
//            cout << "You have to choose at least one territory! Please enter another number:" << endl;
//        } else if (firstIndex > neighbours.size()) {
//            cout << "Please enter a valid number!" << endl;
//        } else {
//            terrAttack.push_back(neighbours[firstIndex-1]);
//            firstFlag = false;
//        }
//    }
//    int attackIndex=-1;
//    while(attackIndex!=neighbours.size()+1){
//        cin>>attackIndex;
//        if (attackIndex > neighbours.size()+1) {
//            cout << "Please enter a valid number!" << endl;
//        }
//        else if(attackIndex!=neighbours.size()+1){
//            terrAttack.push_back(neighbours[attackIndex-1]);
//        }
//    }
//    return terrAttack;
//}

//vector<Territory *> Player::toDefend()
//{
//    vector<Territory *> terrDefend;
//    cout<<"Please choose a list of countries you would like to defend:"<<endl;
//    for(int i=1;i<=this->terrs.size();i++){
//        cout<<i<<". "<<this->terrs[i-1]->getName()<<endl;
//    }
//    cout<<this->terrs.size()+1<<". Exit"<<endl;
//    bool firstFlag=true;
//    int firstIndex;
//    while(firstFlag) {
//        cin>>firstIndex;
//        if (firstIndex == this->terrs.size()+1) {
//            cout << "You have to choose at least one territory! Please enter another number:" << endl;
//        } else if (firstIndex > this->terrs.size()+1||firstIndex<1) {
//            cout << "Please enter a valid number!" << endl;
//        } else {
//            terrDefend.push_back(this->terrs[firstIndex-1]);
//            firstFlag = false;
//        }
//    }
//    int defendIndex;
//    while(defendIndex!=this->terrs.size()+1){
//        cin>>defendIndex;
//        if(defendIndex!=this->terrs.size()+1){
//            terrDefend.push_back(this->terrs[defendIndex-1]);
//        }
//        else if (defendIndex > this->terrs.size()+1||defendIndex<1) {
//            cout << "Please enter a valid number!" << endl;
//        }
//    }
//    return terrDefend;
//}

//void Player::issueOrder(string s, Territory* territory, int numOfArmies)
//{
//    if(s=="deploy"){
//        Deploy *deploy = new Deploy(this, territory, numOfArmies);
//        orders.push_back(deploy);
//        *this->armies-=numOfArmies;
//    }
//}

//void Player::issueOrder(string s, Territory * source, Territory * target, int numOfArmies) {
//    if(s=="airlift"){
//        Airlift *airlift = new Airlift(this, source, target, numOfArmies);
//        this->getOrders().push_back(airlift);
//    }
//    else if(s=="advance"){
//        Advance *advance=new Advance(this, source, target, numOfArmies);
//        orders.push_back(advance);
//    }
//}

//void Player::issueOrder(string s, Territory * t) {
//    if(s=="blockade"){
//        Blockade *blockade = new Blockade(this, t);
//        this->getOrders().push_back(blockade);
//    }
//    else if(s=="bomb"){
//        Bomb *bomb=new Bomb(this, t);
//        this->getOrders().push_back(bomb);
//    }
//}

//void Player::issueOrder(string s, Player * p) {
//    if(s=="diplomacy"){
//        Negotiate *negotiate = new Negotiate(this, p);
//        this->getOrders().push_back(negotiate);
//    }
//}

void Player::setStrategy(PlayerStrategy *s) {
    this->strategy=s;
}

void Player::toAttack() {
    strategy->toAttack();
}

void Player::toDefend(int i) {
    strategy->toDefend(i);
}

void Player::issueOrder() {
    strategy->issueOrder();
}


