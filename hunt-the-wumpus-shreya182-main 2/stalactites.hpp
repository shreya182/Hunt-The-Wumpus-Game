#ifndef STALACTITES_HPP
#define STALACTITES_HPP

#include <string>
#include "event.hpp"
#include "game.hpp"

class Game;

class stalactites : public Event {
public:
    /*
	 * Function: percept
	 * Description: Returns percept message for event 
	 * Returns (string): "You hear water dripping"
	 */
    std::string percept() const { return "You hear water dripping."; }
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
	 * Returns (char): S to represent stalactites on board
	 */
    char get_debug_symbol() const{ return 'S'; }
};

#endif
