#pragma once

#include "computer.h"
#include "../game/structures.h"

#include <map>
#include <memory>

class Computer1: public Computer {
public:
    Computer1(std::string name, char color);
    virtual step_t make_step(const std::shared_ptr<Player> &enemy) const;
private:
    step_t find_eating_option(const std::shared_ptr<Player> &enemy) const;
    step_t find_step_option(const std::shared_ptr<Player> &enemy) const;
};
