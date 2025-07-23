#ifndef SUBJECT_H
#define SUBJECT_H

#include "AttackState.h"
#include "Info.h"
#include <vector>

/* A note on Info and State:

   We have separated the collection of fields into two parts: its Info
   and its State.

   Info is for the parts of the subject inherent to what it is: its position
   and its colour.

   State is for the parts of the subject that, when changed, trigger
   notifications.  This is the information that the Observer "gets" when it
   calls getState on the subject.  It comprises the type of state, a direction,
   and a colour.  For more details, see state.h.
*/

class Observer;

class Subject {
    std::vector<Observer*> observers;
    AttackState state;

public:
    void attach(Observer *newObv);
    void notifyObservers();
    virtual Info getInfo() const = 0;
    AttackState getAttackState() const;
    void setAttackState(AttackState newAttackState);
};

#endif