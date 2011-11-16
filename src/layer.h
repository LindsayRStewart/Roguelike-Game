#ifndef LAYER_H
#define LAYER_H

#include "character.h"
#include <ncurses.h>

#define WIDTH 23 // width of map
#define HEIGHT 60 // height of map

// VARIABLES FOR MAP GENERATIONS
#define ROOM_DENSITY 15
#define MAX_ROOM_RADIUS 35
#define ROOM_VAR 3
#define DOOR_DENSITY 5
#define MAX_REPEATS 10

using namespace std;

struct node;
class tree;
class monster;
class item;
class player;
class base_room;

// PROVIDES A TYPE FOR A PLAYER/CHARACTERS ACTION CHOICE
enum action {MOVE_RIGHT, MOVE_LEFT, MOVE_DOWN, MOVE_UP, INVENTORY, MENU, INVALID, QUIT};
// IDENTIFIES THE TERRAIN OF A PARTICULAR TILE
enum TerrainType {FLOOR, WALL, DOOR, UP_LADDER, DOWN_LADDER};

// Tiles make up individual spaces on the layer. They can contain one character and one item.
// lterrain denotes their type (any of the types enummerated in TerrainType)
// room records the ID of the room that the tile belongs to. (This will be used later to light
// 		up individual rooms rather than the whole map)
struct tile {
	character* lchar;
	item* litem;
	TerrainType lterrain;
	base_room* room;
	bool lit;
	bool explored;
};

class layer{
	public:
		// Constructor for layer. Takes three arguments, the first the previous layer
		// on the map stack, the second the next layer on the map stack, and the third
		// an integer representing the layer's depth.
		// When a map is initially created, call this constructor with the arguments
		// NULL, NULL, and 0. After the first call, descend takes care of layer creation.
		layer(layer*, layer*, int);
		// destructor for layer. Recursively deletes the map stack of layers.
		~layer();
		// Helper function for destructor
		friend void DeleteMap(layer*);
		
		// RUN THIS FUNCTION AT THE END OF EVERY ROUND, SETTING MAP POINTER EQUAL TO IT
		// ie, map = map->AscendOrDescend();
		// If the player is standing on an UP_LADDER or a DOWN_LADDER when the round ends, this function
		// moves the map up or down one layer.
		// If the previous layer is NULL and the player is trying to Ascend, nothing will happen.
		// If the next layer is NULL and the player is trying to Descend, a new layer will be created.
		// The argument is a pointer to the player, which is stored in the new layer's
		// character list. 
		// The function deletes player from the current level, but does not delete player_x or player_y
		// so that when the player returns they return to the correct location. The player is added
		// to the returned layer.
		layer* AscendOrDescend(character* the_player);
		
		// Moves the character at the location given by the first two arguments according to the 
		// command given as the third argument (can be MOVE_RIGHT, MOVE_LEFT, etc. See the enumerated
		// type "action" )
		// If the tile the character is trying to move into is occupied by another character, Attack
		// is called by the moving character and given the stationary character as its argument.
		// If the tile the character is trying to move into is occupied by an item, IsOnItem is called
		// by the moving character. Then the character is moved into that tile.
		// When a character is moved, it is deleted from its current square using DeleteCharacter and
		// added to the new square using AddCharacter.
		int MoveCharacter(int pos_x, int pos_y, action command);
		
		// Deletes the item at the location given by the two arguments by setting the litem pointer
		// for that tile equal to NULL.
		void DeleteItem(int pos_x, int pos_y);
		
		// Deletes the character at the location given by the two arguments by setting the lchar pointer
		// for that tile equal to NULL.
		void DeleteCharacter(int pos_x, int pos_y);
		
		// The first argument is a pointer to an item. The litem pointer at the location given by the
		// second and third arguments is set equal to the first argument.
		void AddItem(item* add_item, int pos_x, int pos_y); 
		
		// The first argument is a pointer to a character. The lchar pointer at the location given by the
		// second and third argument is set equal to the first argument. setX and setY are then called
		// for the first argument to update its record of its location.
		void AddCharacter(character* add_char, int pos_x, int pos_y);
		
		// The argument is an integer representing a location in the charlist array of character pointers.
		// The function returns the pointer at charlist[number].
		character* Get_Character(int number);
		
		// Returns nchars, the number of character pointers in the charlist array
		int Get_Nchars();
		
		// Returns the x coordinate of the player's location.
		// Initially set (in Generate) to the location of the UP_LADDER
		int Get_player_x();
		
		// Returns the y coordinate of the player's location.
		// Initially set (in Generate) to the location of the DOWN_LADDER
		int Get_player_y();
		
		// Prints the map to the ncurses window, including player, monsters, and items.
		void Print(WINDOW*);
		
	private:
		// map data
		tile LayerMap[WIDTH][HEIGHT];
		layer *prevlayer;
		layer *nxtlayer; 
		
		// room information
		int nrooms; 
		int nhalls;
		base_room **roomlist;
		friend class base_room;
		
		// player information
		int player_x;
		int player_y;
		bool can_scend;
		
		// depth of layer
		int depth;
		
		// character information
		character **charlist;
		int nchars;
		
		// item information
		item **itemlist;
		int nitems;
		
		// GENERATE AND GENERATION HELPERS
		// Generate is called once at layer creation and generates the map. It calls Seed(),
		// Build_Doors(), and PlaceLadders() and relies on rand() being seeded in main.
		void Generate();
		bool Build_Doors();
		void Seed();
		void PlaceLadders();
};


#endif
