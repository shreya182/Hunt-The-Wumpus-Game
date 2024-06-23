#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
class Event;
class Game;

class room {
private:
    Event* event = nullptr;
public:
    bool has_event() const;
    void set_event(Event* event); //setter
    Event* get_event(); // getter
    /*
	 * Function: get_event_debug_symbol
	 * Description: returns symbol to print on board 
	 * Returns (char): symbol to print on board
	 */
    char get_event_debug_symbol() const;
    /*
	 * Function: trigger_event
	 * Description: returns true if encountered event
	 * Returns (bool): true if encountered event
	 */
    bool trigger_event(Game& game);
    /*
	 * Function: remove_event
	 * Description: remove the event from memory
	 */
    void remove_event();
    /*
	 * Function: get_event_percept
	 * Description: returns the percept message for the event
	 * Returns (string): percept message for the event
	 */
    std::string get_event_percept() const;
};

#endif
