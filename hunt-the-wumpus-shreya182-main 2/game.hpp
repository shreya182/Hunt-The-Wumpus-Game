#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include "room.hpp"

// game interface
class Game {
private:
	std::vector<std::vector<room>> grid;
	int num_arrows = 0; 	
	int width;				
	int height;				
	bool debug;				

	int player_x;
	int player_y;
	int rope_x;
	int rope_y;
	bool has_gold = false;
	bool has_armor = false;
	bool has_flashlight = false;
	bool killed_wumpus = false;
	int lives = 3;
	int armor_dur;

	void place_events();
	void move_player(int dx, int dy);
	bool player_in_bounds(int x, int y);
	void handle_encounter();
public:
	// Suggested functions (there are no required functions here):
	
	/*
	 * Function: Constructor
	 * Description: Constructs game object with a grid matching the given
	 * 		width and height
	 * Parameters:
	 * 		width (int): Width of the grid
	 * 		height (int): Height of the grid
	 * 		debug (bool): Whether or not debug mode should be enabled
	 */
	Game(int width, int height, bool debug);

	/*
	 * Function: display_game
	 * Description: Displays the game grid in the terminal
	 */
	void display_game() const;

	/*
	 * Function: check_win
	 * Description: Determines whether the player has won the game
	 * Returns (bool): True if the player has won, false otherwise
	 */
	bool check_win() const;

	/*
	 * Function: check_lose
	 * Description: Determines whether the player has lost the game
	 * Returns (bool): True if the player has lost, false otherwise
	 */
	bool check_lose() const;

	/*
	 * Function: is_direction
	 * Description: Returns true if the given character is a valid direction
	 * 		character (w/a/s/d) and false otherwise
	 * Parameters:
	 * 		c (char): The character to check
	 * Returns (bool): Boolean indicating whether the character is a valid
	 * 		direction character (w/a/s/d)
	 */
	bool is_direction(char c);

	/*
	 * Function: to_lower
	 * Description: Converts a given character to lowercase. Used to standardize
	 * 		a user's character input.
	 * Parameters:
	 * 		direction (char): Character to convert to lowercase
	 * Returns (char): Character converted to lowercase
	 */
	char to_lower(char direction);

	/*
	 * Function: can_move_in_direction
	 * Description: Determines whether the player can move in the given
	 * 		direction, based on their current location and the size of the
	 * 		grid.
	 * Parameters:
	 * 		direction (char): Direction the player wishes to move in
	 * Returns (bool): True if the player can move in the given direction
	 * 		without moving off the grid. False otherwise.
	 */
	bool can_move_in_direction(char direction);

	/*
	 * Function: is_valid_action
	 * Description: Determines whether the given action is valid.
	 * Parameters:
	 * 		action (char): Action the player wishes to perform.
	 * Returns (bool): True if the requested action is valid. False otherwise.
	 */
	bool is_valid_action(char action);

	/*
	 * Function: print_action_error
	 * Description: Prints a clear error message associated with the user's
	 * 		provided invalid action
	 * Parameters:
	 * 		action (char): Invalid action that the user requested
	 */
	void print_action_error(char action);

	/*
	 * Function: get_player_action
	 * Description: Prompts the player for their action for the turn and
	 * 		returns it as a char (w, a, s, d, or f). If the player enters
	 * 		an invalid action, this function reprompts until a valid one is
	 * 		provided.
	 * Returns (char): The valid action provided by the player.
	 */
	char get_player_action();

	/*
	 * Function: get_arrow_fire_direction
	 * Description: Prompts the player for the direction they want to fire an
	 * 		arrow (w, a, s, or d) and returns it as a char. If the player enters
	 * 		an invalid direction, this function reprompts until a valid one is
	 * 		provided.
	 * Returns (char): The valid direction provided by the player.
	 */
	char get_arrow_fire_direction();

	/*
	 * Function: move_up
	 * Description: Moves the player up one grid space
	 * Pre-condition: Player is capable of moving in this direction (without
	 * 		hitting the edge of the board)
	 * Post-condition: Player is moved accordingly.
	 */
	void move_up();

	/*
	 * Function: move_down
	 * Description: Moves the player down one grid space
	 * Pre-condition: Player is capable of moving in this direction (without
	 * 		hitting the edge of the board)
	 * Post-condition: Player is moved accordingly.
	 */
	void move_down();

	/*
	 * Function: move_left
	 * Description: Moves the player left one grid space
	 * Pre-condition: Player is capable of moving in this direction (without
	 * 		hitting the edge of the board)
	 * Post-condition: Player is moved accordingly.
	 */
	void move_left();

	/*
	 * Function: move_right
	 * Description: Moves the player right one grid space
	 * Pre-condition: Player is capable of moving in this direction (without
	 * 		hitting the edge of the board)
	 * Post-condition: Player is moved accordingly.
	 */
	void move_right();

	/*
	 * Function: move
	 * Description: Moves the player in the direction specified by the given
	 * 		character
	 * Parameters:
	 * 		direction (char): Direction in which to move the player (a for
	 * 			west, s for south, d for east, w for north).
	 * Pre-condition: Player is capable of moving in this direction (without
	 * 		hitting the edge of the board)
	 * Post-condition: Player is moved accordingly.
	 */
	void move(char direction);

	/*
	 * Function: fire_arrow_up
	 * Description: Fires an arrow upward
	 * Post-condition: Arrow is fired upward. Wumpus is killed if hit / moves
	 * 		if missed.
	 */
	void fire_arrow_up();

	/*
	 * Function: fire_arrow_down
	 * Description: Fires an arrow downward
	 * Post-condition: Arrow is fired downward. Wumpus is killed if hit / moves
	 * 		if missed.
	 */
	void fire_arrow_down();

	/*
	 * Function: fire_arrow_left
	 * Description: Fires an arrow leftward
	 * Post-condition: Arrow is fired leftward. Wumpus is killed if hit / moves
	 * 		if missed.
	 */
	void fire_arrow_left();

	/*
	 * Function: fire_arrow_right
	 * Description: Fires an arrow rightward
	 * Post-condition: Arrow is fired rightward. Wumpus is killed if hit / moves
	 * 		if missed.
	 */
	void fire_arrow_right();

	/*
	 * Function: fire_arrow
	 * Description: Fires an arrow in the direction specified by the given
	 * 		character
	 * Parameters:
	 * 		direction (char): Direction in which to fire arrow (a for
	 * 			west, s for south, d for east, w for north).
	 * Post-condition: Arrow is fired. Wumpus is killed if hit and moves if
	 * 		missed.
	 */
	void fire_arrow(char direction);

	/*
	 * Function: play_game
	 * Description: Runs one full iteration of the game
	 */
	void play_game();

	/*
	 * Function: move_wumpus
	 * Description: Moves the wumpus after arrow misses. If the arrow enters the
	 * wumpus's first room and misses, it relocates to another.
	 * Post-condition: Wumpus has new location
	 */
	void move_wumpus();
	/*
	 * Function: increment_arrows
	 * Description: increases number of arrows, called when arrow picked up
	 */
	void increment_arrows() { num_arrows++; }
	/*
	 * Function: collect_gold
	 * Description: Collects the gold when user comes across it
	 * Post-condition: has_gold boolean set to true
	 */
    void collect_gold() { has_gold = true; }
	/*
	 * Function: collect_armor
	 * Description: collects the armor when user comes across it
	 * Post-condition: sets has_armor to true
	 */
	void collect_armor();
	/*
	 * Function: collect_flashlight
	 * Description: collects the flashlight when user comes across it
	 * Post-condition: sets has_flashlight to true
	 */
	void collect_flashlight();
	/*
	 * Function: lose_arrows
	 * Description: decrements arrow if one is used up
	 */
	void lose_arrows() { num_arrows = 0; }
	/*
	 * Function: print_percepts
	 * Description: prints out percepts for events
	 */
	void print_percepts() const;
	/*
	 * Function: redistribute_item
	 * Description: redistribute item to open room when player is killed and restarts
	 */
	void redistribute_item(Event* item);
	/*
	 * Function: redistribute_item
	 * Description: redistribute item to open room when player is killed and restarts
	 * Post-condition: arrows set to zero, one life lost, items scattered
	 */
	void restart_at_rope();
	/*
	 * Function: lose_life
	 * Description: decrements number of lives if killed
	 */
	void lose_life();
	/*
	 * Function: warp_player
	 * Description: transport player through tunnel to connected room
	 * Post-condition: player moved to a new position
	 */
	void warp_player(int id);
	bool override_next_move = false; // boolean for the bat event
	~Game();
};
#endif
