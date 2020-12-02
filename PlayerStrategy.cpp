#include "PlayerStrategy.h"

void HumanPlayerStrategy::issueOrder(Player *player, int i) {
    switch (i) {

        //deploy orders
        case 1:
            cout << player->getName() << ", it's your turn!" << endl;
            cout << "You have " << *player->getArmies() << " spare armies in total." << endl;
            vector<Territory *> defend = player->toDefend();
            while (*player->getArmies() != 0) {
                cout << "Your territories to defend:" << endl;
                for (int j = 1; j <= defend.size(); j++) {
                    cout << j << ". " << defend[j - 1]->getName() << endl;
                }
                cout << "You have " << *player->getArmies() << " spare armies left." << endl;
                bool validFlag = false;
                int indexTerritory;
                cout << "Please enter the index of territory you would like to defend:" << endl;
                while (!validFlag) {
                    cin >> indexTerritory;
                    if (indexTerritory > defend.size() || indexTerritory < 1) {
                        cout << "Please enter a valid number!" << endl;
                    } else {
                        validFlag = true;
                    }
                }
                int numOfArmies = 0;
                cout << "Please enter the number of armies you would like to use:" << endl;
                validFlag = false;
                while (!validFlag) {
                    cin >> numOfArmies;
                    if (numOfArmies > *player->getArmies() || numOfArmies < 0) {
                        cout << "Please enter a valid number!" << endl;
                    } else {
                        player->issueOrder("deploy", defend[indexTerritory - 1], numOfArmies);
                        validFlag = true;
                    }
                }
            }

            break;

            //other orders
        case 2:
            cout << player->getName() << ", it's your turn!" << endl;

            //use airlift cards
            Card *airlift = player->getHand()->firstAirlift();
            if (airlift == nullptr) {
                cout << "You do not have any Airlift cards!" << endl;
            }
            while (airlift != nullptr) {
                int choice = 0;
                while (choice != 1 || choice != 2) {
                    cout << "You have Airlift cards. Would you like to use it?" << endl;
                    cout << "1. Yes" << endl;
                    cout << "2. No" << endl;
                    cin >> choice;
                    if (choice < 1 || choice > 2) {
                        cout << "Please enter a valid number!" << endl;
                    } else {
                        switch (choice) {
                            case 1: {
                                Territory *source;
                                Territory *target;
                                do {
                                    int choice1 = 0;
                                    while (choice1 < 1 || choice1 > player->getTerritories().size()) {
                                        cout << "Please choose a source territory:" << endl;
                                        for (int j = 1; j <= player->getTerritories().size(); j++) {
                                            cout << i << ". " << player->getTerritories()[j]->getName() << endl;
                                        }
                                        cin >> choice1;
                                        if (choice1 < 1 || choice1 > player->getTerritories().size()) {
                                            cout << "Please enter a valid number!" << endl;
                                        } else {
                                            source = player->getTerritories()[choice1 - 1];
                                        }
                                    }
                                    cout << "Please choose a target territory:" << endl;
                                    int choice2 = 0;
                                    while (choice2 < 1 || choice2 > gameMap->getTerritories().size()) {
                                        cout << "Please choose a target territory:" << endl;
                                        for (int j = 1; j <= gameMap->getTerritories().size(); j++) {
                                            cout << i << ". " << gameMap->getTerritories()[j]->getName() << endl;
                                        }
                                        cin >> choice2;
                                        if (choice2 < 1 || choice2 > players[i]->getTerritories().size()) {
                                            cout << "Please enter a valid number!" << endl;
                                        } else {
                                            target = gameMap->getTerritories()[choice2 - 1];
                                        }
                                    }
                                    if (source == target) {
                                        cout
                                                << "The source country and the target country cannot be the same! Please choose again!"
                                                << endl;
                                    }
                                } while (source == target);
                                int numOfArmies = -1;
                                while (numOfArmies < 0 || numOfArmies > *source->getNumberOfArmies()) {
                                    cout << "You have " << *source->getNumberOfArmies()
                                         << " armies in the source country." << endl;
                                    cout << "Please enter the number of armies you would like to transfer:" << endl;
                                    cin >> numOfArmies;
                                    if (numOfArmies < 0 || numOfArmies > *source->getNumberOfArmies()) {
                                        cout << "Please enter a valid number!" << endl;
                                    }
                                }
                                player->issueOrder("airlift", source, target, numOfArmies);
                                airlift->play();
                                airlift = player->getHand()->firstAirlift();
                                break;
                            }

                            case 2: {
                                cout << "Got it!" << endl;
                                break;
                            }
                        }
                    }
                }
            }

            //use blockade cards
            Card *blockade = player->getHand()->firstBlockade();
            if (blockade == nullptr) {
                cout << "You do not have any Blockade cards!" << endl;
            }
            while (blockade != nullptr) {
                int choice = 0;
                while (choice != 1 || choice != 2) {
                    cout << "You have Blockade cards. Would you like to use it?" << endl;
                    cout << "1. Yes" << endl;
                    cout << "2. No" << endl;
                    cin >> choice;
                    if (choice < 1 || choice > 2) {
                        cout << "Please enter a valid number!" << endl;
                    } else {
                        switch (choice) {
                            case 1: {
                                int choice = 0;
                                while (choice < 1 || choice > player->getTerritories().size()) {
                                    cout << "Please choose a territory you would like to use the card on:" << endl;
                                    for (int j = 1; j <= player->getTerritories().size(); j++) {
                                        cout << i << ". " << player->getTerritories()[j]->getName() << endl;
                                    }
                                    cin >> choice;
                                    if (choice < 1 || choice > player->getTerritories().size()) {
                                        cout << "Please enter a valid number!" << endl;
                                    }
                                }
                                player->issueOrder("blockade", player->getTerritories()[choice - 1]);
                                blockade->play();
                                blockade = player->getHand()->firstBlockade();
                                break;
                            }

                            case 2: {
                                cout << "Got it!" << endl;
                                break;
                            }
                        }
                    }
                }
            }

            int choice = 0;
            while (choice != 3) {
                cout << "What else would you like to do?" << endl;
                cout << "1. Advance" << endl;
                cout << "2. Use other cards" << endl;
                cout << "3. Exit" << endl;
                cin >> choice;
                if (choice < 1 || choice > 3) {
                    cout << "Pleace enter a valid number!" << endl;
                } else {
                    switch (choice) {
                        //advance
                        case 1: {
                            Territory *source;
                            Territory *target;
                            int choice1 = 0;
                            while (choice1 < 1 || choice1 > player->getTerritories().size()) {
                                cout << "Please choose a source territory:" << endl;
                                for (int j = 1; j <= player->getTerritories().size(); j++) {
                                    cout << j << ". " << player->getTerritories()[j - 1]->getName() << endl;
                                }
                                cin >> choice1;
                                if (choice1 < 1 || choice1 > player->getTerritories().size()) {
                                    cout << "Please enter a valid number!" << endl;
                                } else {
                                    source = player->getTerritories()[choice1 - 1];
                                }
                            }
                            int choice2 = 0;
                            vector<Territory *> terrs;
                            while (choice2 != 3) {
                                cout << "Would you like to defend or attack?" << endl;
                                cout << "1. Defend" << endl;
                                cout << "2. Attack" << endl;
                                cout << "3. Exit" << endl;
                                cin >> choice2;
                                if (choice2 < 1 || choice2 > 3) {
                                    cout << "Please enter a valid number!" << endl;
                                }
                                    //choose to defend
                                else if (choice2 == 1) {
                                    terrs = player->toDefend();
                                    cout << "Please choose a target territory:" << endl;
                                    for (int j = 1; j <= terrs.size(); j++) {
                                        cout << j << ". " << terrs[j - 1]->getName() << endl;
                                    }
                                    int choice3 = 0;
                                    while (choice3 < 1 || choice2 > terrs.size()) {
                                        cin >> choice3;
                                        if (choice3 < 1 || choice3 > terrs.size()) {
                                            cout << "Please enter a valid number!" << endl;
                                        } else {
                                            target = terrs[choice3 - 1];
                                        }
                                    }
                                    int numOfArmies = -1;
                                    while (numOfArmies < 0 || numOfArmies > *source->getNumberOfArmies()) {
                                        cout << "You have " << *source->getNumberOfArmies()
                                             << " armies in the source country." << endl;
                                        cout << "Please enter the number of armies you would like to transfer:" << endl;
                                        cin >> numOfArmies;
                                        if (numOfArmies < 0 || numOfArmies > *source->getNumberOfArmies()) {
                                            cout << "Please enter a valid number!" << endl;
                                        }
                                    }
                                    player->issueOrder("advance", source, target, numOfArmies);
                                }
                                    //choose to attack
                                else if (choice2 == 2) {
                                    terrs = player->toAttack(source);
                                    cout << "Please choose a target territory:" << endl;
                                    for (int j = 1; j <= terrs.size(); j++) {
                                        cout << j << ". " << terrs[j - 1]->getName() << endl;
                                    }
                                    int choice3 = 0;
                                    while (true) {
                                        cin >> choice3;
                                        if (choice3 < 1 || choice3 > terrs.size()) {
                                            cout << "Please enter a valid number!" << endl;
                                        } else {
                                            target = terrs[choice3 - 1];
                                            break;
                                        }
                                    }
                                    int numOfArmies = -1;
                                    while (numOfArmies < 0 || numOfArmies > *source->getNumberOfArmies()) {
                                        cout << "You have " << *source->getNumberOfArmies()
                                             << " armies in the source country." << endl;
                                        cout << "Please enter the number of armies you would like to transfer:" << endl;
                                        cin >> numOfArmies;
                                        if (numOfArmies < 0 || numOfArmies > *source->getNumberOfArmies()) {
                                            cout << "Please enter a valid number!" << endl;
                                        }
                                    }
                                    player->issueOrder("advance", source, target, numOfArmies);
                                }
                                    //exit
                                else if (choice2 == 3) {
                                    cout << "Got it!" << endl;
                                }
                            }
                            break;
                        }

                            //use a card
                        case 2: {
                            int choice = 0;
                            while (choice != 4) {
                                cout << "Please choose from the list:" << endl;
                                cout << "1. Bomb" << endl;
                                cout << "2. Reinforcement" << endl;
                                cout << "3. Diplomacy" << endl;
                                cout << "4. Return to the upper menu" << endl;
                                cin >> choice;
                                if (choice < 1 || choice > 4) {
                                    cout << "Please enter a valid number!" << endl;
                                } else {
                                    switch (choice) {

                                        //bomb
                                        case 1: {
                                            Card *bomb = player->getHand()->firstBomb();
                                            if (bomb == nullptr) {
                                                cout << "You do not have any Bomb cards!" << endl;
                                            } else {
                                                Territory *target;
                                                cout << "Please choose a target territory:" << endl;
                                                int choice1 = 0;
                                                while (choice1 < 1 || choice1 > game.getMap()->getTerritories().size()) {
                                                    cout << "Please choose a target territory:" << endl;
                                                    for (int j = 1; j <= gameMap->getTerritories().size(); j++) {
                                                        cout << i << ". " << gameMap->getTerritories()[j]->getName()
                                                             << endl;
                                                    }
                                                    cin >> choice1;
                                                    if (choice1 < 1 ||
                                                        choice1 > players[i]->getTerritories().size()) {
                                                        cout << "Please enter a valid number!" << endl;
                                                    } else {
                                                        target = gameMap->getTerritories()[choice1 - 1];
                                                    }
                                                }
                                                player->issueOrder("bomb", target);
                                                bomb->play();
                                            }
                                            break;
                                        }

                                            //reinforcement
                                        case 2: {
                                            Card *reinforcement = player->getHand()->firstReinforcement();
                                            if (reinforcement == nullptr) {
                                                cout << "You do not have any Reinforcement cards!" << endl;
                                            } else {
                                                cout << "You got 5 reinforce armies from this card!" << endl;
                                                player->addArmies(5);
                                                reinforcement->play();
                                            }
                                            break;
                                        };

                                            //diplomacy
                                        case 3: {
                                            Card *diplomacy = player->getHand()->firstDiplomacy();
                                            if (diplomacy == nullptr) {
                                                cout << "You do not have any Diplomacy cards!" << endl;
                                            } else {
                                                int choice1 = 0;
                                                while (choice1 < 1 || choice1 > gameMap.getPlayers().size()) {
                                                    cout << "Please choose a player:" << endl;
                                                    for (int j = 1; j <= gameMap.getPlayers().size(); j++) {
                                                        cout << i << ". " << gameMap.getPlayers()[j]->getName() << endl;
                                                    }
                                                    cin >> choice1;
                                                }
                                                player->issueOrder("diplomacy", gameMap.getPlayers()[choice]);
                                                diplomacy->play();
                                            }
                                            break;
                                        }

                                            //return
                                        case 4: {
                                            cout << "Got it!" << endl;
                                            break;
                                        }
                                    }
                                }
                            }
                            break;
                        }

                            //exit
                        case 3: {
                            cout << "Your round is over." << endl;
                            break;
                        }
                    }
                }
            }
            break;
    }
}

void HumanPlayerStrategy::toAttack(Player *player) {

}

void HumanPlayerStrategy::toDefend(Player *player) {

}

void NeutralPlayerStrategy::issueOrder(Player *player, int i) {

}

void NeutralPlayerStrategy::toAttack(Player *player) {

}

void NeutralPlayerStrategy::toDefend(Player *player) {

}