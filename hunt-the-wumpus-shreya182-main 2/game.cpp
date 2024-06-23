#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.hpp"
#include "gold.hpp"
#include "bats.hpp"
#include "stalactites.hpp"
#include "wumpus.hpp"
#include "escape_rope.hpp"
#include "arrow.hpp"
#include "armor.hpp"
#include "hidden_passage.hpp"
#include "flashlight.hpp"

// game implementation

Game::Game(int width, int height, bool debug) :
		width(width),
		height(height),
		debug(debug) {
	//Create the game board: 2D vector of room objects
	grid.resize(height, std::vector<room>(width));
	
	place_events();
}

void Game::place_events() {
    rope_x = rand() % width;
    rope_y = rand() % height;
    grid[rope_y][rope_x].set_event(new escaperope());
    player_x = rope_x;
    player_y = rope_y;

    std::vector<Event*> events = { //create board events
        new bats(), new bats(),
        new stalactites(), new stalactites(),
        new wumpus(), new gold(),
        new arrow(), new arrow(),
        new armor(), new hiddenpassage(1),
        new hiddenpassage(2), new flashlight()
    };
    for (size_t i = 0; i < events.size(); i++) { // place events randomly
        Event* event = events[i];
        int x, y;
        do {
            x = rand() % width;
            y = rand() % height;
        } while (grid[y][x].has_event() || (y == rope_y && x == rope_x));
            grid[y][x].set_event(event);
    }
}
void Game::display_game() const{ 
	std::cout << "\n\nArrows remaining: " << num_arrows << std::endl;
    std::cout << "Lives remaining: " << lives << std::endl;

    std::string row_border = "--";
    for (int i = 0; i < width; i++) {
        row_border += "-----";
    }

    std::cout << row_border << std::endl;
    for (int i = 0; i < height; i++) {
        std::cout << "||";
        for (int j = 0; j < width; j++) {
            if (i == player_y && j == player_x) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }

              if (has_flashlight && (i == player_y || j == player_x)) {
                if (!grid[i][j].has_event()) {
                    std::cout << " ";
                } else {
                    std::cout << grid[i][j].get_event_debug_symbol();
                }
            } else if (!this->debug || !grid[i][j].has_event()) {
                std::cout << " ";
            } else {
                std::cout << grid[i][j].get_event_debug_symbol();
            }
            std::cout << " ||";
        }
        std::cout << std::endl;
        std::cout << row_border << std::endl;
    }
}
void Game::collect_armor(){
    has_armor = true;
    armor_dur = 2;
}
void Game::collect_flashlight(){
    has_flashlight = true;
}
void Game::lose_life(){
    if (has_armor && armor_dur > 0) { // update armor durabilty
        armor_dur--;
        std::cout << "Your armor protected you! Durability remaining: " << armor_dur << std::endl;
        if (armor_dur == 0) {
            has_armor = false;
            std::cout << "Your armor is now destroyed." << std::endl;
        }
    } else { //decrement lives
        lives--;
        if (lives <= 0) {
            std::cout << "Game over! You have lost all your lives." << std::endl;
            exit(0);
        } else {
            std::cout << "You have " << lives << " lives remaining." << std::endl;
        }
    }
}
void Game::restart_at_rope() {
    if (has_gold) { // scatter gold
            redistribute_item(new gold());
            has_gold = false;
        }
    if (has_flashlight){ // scatter flashlight
        redistribute_item(new flashlight());
        has_flashlight = false;
    }
    for (int i = 0; i < num_arrows; i++) { // scatter arrows
            redistribute_item(new arrow());
    }

    for (int y = 0; y < height; y++) { // restart player at escape rope
        for (int x = 0; x < width; x++) {
            if (grid[y][x].has_event()) {
                    player_x = rope_x;
                    player_y = rope_y;
                    return;
            }
        }
    }
}

bool Game::check_win() const{
    if (player_x == rope_x && player_y == rope_y && has_gold){ // check for winning condition 1
        return true;
    } else if (killed_wumpus){ // check for winning condition 2
        return true;
    }
    return false;
}

bool Game::check_lose() const{ 
	return lives <= 0;
}

bool Game::is_direction(char c) {
	return c == 'w' ||
		c == 'a' ||
		c == 's' ||
		c == 'd';
}

char Game::to_lower(char direction) {
	if (direction >= 'A' && direction <= 'Z') {
		return direction + ('a' - 'A');
	}
	return direction;
}

bool Game::can_move_in_direction(char direction) {
	if (direction == 'w'){
        return player_y > 0;
    } else if (direction == 'a'){
        return player_x > 0;
    } else if (direction == 's'){
        return player_y < height - 1;
    } else if (direction == 'd'){
        return player_x < width - 1;
    } else {
        return false;
    }
}

bool Game::is_valid_action(char action) {
	if (this->is_direction(action)) {
		char direction = action;
		return this->can_move_in_direction(direction);
	} else if (action == 'f') {
		return this->num_arrows > 0;
	}
	return false;
}

void Game::print_action_error(char action) {
	if (this->is_direction(action)) {
		std::cout << "You can't move in that direction!" << std::endl << std::endl;
	} else if (action == 'f') {
		std::cout << "You're out of arrows!" << std::endl << std::endl;
	} else {
		std::cout << std::endl << "That's an invalid input!" << std::endl
			<< std::endl;
	}
}

char Game::get_player_action() {
	char action;
	bool first = true;
	do {
		if (!first) {
			char previous_action = action;
			this->print_action_error(previous_action);
		}
		first = false;
        //get input
		std::cout << std::endl << std::endl << "What would you like to do?" <<
			std::endl << std::endl;
		std::cout << "w: move up" << std::endl;
		std::cout << "a: move left" << std::endl;
		std::cout << "s: move down" << std::endl;
		std::cout << "d: move right" << std::endl;
		std::cout << "f: fire an arrow" << std::endl;

		std::cin >> action;
		action = this->to_lower(action);
	} while (!this->is_valid_action(action));

	return action;
}

char Game::get_arrow_fire_direction() {
	char direction;
	bool first = true;
	do {
		if (!first) {
			std::cout << std::endl << "That's an invalid input!" <<
				std::endl << std::endl;
		}
		first = false;
        display_game();
		print_percepts();
        
        //get input
		std::cout << std::endl << std::endl <<
			"What direction would you like to fire the arrow?" << std::endl <<
			std::endl;
		std::cout << "w: up" << std::endl;
		std::cout << "a: left" << std::endl;
		std::cout << "s: down" << std::endl;
		std::cout << "d: right" << std::endl;

		std::cin >> direction;
		direction = this->to_lower(direction);
	} while (!this->is_direction(direction));

	return direction;
}

void Game::move_up() {
	if (can_move_in_direction('w')){
		player_y--;
	}
}

void Game::move_down() {
	if (can_move_in_direction('s')){
		player_y++;
	}
}

void Game::move_left() {
	if (can_move_in_direction('a')){
		player_x--;
	}
}

void Game::move_right() {
	if (can_move_in_direction('d')){
		player_x++;
	}
}

void Game::move(char direction) {
    if (override_next_move){ // if user encountered bat
        int random_dir;
        char random_direction;
        do {
            random_dir = rand() % 4;
            random_direction = "wasd"[random_dir];
        } while (!can_move_in_direction(random_direction) || random_direction == direction);
        direction = random_direction;
        override_next_move = false;
    }
    // move in direction
	if (direction == 'w') {
		this->move_up();
	} else if (direction == 'a') {
		this->move_left();
	} else if (direction == 's') {
		this->move_down();
	} else if (direction == 'd'){
		this->move_right();
	} 
}
void Game::move_wumpus(){
	for (int i = 0; i < height; i++) { // find wumpus position
        for (int j = 0; j < width; j++) {
            if (grid[i][j].get_event_debug_symbol() == 'W') {
                grid[i][j].remove_event();
                break;
            }
        }
    }
    // move the wumpus to a random empty room
    int x, y;
    do {
        x = rand() % width;
        y = rand() % height;
    } while (grid[y][x].has_event());
    grid[y][x].set_event(new wumpus());
}
void Game::fire_arrow_up() {
    for (int i = 1; i <= 3 && player_y - i >= 0; i++) {
        if (grid[player_y - i][player_x].has_event()) {
            if (grid[player_y - i][player_x].get_event_debug_symbol() == 'W') {
                std::cout << "You killed the Wumpus!" << std::endl;
                killed_wumpus = true;
                grid[player_y - i][player_x].remove_event();
                return;
            }
        }
    }
    std::cout << "You missed!" << std::endl;
    move_wumpus();
}
void Game::fire_arrow_down() {
    for (int i = 1; i <= 3 && player_y + i < height; i++) {
        if (grid[player_y + i][player_x].has_event()) {
            if (grid[player_y + i][player_x].get_event_debug_symbol() == 'W') {
                std::cout << "You killed the Wumpus!" << std::endl;
                killed_wumpus = true;
                grid[player_y + i][player_x].remove_event();
                return;
            }
        }
    }
    std::cout << "You missed!" << std::endl;
    move_wumpus();
}

void Game::fire_arrow_left() {
    for (int i = 1; i <= 3 && player_x - i >= 0; i++) {
        if (grid[player_y][player_x - i].has_event()) {
            if (grid[player_y][player_x - i].get_event_debug_symbol() == 'W') {
                std::cout << "You killed the Wumpus!" << std::endl;
                killed_wumpus = true;
                grid[player_y][player_x - i].remove_event();
                return;
            }
        }
    }
    std::cout << "You missed!" << std::endl;
    move_wumpus();
}

void Game::fire_arrow_right() {
    for (int i = 1; i <= 3 && player_x + i < width; i++) { // shoot arrow through up to 3 rooms
        if (grid[player_y][player_x + i].has_event()) {
            if (grid[player_y][player_x + i].get_event_debug_symbol() == 'W') {
                std::cout << "You killed the Wumpus!" << std::endl;
                killed_wumpus = true;
                grid[player_y][player_x + i].remove_event();
                return;
            }
        }
    }
    std::cout << "You missed!" << std::endl;
    move_wumpus();
}

void Game::fire_arrow(char direction) {
	if (direction == 'w') {
		this->fire_arrow_up();
	} else if (direction == 'a') {
		this->fire_arrow_left();
	} else if (direction == 's') {
		this->fire_arrow_right();
	} else {
		this->fire_arrow_down();
	}

	this->num_arrows--;
}
void Game::handle_encounter() { 
    room& room = grid[player_y][player_x];
    if (room.has_event()) { // if event in room, trigger event
        bool keep_event = room.trigger_event(*this); 
        if (!keep_event) {
            room.remove_event();
        }
    }
}
void Game::redistribute_item(Event* item) { // scatter item
    int x, y;
    do {
        x = rand() % width;
        y = rand() % height;
    } while (grid[y][x].has_event() || (player_y == y && player_x == x));
    
    grid[y][x].set_event(item);
}
void Game::print_percepts() const {
    //check adjacent rooms
    int directions[4][2] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} }; 
    for (const auto& dir : directions) {
        int nx = player_x + dir[0];
        int ny = player_y + dir[1];
        if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
            std::string percept = grid[ny][nx].get_event_percept();
            if (!percept.empty()) {
                std::cout << percept << std::endl;
            }
        }
    }
}
void Game::warp_player(int id){ 
    // send player through hidden passage
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Event* event = grid[y][x].get_event();
            hiddenpassage* passage = dynamic_cast<hiddenpassage*>(event);
            if (passage && passage->get_id() != id) {
                player_x = x;
                player_y = y;
                return;
            }
        }
    }
}
void Game::play_game(){
    bool first = true;
	while (!check_win() && !check_lose()) {
        handle_encounter();
        display_game();
        print_percepts();
        char action = get_player_action();
        if (is_direction(action)) {
            move(action);
        } else {
            char direction = get_arrow_fire_direction();
            fire_arrow(direction);
        }
    }
    if (check_win()) {
        std::cout << "Congratulations! You have won the game!" << std::endl;
    } else {
        std::cout << "Game over! You have lost all your lives." << std::endl;
    }
}
Game::~Game() { //destructor
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[y][x].has_event()) {
                delete grid[y][x].get_event(); 
                grid[y][x].set_event(nullptr); 
            }
        }
    }
}
