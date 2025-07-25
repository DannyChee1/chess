#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <iostream>
#include <vector>
#include <string>
#include "Observer.h"
#include "AttackState.h"
#include "Info.h"

class TextDisplay : public Observer {
    std::vector<std::vector<char>> charDisplay;
    std::vector<std::vector<std::string>> stringDisplay;
    const int boardSize;
    bool enableBonus;

public:
    TextDisplay(std::string setupString, int n, bool enableBonus = false);
    void notify(Subject &sender) override;

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

std::ostream &operator<<(std::ostream &out, const TextDisplay &td);

#endif