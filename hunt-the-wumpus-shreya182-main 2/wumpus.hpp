#ifndef WUMPUS_HPP
#define WUMPUS_HPP

#include <string>
#include "event.hpp"
#include "game.hpp"

class wumpus : public Event {
public:
    /*
	 * Function: percept
	 * Description: Returns percept message for event 
	 * Returns (string): "You smell a terrible stench"
	 */
    std::string percept() const { return "You smell a terrible stench."; }
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
	 * Returns (char): W to represent wumpus on board
	 */
    char get_debug_symbol() const { return 'W'; }
    
};

#endif
