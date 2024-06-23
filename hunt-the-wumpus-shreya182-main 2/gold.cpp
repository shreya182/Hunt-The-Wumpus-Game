#include "gold.hpp"
#include <iostream>


bool gold::encounter(Game& game) {
    std::cout << "You found the gold!" << std::endl;
    game.collect_gold();
    return false;  // Indicate that the gold should be removed from the game
}
