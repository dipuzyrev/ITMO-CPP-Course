#pragma once

#include <algorithm>

struct position_t {
    position_t(): x{0}, y{0} {}
    position_t(int x, int y): x{x}, y{y} {}
    int x, y;
};

enum step_type {
    STEP,
    EAT,
    BECOME_KING,
    WRONG
};

struct step_t {
    step_t():
    before{position_t(0,0)},
    after{position_t(0,0)} {}
    
    step_t(position_t before, position_t after):
        before{before},
        after{after} {}
    
    position_t before;
    position_t after;
};

enum pawn_type {
    MAN,
    KING,
    UNDEFINED
};

struct cell_t {
    position_t position;
    pawn_type p_type;
};
