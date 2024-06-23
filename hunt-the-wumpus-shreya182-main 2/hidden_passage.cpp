#include "hidden_passage.hpp"
#include "game.hpp"
#include <iostream>

bool hiddenpassage::encounter(Game& game) {
    std::cout << "You were warped to a different room!" << std::endl;
    game.warp_player(id);
    //game.display_game();
    return true;  // The hidden passage remains in the game
}
