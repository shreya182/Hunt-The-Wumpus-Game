#include "armor.hpp"
#include "game.hpp"
#include <iostream>

bool armor::encounter(Game& game) {
    std::cout << "You have found armor! It will protect you from 2 fatal encounters." << std::endl;
    game.collect_armor();
    return false;  // Remove armor after it is found
}
