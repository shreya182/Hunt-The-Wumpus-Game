#include "wumpus.hpp"
#include <iostream>


bool wumpus::encounter(Game& game) {
    std::cout << "The Wumpus has eaten you!" << std::endl;
    game.lose_life();
    game.restart_at_rope();
    game.lose_arrows();
    return true;  // The Wumpus remains in the game
}