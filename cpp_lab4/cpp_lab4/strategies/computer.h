#pragma once

#include "player.h"
#include "../game/structures.h"

#include <map>
#include <memory>

class Computer: public Player {
public:
    Computer(std::string name, char color);
    
    virtual step_t make_step(const std::shared_ptr<Player> &enemy) const override = 0;
    virtual void on_incorrect_step(const step_t &step) const override;
    void print_stat() const;

    virtual void on_lose() override;
    virtual void on_win() override;
    virtual void on_tie() override;
private:
    size_t win_counter;
    size_t lose_counter;
    size_t tie_counter;
};
