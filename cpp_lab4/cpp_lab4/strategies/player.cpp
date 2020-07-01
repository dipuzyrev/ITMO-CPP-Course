#include "player.h"

bool operator<(const position_t &pos1, const position_t &pos2) {
    if (pos1.x != pos2.x) {
        return pos1.x < pos2.x;
    } else {
        return pos1.y < pos2.y;
    }
}

Player::Player(std::string name, char color): name(name), color(color) {}


void Player::init_pawns() {
    
      /* Place pawns in start position:       A B C D E F G H
                                             -----------------
                                          8 | _ . _ . _ . _ . | 1
                                          7 | . _ . _ . _ . _ | 2
                                          6 | _ . _ . _ . _ . | 3
                                          5 | . _ . _ . _ . _ | 4
                                          4 | _ . _ . _ . _ . | 5
                                          3 | p _ p _ p _ p _ | 6
                                          2 | _ p _ p _ p _ p | 7
                                          1 | p _ p _ p _ p _ | 8
                                             -----------------
                                              A B C D E F G H     */
    pawns.clear();
    
    for (int i = 8; i >= 6; i--) {
          pawns[position_t(i, (i % 2) + 1)] = MAN;
          pawns[position_t(i, (i % 2) + 3)] = MAN;
          pawns[position_t(i, (i % 2) + 5)] = MAN;
          pawns[position_t(i, (i % 2) + 7)] = MAN;
      }
}

step_t Player::make_step(const std::shared_ptr<Player> &enemy) const {
    std::cout << std::endl;
    print_field(enemy);
    std::cout << std::endl << name << ", your turn!" << std::endl << "Input coordinates (like '6a 5b'): ";
    
    std::string input1, input2;
    std::cin >> input1 >> input2;
    
    position_t before, after;
    before = {define_index(input1[0], NUMBER), define_index(input1[1], LETTER)};
    after = {define_index(input2[0], NUMBER), define_index(input2[1], LETTER)};
    
//    std::cout << define_index(input1[0], NUMBER) << ' ' << define_index(input1[1], LETTER) << ' ' << define_index(input2[0], NUMBER) << ' ' << define_index(input2[1], LETTER) << std::endl;
    
    return {before, after};
}

void Player::on_incorrect_step(const step_t &step) const {
    std::cout << std::endl << "Incorrect input!" << std::endl;
}

void Player::move_pawn(const step_t &step) {
    position_t before = step.before;
    position_t after = step.after;
    
    if (pawns.count(before) != 0) {
        pawns[after] = pawns[before];
        if (after.x == 1) { pawns[after] = KING; }
        pawns.erase(before);
    }
}

void Player::remove_pawn(const position_t &position) {
    if (pawns.count(position) != 0) {
        pawns.erase(position);
    }
}

void Player::on_lose() {
    std::cout << std::endl << name << ", you lose :(" << std::endl;
}

void Player::on_win() {
    std::cout << std::endl << name << ", congratulations!!!" << std::endl;
}

void Player::on_tie() {
    std::cout << "Tie :|" << std::endl;
}

// Print game field with comfortable position for this user
void Player::print_field(const std::shared_ptr<Player> &enemy) const {
    char field[8][8];
    int counter = 1;
    for (char *line: field) {
        counter = (counter + 1) % 2;
        for (int i = counter; i < 8; i += 2) {
            line[i] = ' ';
        }
        for (int j = (counter + 1) % 2; j < 8; j += 2) {
            line[j] = '.';
        }
    }
    
    for (auto const& pawn: pawns) {
        int x = pawn.first.x - 1;
        int y = pawn.first.y - 1;
        char pawn_mark = color;
        if (pawn.second == KING) {
            pawn_mark = toupper(color);
        }
        field[x][y] = pawn_mark;
    }
    
    for (auto const& pawn: enemy->pawns) {
        int x = 7 - (pawn.first.x - 1);
        int y = 7 - (pawn.first.y - 1);
        char pawn_mark = enemy->color;
        if (pawn.second == KING) {
            pawn_mark = toupper(enemy->color);
        }
        field[x][y] = pawn_mark;
    }
    
    int i = 1;
    std::cout << "    A B C D E F G H" << std::endl;
    std::cout << "   -----------------" << std::endl;
    for (char *line: field) {
        std::cout << i << " | ";
        for (int j = 0; j < 8; j++) {std::cout << line[j] << ' ';}
        std::cout << "| " << i << std::endl;
        i++;
    }
    std::cout << "   -----------------" << std::endl;
    std::cout << "    A B C D E F G H" << std::endl;
}

Player::cell_type Player::check_cell(const position_t &pos, const std::shared_ptr<Player> &enemy) const {
    
    if(pawns.count(pos) != 0) {
        return Player::ME;
    } else {
        position_t enemy_pos = {9 - pos.x, 9 - pos.y};
        if (enemy->pawns.count(enemy_pos) != 0) {
            return Player::ENEMY;
        }
    }
    
    return Player::EMPTY;
}

size_t Player::pawns_count() const {
    return pawns.size();
}

pawn_type Player::get_pawn_type(const position_t &pos) {
    if(pawns.count(pos) != 0) {
        return pawns[pos];
    }
    
    return UNDEFINED;
}

int Player::define_index(char letter, input_type t) const {
    if (t == NUMBER) {
        return letter - '0';
    } else if (t == LETTER) {
        if (letter >= 'A' && letter <= 'H') {
            return letter - 'A' + 1;
        } else if (letter >= 'a' && letter <= 'h') {
            return letter - 'a' + 1;
        }
    }
    return -1;
}


/* Field:
 
    A B C D E F G H
   -----------------
1 | _ b _ b _ b _ b | 1
2 | b _ b _ b _ b _ | 2
3 | _ b _ b _ b _ b | 3
4 | . _ . _ . _ . _ | 4
5 | _ . _ . _ . _ . | 5
6 | w _ w _ w _ w _ | 6
7 | _ w _ w _ w _ w | 7
8 | w _ w _ w _ w _ | 8
   -----------------
    A B C D E F G H


    b - black
    w - white
    . - right field
    _ - wrong field
*/
