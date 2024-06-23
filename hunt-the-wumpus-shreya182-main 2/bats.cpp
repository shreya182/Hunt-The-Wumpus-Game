#include "bats.hpp"
#include <iostream>

bool bats::encounter(Game& game) {
    std::cout << "You are confused by the bats and move randomly." << std::endl;
    game.override_next_move = true;
    return true;  // Indicate that the bats remain in the game
}
