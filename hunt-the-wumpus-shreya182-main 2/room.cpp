#include "room.hpp"
#include "event.hpp"

bool room::has_event() const {
    return event != nullptr;
}

void room::set_event(Event* event) {
    this->event = event;
}
Event* room::get_event(){
    return event;
}
char room::get_event_debug_symbol() const {
    if (event) {
        return event->get_debug_symbol(); 
    }
    return ' ';
}
bool room::trigger_event(Game& game) {
    if (event) {
        return event->encounter(game);
    }
    return false;
}

void room::remove_event() {
    delete event;
    event = nullptr;
}

std::string room::get_event_percept() const {
    if (event){
        return event->percept();
    }
    return "";
}
