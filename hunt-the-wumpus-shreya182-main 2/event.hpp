#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>

class Game;

class Event {
public:
    //virtual percept function, overriden later
    virtual std::string percept() const = 0;
    //virtual encounter function, overriden later
    virtual bool encounter(Game& game) = 0;
    //virtual getsymbol function, overriden later
	virtual char get_debug_symbol() const = 0;
    //Desctructor
	virtual ~Event() = default;
};

#endif
