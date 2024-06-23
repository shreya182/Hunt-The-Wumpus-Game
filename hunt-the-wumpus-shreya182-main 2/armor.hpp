#ifndef ARMOR_HPP
#define ARMOR_HPP

#include "event.hpp"
#include "game.hpp"

class armor : public Event {
public:
    /*
	 * Function: encounter
	 * Description: Performs action when user encounters object
	 * Parameters:
	 * 		game (Game class object): Reference to game class object
	 * Returns (bool): True if the object should stay in game
	 */
    bool encounter(Game& game);
    /*
	 * Function: get_debug_symbol
	 * Description: Returns symbol to print on board
	 * Returns (char): M to represent armor on board
	 */
    char get_debug_symbol() const { return 'M'; }
    /*
	 * Function: percept
	 * Description: returns the percept message for event
	 * Returns (string): "You feel the power"
	 */
    std::string percept() const { return "You feel the power."; }
};

#endif
