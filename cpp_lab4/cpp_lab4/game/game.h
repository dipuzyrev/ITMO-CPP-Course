#pragma once

#include <memory>
#include <vector>

#include "../strategies/player.h"
#include "structures.h"

class Game {
public:
    using player_t = std::shared_ptr<Player>;
    Game(const player_t &first, const player_t &second);

    void play();

private:
    enum game_status_t {
        IN_PROGRESS,
        SOMEONE_WIN,
        TIE
    };

    game_status_t game_status(size_t current_player_index);
    step_type apply_step(const step_t &step, size_t player_num, position_t previous_eat);

    std::vector<player_t> players;
    
    size_t steps_count;
    size_t pawns_count;
    
    size_t next_counter(const size_t counter) const;
};

