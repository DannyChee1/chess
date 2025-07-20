#include "subject.h"
#include "observer.h"

void Subject::attach(Observer *newObv) {
    observers.emplace_back(newObv);
}

void Subject::notifyObservers() {
    for (auto &obser : observers) {
    obser->notify(*this);}
}

void Subject::setAttackState(attackState newAttackState) { 
    state = newAttackState;
}

attackState Subject::getAttackState() const { 
    return state; 
}