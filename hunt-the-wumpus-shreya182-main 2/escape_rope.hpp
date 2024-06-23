#ifndef ESCAPE_ROPE_HPP
#define ESCAPE_ROPE_HPP

#include "event.hpp"

class escaperope : public Event {
public:
    /*
	 * Function: percept
	 * Description: Returns percept message for event (just here to avoid errors)
	 * Returns (string): empty string
	 */
    std::string percept() const { return ""; }
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
	 * Description: returns blank symbol to print on board (just here to avoid errors)
	 * Returns (char): empty char
	 */
    char get_debug_symbol() const { return ' '; }
};

#endif
