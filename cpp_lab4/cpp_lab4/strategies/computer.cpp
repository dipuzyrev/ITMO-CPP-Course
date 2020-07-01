#include "computer.h"

#include <cassert>
#include <iostream>

Computer::Computer(std::string name, char color):
    Player(name, color),
    win_counter{0},
    lose_counter{0},
    tie_counter{0} {}

void Computer::on_incorrect_step(const step_t &step) const {
    assert(false);
}

void Computer::print_stat() const {
    std::cout << std::endl << name << ":" << std::endl;
    std::cout << "Wins:  " << win_counter << std::endl;
    std::cout << "Loses: " << lose_counter << std::endl;
    std::cout << "Ties:  " << tie_counter << std::endl;
}

void Computer::on_lose() {
    ++lose_counter;
}

void Computer::on_win() {
    ++win_counter;
}

void Computer::on_tie() {
    ++tie_counter;
}
