#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <iostream>
#include <vector>
#include <string>
#include "Observer.h"
#include "AttackState.h"
#include "Info.h"

class TextDisplay : public Observer {
    std::vector<std::vector<char>> display;
    const int boardSize;

public:
    TextDisplay(std::string setupString, int n);
    void notify(Subject &sender) override;

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

std::ostream &operator<<(std::ostream &out, const TextDisplay &td);

#endif
