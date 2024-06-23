#include "arrow.hpp"
#include <iostream>


bool arrow::encounter(Game& game) {
    std::cout << "You found an arrow!" << std::endl;
    game.increment_arrows();
    return false;  // Indicate that the arrow should be removed from the game
}
