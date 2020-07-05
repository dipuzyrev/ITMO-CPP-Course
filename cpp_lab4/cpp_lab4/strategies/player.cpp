#include "player.h"

#include <vector>

bool operator<(const position_t &pos1, const position_t &pos2) {
    if (pos1.x != pos2.x) {
        return pos1.x < pos2.x;
    } else {
        return pos1.y < pos2.y;
    }
}

Player::Player(std::string name, char color): name(name), color(color) {}


void Player::init_pawns(int option) {  // option is only for debug purposes
    
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
    
    if (!option) {
        for (int i = 8; i >= 6; i--) {
            pawns[position_t(i, (i % 2) + 1)] = MAN;
            pawns[position_t(i, (i % 2) + 3)] = MAN;
            pawns[position_t(i, (i % 2) + 5)] = MAN;
            pawns[position_t(i, (i % 2) + 7)] = MAN;
        }
        return;
    }

    if (option == 1) {
        pawns[position_t(8,1)] = MAN;
        pawns[position_t(8,3)] = MAN;
        pawns[position_t(8,7)] = MAN;
        pawns[position_t(7,2)] = MAN;
        pawns[position_t(5,4)] = MAN;
        pawns[position_t(3,8)] = MAN;
        pawns[position_t(5,6)] = KING;
    } else if (option == 2) {
        pawns[position_t(7,6)] = MAN;
        pawns[position_t(3,8)] = MAN;
    } else if (option == 3) {
        pawns[position_t(8,3)] = MAN;
        pawns[position_t(8,7)] = MAN;
        pawns[position_t(7,2)] = MAN;
        pawns[position_t(7,6)] = MAN;
        pawns[position_t(7,8)] = MAN;
        pawns[position_t(6,7)] = MAN;
        pawns[position_t(5,2)] = MAN;
        pawns[position_t(1,4)] = KING;
    } else if (option == 4) {
        pawns[position_t(8,3)] = MAN;
        pawns[position_t(8,1)] = MAN;
        pawns[position_t(8,7)] = MAN;
        pawns[position_t(7,2)] = MAN;
        pawns[position_t(6,1)] = MAN;
        pawns[position_t(6,3)] = MAN;
        pawns[position_t(6,5)] = MAN;
        pawns[position_t(5,4)] = MAN;
        pawns[position_t(4,1)] = MAN;
        pawns[position_t(4,3)] = MAN;
    }
    
}

step_t Player::make_step(const std::shared_ptr<Player> &enemy) const {
    
    if(!can_go(enemy)) { // no possible steps anymore
        return step_t {{0,0}, {0,0}};
    }
    
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

step_type Player::move_pawn(const step_t &step) {
    position_t before = step.before;
    position_t after = step.after;
    
    if (pawns.count(before) != 0) {  // pawn exists on map
        pawns[after] = pawns[before];
        pawns.erase(before);
        
        if (after.x == 1) {  // first row of enemy's field - transform to KING
            pawns[after] = KING;
            return BECOME_KING;
        }
        
        return STEP;
    }
    
    return WRONG;
}

void Player::remove_pawn(const position_t &position) {
    if (pawns.count(position) != 0) {
        pawns.erase(position);
    }
}

bool Player::can_go(const std::shared_ptr<Player> &enemy) const {
    
    for (auto it=pawns.begin(); it!=pawns.end(); ++it) {
        position_t pawn_pos = it->first;
        pawn_type pawn_type = it->second;
        
        std::vector<position_t> near_cells = {
            {pawn_pos.x + 1, pawn_pos.y + 1},
            {pawn_pos.x + 1, pawn_pos.y - 1},
            {pawn_pos.x - 1, pawn_pos.y + 1},
            {pawn_pos.x - 1, pawn_pos.y - 1}
        };
    
        for (int i = 0; i < 4; i++) {
            if ((i < 2) && (pawn_type != KING)) { continue; }  // MEN could go only forward
            
            position_t pos = near_cells[i];
            
            if (((pos.x <= 8) && (pos.x >= 1)) && ((pos.y <= 8) && (pos.y >= 1))) {
                if (check_cell(pos, enemy) == EMPTY) {
                    return true;
                }
            }
        }
    }
    
    return false;
}

bool Player::can_eat(const std::shared_ptr<Player> &enemy) const {
    for (auto const& pawn: pawns) {
        if (can_eat(pawn.first, enemy)) {
            return true;
        }
    }
    
    return false;
}


bool Player::can_eat(position_t p_position, const std::shared_ptr<Player> &enemy) const {
    pawn_type p_type = pawns.find(p_position)->second;
    
    if (p_type == MAN) {
        std::vector<position_t> near_cells = {
            {p_position.x + 1, p_position.y + 1},
            {p_position.x + 1, p_position.y - 1},
            {p_position.x - 1, p_position.y + 1},
            {p_position.x - 1, p_position.y - 1}
        };
        
        std::vector<position_t> near_cells_2 = {
            {p_position.x + 2, p_position.y + 2},
            {p_position.x + 2, p_position.y - 2},
            {p_position.x - 2, p_position.y + 2},
            {p_position.x - 2, p_position.y - 2}
        };
    
        for (int i = 0; i < 4; i++) {
            position_t pos2 = near_cells_2[i];
            
            if (((pos2.x <= 8) && (pos2.x >= 1)) && ((pos2.y <= 8) && (pos2.y >= 1))) {
                if ((check_cell(pos2, enemy) == EMPTY) && (check_cell(near_cells[i], enemy) == ENEMY)) {
                    return true;
                }
            }
        }
    } else {
        std::vector<position_t> iterators = {
            {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
        };
        for (int j = 0; j < 4; j++) {
            position_t iterator = iterators[j];
            
            for (int i = 1; i < 8; i++) {
                int near_x1 = p_position.x + (iterator.x * i);
                int near_y1 = p_position.y + (iterator.y * i);
                int near_x2 = p_position.x + (iterator.x * (i + 1));
                int near_y2 = p_position.y + (iterator.y * (i + 1));
                
                if ((near_x2 <= 8) && (near_x2 >= 1) && (near_y2 <= 8) && (near_y2 >= 1)) {
                    if ((check_cell({near_x2, near_y2}, enemy) == EMPTY) &&
                        (check_cell({near_x1, near_y1}, enemy) == ENEMY)) {
                        return true;
                    } else if (check_cell({near_x1, near_y1}, enemy) == EMPTY) {
                        continue;
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            }
        }
    }
    
    return false;
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
