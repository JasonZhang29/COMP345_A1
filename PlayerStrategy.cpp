#include "PlayerStrategy.h"

PlayerStrategy::PlayerStrategy() {}

PlayerStrategy::PlayerStrategy(GameEngine *game, Player *player) : game(game), player(player) {}

PlayerStrategy::~PlayerStrategy() {}
//
//HumanPlayerStrategy::HumanPlayerStrategy() : PlayerStrategy() {}
//
//HumanPlayerStrategy::HumanPlayerStrategy(GameEngine *game, Player *player) : PlayerStrategy(game, player) {}
//
//HumanPlayerStrategy::~HumanPlayerStrategy() {}


BenevolentPlayerStrategy::BenevolentPlayerStrategy() {}
BenevolentPlayerStrategy::BenevolentPlayerStrategy(GameEngine* game, Player* player) : PlayerStrategy(game, player) {}
BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {}


//prompts the player to use a card
//void HumanPlayerStrategy::issueOrder() {
//
//    //use airlift cards
//    Card *airlift = player->getHand()->firstAirlift();
//    if (airlift == nullptr) {
//        cout << "You do not have any Airlift cards!" << endl;
//    }
//    while (airlift != nullptr) {
//        int choice = 0;
//        while (choice != 1 || choice != 2) {
//            cout << "You have Airlift cards. Would you like to use it?" << endl;
//            cout << "1. Yes" << endl;
//            cout << "2. No" << endl;
//            cin >> choice;
//            if (choice < 1 || choice > 2) {
//                cout << "Please enter a valid number!" << endl;
//            } else {
//                switch (choice) {
//                    case 1: {
//                        Territory *source;
//                        Territory *target;
//                        do {
//                            //choose source territory
//                            int choice1 = 0;
//                            while (choice1 < 1 || choice1 > player->getTerritories().size()) {
//                                cout << "Please choose a source territory:" << endl;
//                                for (int i = 0; i < player->getTerritories().size(); i++) {
//                                    cout << i + 1 << ". " << player->getTerritories()[i]->getName() << endl;
//                                }
//                                cin >> choice1;
//                                if (choice1 < 1 || choice1 > player->getTerritories().size()) {
//                                    cout << "Please enter a valid number!" << endl;
//                                } else {
//                                    source = player->getTerritories()[choice1 - 1];
//                                }
//                            }
//                            cout << "Please choose a target territory:" << endl;
//                            //choose target territory
//                            int choice2 = 0;
//                            while (choice2 < 1 || choice2 > game->getMap()->getTerritories().size()) {
//                                cout << "Please choose a target territory:" << endl;
//                                for (int i = 0; i < game->getMap()->getTerritories().size(); i++) {
//                                    cout << i + 1 << ". " << game->getMap()->getTerritories()[i]->getName() << endl;
//                                }
//                                cin >> choice2;
//                                if (choice2 < 1 || choice2 > player->getTerritories().size()) {
//                                    cout << "Please enter a valid number!" << endl;
//                                } else {
//                                    target = game->getMap()->getTerritories()[choice2 - 1];
//                                }
//                            }
//                            if (source == target) {
//                                cout
//                                        << "The source country and the target country cannot be the same! Please choose again!"
//                                        << endl;
//                            }
//                        } while (source == target);
//                        int numOfArmies = -1;
//                        while (numOfArmies < 0 || numOfArmies > *source->getNumberOfArmies()) {
//                            cout << "You have " << *source->getNumberOfArmies()
//                                 << " armies in the source country." << endl;
//                            cout << "Please enter the number of armies you would like to transfer:" << endl;
//                            cin >> numOfArmies;
//                            if (numOfArmies < 0 || numOfArmies > *source->getNumberOfArmies()) {
//                                cout << "Please enter a valid number!" << endl;
//                            }
//                        }
//                        player->getOrders().push_back(new Airlift(player, source, target, numOfArmies));
//                        airlift->play();
//                        airlift = player->getHand()->firstAirlift();
//                        break;
//                    }
//                    case 2: {
//                        cout << "Got it!" << endl;
//                        airlift = nullptr;
//                        break;
//                    }
//                }
//            }
//        }
//    }
//
//    //use blockade cards
//    Card *blockade = player->getHand()->firstBlockade();
//    if (blockade == nullptr) {
//        cout << "You do not have any Blockade cards!" << endl;
//    }
//    while (blockade != nullptr) {
//        int choice = 0;
//        while (choice != 1 || choice != 2) {
//            cout << "You have Blockade cards. Would you like to use it?" << endl;
//            cout << "1. Yes" << endl;
//            cout << "2. No" << endl;
//            cin >> choice;
//            if (choice < 1 || choice > 2) {
//                cout << "Please enter a valid number!" << endl;
//            } else {
//                switch (choice) {
//                    case 1: {
//                        int choice = 0;
//                        while (choice < 1 || choice > player->getTerritories().size()) {
//                            cout << "Please choose a territory you would like to use the card on:" << endl;
//                            for (int i = 0; i < player->getTerritories().size(); i++) {
//                                cout << i + 1 << ". " << player->getTerritories()[i]->getName() << endl;
//                            }
//                            cin >> choice;
//                            if (choice < 1 || choice > player->getTerritories().size()) {
//                                cout << "Please enter a valid number!" << endl;
//                            }
//                        }
//                        player->getOrders().push_back(new Blockade(player, player->getTerritories()[choice - 1]));
//                        blockade->play();
//                        blockade = player->getHand()->firstBlockade();
//                        break;
//                    }
//
//                    case 2: {
//                        cout << "Got it!" << endl;
//                        blockade = nullptr;
//                        break;
//                    }
//                }
//            }
//        }
//    }
//
//    //use other cards
//    int choice = 0;
//    while (choice != 4) {
//        cout << "What other cards would you like to use?" << endl;
//        cout << "1. Bomb" << endl;
//        cout << "2. Reinforcement" << endl;
//        cout << "3. Diplomacy" << endl;
//        cout << "4. Proceed to Advance" << endl;
//        cin >> choice;
//        if (choice < 1 || choice > 4) {
//            cout << "Please enter a valid number!" << endl;
//        } else {
//            switch (choice) {
//
//                //bomb
//                case 1: {
//                    Card *bomb = player->getHand()->firstBomb();
//                    if (bomb == nullptr) {
//                        cout << "You do not have any Bomb cards!" << endl;
//                    } else {
//                        Territory *target;
//                        cout << "Please choose a target territory:" << endl;
//                        int choice1 = 0;
//                        while (choice1 < 1 || choice1 > game->getMap()->getTerritories().size()) {
//                            cout << "Please choose a target territory:" << endl;
//                            for (int i = 0; i <= game->getMap()->getTerritories().size(); i++) {
//                                cout << i + 1 << ". " << game->getMap()->getTerritories()[i]->getName() << endl;
//                            }
//                            cin >> choice1;
//                            if (choice1 < 1 || choice1 > player->getTerritories().size()) {
//                                cout << "Please enter a valid number!" << endl;
//                            } else {
//                                target = game->getMap()->getTerritories()[choice1 - 1];
//                            }
//                        }
//                        player->getOrders().push_back(new Bomb(player, target));
//                        bomb->play();
//                    }
//                    break;
//                }
//
//                    //reinforcement
//                case 2: {
//                    Card *reinforcement = player->getHand()->firstReinforcement();
//                    if (reinforcement == nullptr) {
//                        cout << "You do not have any Reinforcement cards!" << endl;
//                    } else {
//                        cout << "You got 5 reinforce armies from this card!" << endl;
//                        player->addArmies(5);
//                        reinforcement->play();
//                    }
//                    break;
//                };
//
//                    //diplomacy
//                case 3: {
//                    Card *diplomacy = player->getHand()->firstDiplomacy();
//                    if (diplomacy == nullptr) {
//                        cout << "You do not have any Diplomacy cards!" << endl;
//                    } else {
//                        int choice1 = 0;
//                        while (choice1 < 1 || choice1 > game->getPlayers().size()) {
//                            cout << "Please choose a player:" << endl;
//                            for (int i = 0; i < game->getPlayers().size(); i++) {
//                                cout << i + 1 << ". " << game->getPlayers()[i]->getName() << endl;
//                            }
//                            cin >> choice1;
//                            if (choice1 < 1 || choice1 > game->getPlayers().size()) {
//                                cout << "Please enter a valid number!" << endl;
//                            }
//                        }
//                        player->getOrders().push_back(new Negotiate(player, game->getPlayers()[choice1 - 1]));
//                        diplomacy->play();
//                    }
//                    break;
//                }
//
//                    //exit
//                case 4: {
//                    cout << "Got it!" << endl;
//                    break;
//                }
//            }
//        }
//    }
//}
//
////prompts player to advance armies to attack enemies' territories
//void HumanPlayerStrategy::toAttack() {
//    int choice=0;
//    while(choice!=2){
//        cout<<"Would you like to attack a territory?"<<endl;
//        cout<<"1. Yes"<<endl;
//        cout<<"2. No"<<endl;
//        cin>>choice;
//        if(choice==1){
//            //choose a source territory
//            cout << "Please choose a source territory:" << endl;
//            Territory* source;
//            for (int i = 0; i < player->getTerritories().size(); i++) {
//                cout << i + 1 << ". " << player->getTerritories()[i]->getName() << endl;
//            }
//            int choice1 = 0;
//            while (choice1 < 1 || choice1 > player->getTerritories().size()) {
//                cin >> choice1;
//                if (choice1 < 1 || choice1 > player->getTerritories().size()) {
//                    cout << "Please enter a valid number!" << endl;
//                } else {
//                    source = player->getTerritories()[choice1 - 1];
//                }
//            }
//            //choose a target territory
//            cout << "Please choose a target territory:" << endl;
//            Territory* target;
//            vector<Territory*> enemies=source->getEnemyNeighbours();
//            for (int i = 0; i < enemies.size(); i++) {
//                cout << i+1 << ". " << enemies[i]->getName() << endl;
//            }
//            int choice2 = 0;
//            while (choice2 < 1 || choice2 > enemies.size()) {
//                cin >> choice;
//                if (choice2 < 1 || choice2 > enemies.size()) {
//                    cout << "Please enter a valid number!" << endl;
//                } else {
//                    target = enemies[choice2 - 1];
//                }
//            }
//            //choose the number of armies to advance
//            int numOfArmies = -1;
//            while (numOfArmies < 0 || numOfArmies > *source->getNumberOfArmies()) {
//                cout << "You have " << *source->getNumberOfArmies()<< " armies in the source country." << endl;
//                cout << "Please enter the number of armies you would like to transfer:" << endl;
//                cin >> numOfArmies;
//                if (numOfArmies < 0 || numOfArmies > *source->getNumberOfArmies()) {
//                    cout << "Please enter a valid number!" << endl;
//                }
//            }
//            player->getOrders().push_back(new Advance(player, source, target, numOfArmies));
//        }
//        else if(choice==2){
//            cout<<"Got it!"<<endl;
//        }
//        else{
//            cout<<"Please enter a valid number!"<<endl;
//        }
//    }
//}
//
//void HumanPlayerStrategy::toDefend(int i) {
//    switch (i) {
//
//        //deploy armies in reinforcement  pool
//        case 1:
//            cout << "You have " << *player->getArmies() << " spare armies in total." << endl;
//            while (*player->getArmies() != 0) {
//                cout << "Your territories:" << endl;
//                for (int i = 0; i < player->getTerritories().size(); i++) {
//                    cout << i + 1 << ". " << player->getTerritories()[i]->getName() << endl;
//                }
//                cout << "You have " << *player->getArmies() << " spare armies left." << endl;
//                bool validFlag = false;
//                int indexTerritory;
//                cout << "Please enter the index of territory you would like to defend:" << endl;
//                while (!validFlag) {
//                    cin >> indexTerritory;
//                    if (indexTerritory > player->getTerritories().size() || indexTerritory < 1) {
//                        cout << "Please enter a valid number!" << endl;
//                    } else {
//                        validFlag = true;
//                    }
//                }
//                int numOfArmies = 0;
//                cout << "Please enter the number of armies you would like to use:" << endl;
//                validFlag = false;
//                while (!validFlag) {
//                    cin >> numOfArmies;
//                    if (numOfArmies > *player->getArmies() || numOfArmies < 0) {
//                        cout << "Please enter a valid number!" << endl;
//                    } else {
//                        player->getOrders().push_back(new Deploy(player, player->getTerritories()[indexTerritory - 1], numOfArmies));
//                        validFlag = true;
//                    }
//                }
//            }
//            break;
//
//        //advance armies to defend territories
//        case 2:
//            int choice=0;
//            cout<<"Would you like to defend a territory?"<<endl;
//            cout<<"1. Yes"<<endl;
//            cout<<"2. No"<<endl;
//            while(choice!=2){
//                cin>>choice;
//                if(choice==1){
//                    //choose a source territory
//                    cout << "Please choose a source territory:" << endl;
//                    Territory* source;
//                    for (int i = 0; i < player->getTerritories().size(); i++) {
//                        cout << i + 1 << ". " << player->getTerritories()[i]->getName() << endl;
//                    }
//                    int choice1 = 0;
//                    while (choice1 < 1 || choice1 > player->getTerritories().size()) {
//                        cin >> choice1;
//                        if (choice1 < 1 || choice1 > player->getTerritories().size()) {
//                            cout << "Please enter a valid number!" << endl;
//                        } else {
//                            source = player->getTerritories()[choice1 - 1];
//                        }
//                    }
//                    //choose a target territory
//                    cout << "Please choose a target territory:" << endl;
//                    Territory* target;
//                    vector<Territory*> friends=source->getFriendlyNeighbours();
//                    for (int i = 0; i < friends.size(); i++) {
//                        cout << i+1 << ". " << friends[i]->getName() << endl;
//                    }
//                    int choice2 = 0;
//                    while (choice2 < 1 || choice2 > friends.size()) {
//                        cin >> choice;
//                        if (choice2 < 1 || choice2 > friends.size()) {
//                            cout << "Please enter a valid number!" << endl;
//                        } else {
//                            target = friends[choice2 - 1];
//                        }
//                    }
//                    //choose the number of armies to advance
//                    int numOfArmies = -1;
//                    while (numOfArmies < 0 || numOfArmies > *source->getNumberOfArmies()) {
//                        cout << "You have " << *source->getNumberOfArmies()<< " armies in the source country." << endl;
//                        cout << "Please enter the number of armies you would like to transfer:" << endl;
//                        cin >> numOfArmies;
//                        if (numOfArmies < 0 || numOfArmies > *source->getNumberOfArmies()) {
//                            cout << "Please enter a valid number!" << endl;
//                        }
//                    }
//                    player->getOrders().push_back(new Advance(player, source, target, numOfArmies));
//                }
//                else if(choice==2){
//                    cout<<"Got it!"<<endl;
//                }
//                else{
//                    cout<<"Please enter a valid number!"<<endl;
//                }
//            }
//            break;
//    }
//}

void NeutralPlayerStrategy::issueOrder() {
    cout<<player->getName()<<" is neutral and did nothing."<<endl;
}

void NeutralPlayerStrategy::toAttack() {
    cout<<player->getName()<<" is neutral and did nothing."<<endl;
}

void NeutralPlayerStrategy::toDefend(int i) {
    cout<<player->getName()<<" is neutral and did nothing."<<endl;
}



void BenevolentPlayerStrategy::issueOrder(){

}

void BenevolentPlayerStrategy::toAttack() {

}

void BenevolentPlayerStrategy::toDefend(int i) {
}

