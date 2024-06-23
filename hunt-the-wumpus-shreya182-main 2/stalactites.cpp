#include "stalactites.hpp"
#include <iostream>
#include <cstdlib>


bool stalactites::encounter(Game& game) {
    if (rand() % 2 == 0) {
        std::cout << "Stalactites fell and killed you!" << std::endl;
        game.lose_life();
        game.restart_at_rope();
        game.lose_arrows();
        //game.display_game();
        return true;
    } else {
        std::cout << "You narrowly avoided falling stalactites!" << std::endl;
        return true;  // The stalactites remain in the game
    }
}
