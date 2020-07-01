#include "computer1.h"

#include <iostream>
#include <vector>
#include <algorithm>

Computer1::Computer1(std::string name, char color): Computer(name, color) {};

step_t Computer1::make_step(const std::shared_ptr<Player> &enemy) const {
    
    // Naive strategy
    // 1. find any eating option
    // 2. first possible step
    
    step_t eating_option = find_eating_option(enemy);
    if (eating_option.before.x) {
        return eating_option;
    }
    
    step_t step_option = find_step_option(enemy);
    return step_option;
};

step_t Computer1::find_eating_option(const std::shared_ptr<Player> &enemy) const {
    for (auto const& pawn: pawns) {
        position_t pawn_pos = pawn.first;
        pawn_type pawn_type = pawn.second;
        
        if (pawn_type == MAN) {
            // MEN
            
            std::vector<position_t> near_cells = {
                {pawn_pos.x + 1, pawn_pos.y + 1},
                {pawn_pos.x + 1, pawn_pos.y - 1},
                {pawn_pos.x - 1, pawn_pos.y + 1},
                {pawn_pos.x - 1, pawn_pos.y - 1}
            };
            
            std::vector<position_t> near_cells_2 = {
                {pawn_pos.x + 2, pawn_pos.y + 2},
                {pawn_pos.x + 2, pawn_pos.y - 2},
                {pawn_pos.x - 2, pawn_pos.y + 2},
                {pawn_pos.x - 2, pawn_pos.y - 2}
            };
        
            for (int i = 0; i < 4; i++) {
                position_t pos2 = near_cells_2[i];
                
                if (((pos2.x <= 8) && (pos2.x >= 1)) && ((pos2.y <= 8) && (pos2.y >= 1))) {
                    if ((check_cell(pos2, enemy) == EMPTY) && (check_cell(near_cells[i], enemy) == ENEMY)) {
                        return {pawn_pos, pos2};
                    }
                }
            }
        } else {
            // KINGS
            
            std::vector<position_t> iterators = {
                {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
            };
            for (int j = 0; j < 4; j++) {
                position_t iterator = iterators[j];
                
                for (int i = 1; i < 8; i++) {
                    int near_x1 = pawn_pos.x + (iterator.x * i);
                    int near_y1 = pawn_pos.y + (iterator.y * i);
                    int near_x2 = pawn_pos.x + (iterator.x * (i + 1));
                    int near_y2 = pawn_pos.y + (iterator.x * (i + 1));
                    
                    if (((near_x2 <= 8) && (near_x2 >= 1)) && ((near_y2 <= 8) && (near_y2 >= 1))) {
                        if ((check_cell({near_x2, near_y2}, enemy) == EMPTY) &&
                            (check_cell({near_x1, near_y1}, enemy) == ENEMY)) {
                            return {pawn_pos, {near_x2, near_y2}};
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
    }
    
    return {{0,0}, {0,0}};
}

step_t Computer1::find_step_option(const std::shared_ptr<Player> &enemy) const {
    std::vector<cell_t> pawns_arr = {};
    
    for (auto const& pawn: pawns) {
        pawns_arr.push_back({pawn.first, pawn.second});
    }
    
    std::random_shuffle(pawns_arr.begin(), pawns_arr.end());
    
    for(std::vector<cell_t>::iterator it=pawns_arr.begin(); it!=pawns_arr.end(); ++it) {
        position_t pawn_pos = it->position;
        pawn_type pawn_type = it->p_type;
        
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
                    return {pawn_pos, pos};
                }
            }
        }
    }
    
    return {{0,0}, {0,0}};
}
