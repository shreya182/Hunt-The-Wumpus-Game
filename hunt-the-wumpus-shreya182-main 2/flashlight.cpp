#include "flashlight.hpp"
#include "game.hpp"
#include <iostream>

bool flashlight::encounter(Game& game) {
    std::cout << "You found a flashlight! Now you can see debug symbols in your row and column." << std::endl;
    game.collect_flashlight();
    return false;  // Flashlight is removed from the room
}
