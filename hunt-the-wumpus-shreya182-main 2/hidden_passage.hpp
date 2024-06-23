#ifndef HIDDEN_PASSAGE_HPP
#define HIDDEN_PASSAGE_HPP

#include "event.hpp"

class hiddenpassage : public Event {
public:
    hiddenpassage(int id) : id(id) {}
    /*
	 * Function: percept
	 * Description: Returns percept message for event 
	 * Returns (string): "You feel a breeze"
	 */
    std::string percept() const override { return "You feel a breeze"; }
    /*
	 * Function: encounter
	 * Description: Performs action when user encounters object
	 * Parameters:
	 * 		game (class game object): reference to game object
	 * Returns (bool): True if object should stay in game
	 */
    bool encounter(Game& game) override;
    /*
	 * Function: get_debug_symbol
	 * Description: returns symbol to print on board 
	 * Returns (char): P to represent hidden passage on board
	 */
    char get_debug_symbol() const override { return 'P'; }
    /*
	 * Function: get_jd
	 * Description: returns which number door it is
	 * Returns (char): number door
	 */
    int get_id() const { return id; }

private:
    int id;
};

#endif
