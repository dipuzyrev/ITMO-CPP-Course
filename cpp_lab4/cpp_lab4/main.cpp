#include <memory>
#include "iostream"

#include "game/game.h"
#include "strategies/player.h"
#include "strategies/computer1.h"
#include "strategies/computer2.h"

int main() {
//    {
//        auto player1 = std::make_shared<Computer1>("Naive", 'w');
//        auto player2 = std::make_shared<Computer2>("Smart", 'b');
//
//        for (int i = 0; i < 1000; ++i) {
//            std::cout << "game #" << i << std::endl;
//            Game game(player1, player2);
//            game.play();
//        }
//
//        player1->print_stat();
//        player2->print_stat();
//    }
    {
            
        auto player1 = std::make_shared<Player>("Dima", 'w');
        auto player2 = std::make_shared<Player>("Sasha", 'b');
//        auto player2 = std::make_shared<Computer2>("MacBook", 'b');

        Game game(player1, player2);
        game.play();
        
        return 0;
    }
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
