#pragma once

#include <iostream>
#include <map>
#include <memory>

#include "../game/structures.h"

class Player {
public:
    Player(std::string name, char color);
    void init_pawns();
    
    virtual step_t make_step(const std::shared_ptr<Player> &enemy) const;
    virtual void on_incorrect_step(const step_t &step) const;
    step_type move_pawn(const step_t &step);
    void remove_pawn(const position_t &position);
    void print_field(const std::shared_ptr<Player> &enemy) const;
    
    bool can_go(const std::shared_ptr<Player> &enemy) const;
    bool can_eat(const std::shared_ptr<Player> &enemy) const;
    bool can_eat(position_t p_position, const std::shared_ptr<Player> &enemy) const;

    virtual void on_lose();
    virtual void on_win();
    virtual void on_tie();
    
    char get_color() const {return color;}
    std::string get_name() const {return name;}
    
    enum cell_type {
        ME,
        ENEMY,
        EMPTY
    };
    cell_type check_cell(const position_t &pos, const std::shared_ptr<Player> &enemy) const;
    size_t pawns_count() const;
    
    pawn_type get_pawn_type(const position_t &pos);
    
protected:
    const char color;
    std::string name;
    std::map<position_t, pawn_type> pawns;
    
    enum input_type {
        NUMBER,
        LETTER
    };
    int define_index(char letter, input_type t) const;
};
