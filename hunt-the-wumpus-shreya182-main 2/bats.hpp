#ifndef BATS_HPP
#define BATS_HPP

#include <string>
#include "event.hpp"
#include "game.hpp"

class bats : public Event {
public:
    /*
	 * Function: percept
	 * Description: Returns percept message for event
	 * Returns (string): "You hear wings flapping"
	 */
    std::string percept() const { return "You hear wings flapping."; }
    /*
	 * Function: encounter
	 * Description: Performs action when user encounters object
	 * Parameters:
	 * 		game (class game object): reference to game object
	 * Returns (bool): True if object should stay in game
	 */
    bool encounter(Game& game);
    /*
	 * Function: get_debug_symbol
	 * Description: returns symbol to print on board
	 * Returns (char): B to represent arrow on board
	 */
    char get_debug_symbol() const { return 'B'; }
};

#endif
