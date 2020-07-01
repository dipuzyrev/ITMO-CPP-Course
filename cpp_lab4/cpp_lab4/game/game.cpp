#include "game.h"

Game::Game(const player_t &first, const player_t &second): steps_count(0), pawns_count(0) {
    players.push_back(first);
    players.push_back(second);
}

bool Game::apply_step(const step_t &step, size_t player_num) {
    
    int vertical_shift = step.before.x - step.after.x;
    int horizontal_shift = step.after.y - step.before.y;
    
//    std::cout << "vertical shift: " << vertical_shift << std::endl;
//    std::cout << "horizontal shift: " << horizontal_shift << std::endl;
    
    player_t me = players[player_num];
    player_t enemy = players[(player_num + 1) % 2];
    
    pawn_type pawn_type = me->get_pawn_type(step.before);
    Player::cell_type before_cell = me->check_cell(step.before, enemy);
    Player::cell_type after_cell = me->check_cell(step.after, enemy);
    
//    std::cout << "before cell: " << before_cell << std::endl;
//    std::cout << "after cell: " << after_cell << std::endl;
    
    if (before_cell == Player::cell_type::ME && after_cell == Player::cell_type::EMPTY) {
        if ((vertical_shift == 1) && (std::abs(horizontal_shift) == 1)) {
            me->move_pawn(step);
            return true;
        } else if ((std::abs(vertical_shift) == 2) && (std::abs(horizontal_shift) == 2)) {
            int between_x = (step.before.x + step.after.x) / 2;
            int between_y = (step.before.y + step.after.y) / 2;
            position_t between = {between_x, between_y};
            Player::cell_type between_cell = me->check_cell(between, enemy);
//            std::cout << "between cell: " << between_x << "," << between_y << std::endl;
            
            if (between_cell == Player::cell_type::ENEMY) {
                me->move_pawn(step);
                enemy->remove_pawn({9 - between_x, 9 - between_y});
                
                return true;
            } else {
                if (pawn_type == KING) {
                    me->move_pawn(step);
                    return true;
                }
                return false;
            }
        } else {
            if (std::abs(vertical_shift) == std::abs(horizontal_shift)) {
                me->move_pawn(step);
                
                int x_iterator = (step.after.x < step.before.x) ? -1 : 1;
                int y_iterator = (step.after.y < step.before.y) ? -1 : 1;
                int counter = 1;
                
                for (int i = step.before.x + x_iterator; i != step.after.x; i += x_iterator) {
                    int j = step.before.y + (y_iterator * counter);
                    
                    position_t next_between = {i, j};
                    Player::cell_type between_cell = me->check_cell(next_between, enemy);
//                    std::cout << "between cell: " << i << "," << j << std::endl;
                    
                    if (between_cell == Player::cell_type::ENEMY) {
                        enemy->remove_pawn({9 - i, 9 - j});
                    }
                    
                    counter++;
                }
                
                return true;
            }
            
            return false;
        }
    }
    
    return false;
}

Game::game_status_t Game::game_status() {
    
    size_t p1_pawns_count = players[0]->pawns_count();
    size_t p2_pawns_count = players[1]->pawns_count();
    
    if ((p1_pawns_count + p2_pawns_count) == pawns_count) {
        steps_count++;
    } else {
        steps_count = 1;
        pawns_count = p1_pawns_count + p2_pawns_count;
    }
    
    if ((p1_pawns_count == 0) || (p2_pawns_count == 0)) {
        return SOMEONE_WIN;
    } else if (steps_count > 50) {
        return TIE;
    }
    
    return IN_PROGRESS;
}

void Game::play() {
    for (size_t i = 0; i < players.size(); ++i) {
        players[i]->init_pawns();
    }
    
    size_t counter = 1;

    while (game_status() == IN_PROGRESS) {
        counter = (counter + 1) % 2;
        
        bool is_correct = false;
        while (!is_correct) {
            player_t enemy = (counter == 0) ? players[1] : players[0];
            step_t step = players[counter]->make_step(enemy);
            is_correct = apply_step(step, counter);
            
            if (!step.before.x && !step.before.y) {
                counter++;
                break;  // no possible steps anymore
            }
            
            if (!is_correct) {
                players[counter]->on_incorrect_step(step);
            }
        }
    }
    
    if (game_status() == TIE) {
        for (size_t i = 0; i < players.size(); ++i) {
            players[i]->on_tie();
        }
        
        return;
    }

    for (size_t i = 0; i < players.size(); ++i) {
        if (i == counter) {
            players[i]->on_win();
        } else {
            players[i]->on_lose();
        }
        
//        players[counter]->print_field(players[(counter + 1) % 2]);
    }
}
