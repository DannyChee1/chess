#include "Subject.h"
#include "Observer.h"

void Subject::attach(Observer *newObv) {
    observers.emplace_back(newObv);
}

void Subject::notifyObservers() {
    for (auto &obser : observers)
        obser->notify(*this);
}

void Subject::setAttackState(AttackState newAttackState) { 
    state = newAttackState;
}

AttackState Subject::getAttackState() const { 
    return state; 
}