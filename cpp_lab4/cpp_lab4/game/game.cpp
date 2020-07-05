#include "game.h"

Game::Game(const player_t &first, const player_t &second): steps_count(0), pawns_count(0) {
    players.push_back(first);
    players.push_back(second);
}

step_type Game::apply_step(const step_t &step, size_t player_num, position_t previous_eat) {
    
    if (previous_eat.x && previous_eat.x) {
        if ((step.before.x != previous_eat.x) && (step.before.y != previous_eat.y)) {
            return WRONG;  // ate and then moved other pawn
        }
    }
    
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
        if ((vertical_shift == 1) && (std::abs(horizontal_shift) == 1) && !me->can_eat(enemy)) {
            return me->move_pawn(step);
        } else if ((std::abs(vertical_shift) == 2) && (std::abs(horizontal_shift) == 2)) {
            int between_x = (step.before.x + step.after.x) / 2;
            int between_y = (step.before.y + step.after.y) / 2;
            position_t between = {between_x, between_y};
            Player::cell_type between_cell = me->check_cell(between, enemy);
//            std::cout << "between cell: " << between_x << "," << between_y << std::endl;
            
            if (between_cell == Player::cell_type::ENEMY) {
                enemy->remove_pawn({9 - between_x, 9 - between_y});
                step_type step_result = me->move_pawn(step);
                if (step_result == BECOME_KING) {
                    return BECOME_KING;
                } else {
                    return EAT;
                }
            } else if (between_cell == Player::cell_type::EMPTY && pawn_type == KING) {
                me->move_pawn(step);
                return STEP;
            } else {
                return WRONG;
            }
        } else if (pawn_type == KING) {
            std::vector<position_t> enemies;
            
            if (std::abs(vertical_shift) == std::abs(horizontal_shift)) {
                
                int x_iterator = (step.after.x < step.before.x) ? -1 : 1;
                int y_iterator = (step.after.y < step.before.y) ? -1 : 1;
                int counter = 1;
                
                for (int i = step.before.x + x_iterator; i != step.after.x; i += x_iterator) {
                    int j = step.before.y + (y_iterator * counter);
                    
                    position_t next_between = {i, j};
                    Player::cell_type between_cell = me->check_cell(next_between, enemy);
                    
                    if (between_cell == Player::cell_type::ENEMY) {
                        enemies.push_back({9 - i, 9 - j});
                    } else if (between_cell == Player::cell_type::ME) {
                            return WRONG;
                    } else {
                        if (enemies.size()) {
                            return WRONG;
                        }
                    }
                    
                    counter++;
                }
                
                me->move_pawn(step);
                
                for(position_t &pawn: enemies) {
                    enemy->remove_pawn(pawn);
                }
                
                return WRONG;
            }
            
            return WRONG;
        }
    }
    
    return WRONG;
}

Game::game_status_t Game::game_status(size_t current_player_index) {
    
//    std::cout << current_player_index << std::endl;
    
    player_t current = players[current_player_index];
    player_t other = players[next_counter(current_player_index)];
    
    if(!current->can_go(other)) {
        return SOMEONE_WIN;
    }
    
    if ((current->pawns_count() + other->pawns_count()) == pawns_count) {
        steps_count++;
    } else {
        steps_count = 1;
        pawns_count = current->pawns_count() + other->pawns_count();
    }
    
    if ((current->pawns_count() == 0) || (other->pawns_count() == 0)) {
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

    while (game_status(next_counter(counter)) == IN_PROGRESS) {
        counter = next_counter(counter);
        
        step_type step_result = WRONG;
        while (step_result == WRONG) {
            player_t enemy = players[next_counter(counter)];
            
            step_t step;
            position_t previous_eat = {0,0};
            
            do {
                step = players[counter]->make_step(enemy);
                step_result = apply_step(step, counter, previous_eat);
                
                if (!step.before.x && !step.before.y) {  // no possible steps anymore
                    counter = next_counter(counter);
                    break;
                }
                
                if (step_result == WRONG) {
                    players[counter]->on_incorrect_step(step);
                } else if (step_result == EAT) {
                    previous_eat = step.after;
                }
                
            } while((step_result == EAT or step_result == BECOME_KING) &&
                    players[counter]->can_eat(step.after, enemy));
        }
    }
    
    if (game_status(counter) == TIE) {
        for (size_t i = 0; i < players.size(); ++i) {
            players[i]->on_tie();
        }
        
        return;
    } else {
        players[counter]->on_win();
        players[next_counter(counter)]->on_lose();
    }

//  players[counter]->print_field(players[(counter + 1) % 2]);
}

size_t Game::next_counter(const size_t counter) const {
    size_t next = (counter + 1) % 2;
    return next;
}
