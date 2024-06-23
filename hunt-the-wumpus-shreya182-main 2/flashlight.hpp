#ifndef FLASHLIGHT_HPP
#define FLASHLIGHT_HPP

#include "event.hpp"
#include <string>

class flashlight : public Event {
public:
    /*
	 * Function: get_debug_symbol
	 * Description: returns symbol to print on board 
	 * Returns (char): F to represent flashlight on board
	 */
    char get_debug_symbol() const override { return 'F'; }
    /*
	 * Function: percept
	 * Description: Returns percept message for event
	 * Returns (string): "You see a faint glow"
	 */
    std::string percept() const override { return "You see a faint glow."; }
    /*
	 * Function: encounter
	 * Description: Performs action when user encounters object
	 * Parameters:
	 * 		game (class game object): reference to game object
	 * Returns (bool): True if object should stay in game
	 */
    bool encounter(Game& game) override;
};

#endif
