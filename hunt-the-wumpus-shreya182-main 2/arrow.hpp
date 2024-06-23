#ifndef ARROW_HPP
#define ARROW_HPP

#include <string>
#include "event.hpp"
#include "game.hpp"

class arrow : public Event {
public:
    /*
	 * Function: percept
	 * Description: Returns percept message for event
	 * Returns (string): "You see an arrow on the ground in an adjacent room"
	 */
    std::string percept() const { return "You see an arrow on the ground in an adjacent room."; }
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
	 * Returns (char): A to represent arrow on board
	 */
    char get_debug_symbol() const { return 'A'; }
};

#endif
