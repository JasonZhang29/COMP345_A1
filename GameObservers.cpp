#include "GameObservers.h"
#include "GameEngine.h"

Observer::Observer() {};
Observer::~Observer() {};
//
//Subject::Subject() {
//    _observers = new list<Observer*>;
//}
//Subject::~Subject() {
//    delete _observers;
//}
//void Subject::Attach(Observer* o) {
//    _observers->push_back(o);
//};
//void Subject::Detach(Observer* o) {
//    _observers->remove(o);
//};
//void Subject::Notify() {
//    list<Observer*>::iterator i = _observers->begin();
//    for (; i != _observers->end(); ++i)
//        (*i)->Update();
//};
//
//PhaseObserver::PhaseObserver() {}
//
//PhaseObserver::PhaseObserver(GameEngine* ge)
//{
//    _subject = ge;
//    _subject->Attach(this);
//}
//
//PhaseObserver::~PhaseObserver()
//{
//    _subject->Detach(this);
//}
//
//void PhaseObserver::Update()
//{
//    display();
//}
//
//void PhaseObserver::display()
//{
//    string currenState = _subject->getState();
//    cout << "Phase: " << currenState;
//}