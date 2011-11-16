//player.h
#ifndef _PLAYER
#define _PLAYER

#include "character.h"
#include "item.h"
#include "armor.h"
#include "weapon.h"
#include <ncurses.h>

#define PLAYER_START_HP 20
#define PLAYER_START_ATK 1
#define PLAYER_START_DEF 5

#define MAX_INVENTORY 20

class player:public character{
public:
	// constructor for player objects. It takes no arguments, but calls the base
	// character constructor with the arguments of PLAYER_START_HP, PLAYER_START_ATK,
	// and PLAYER_START_DEF.
	player();

	// VIRTUAL FUNCTIONS INHERITTED FROM CHARACTER
	// This function, inherited from the character class, is not currently being used.
	// However, it would allow the player to move in the same way other characters do.
	// For now, it returns an invalid command.
	char TakeTurn();
	
	// The player attacks the character pointed to by the argument. BeAttacked is called for the argument
	// and given an attack value calculated in this function based on weapons equipped by the player.
	void Attack(character* defender);
	
	// BeAttacked takes one argument, an int representing the attack against it. It subtracts its 
	// defense and bonus from equipped armor from the attack and then 
	// subtracts the result from its health. If its health is then below 0, the player is dead and its   	
	// is_alive bool is set to false.
	void BeAttacked(int attack);
	
	// IsOnItem takes one argument, a pointer to an item in the same tile it is occupying. Players can
	// pick up items, so IsOnItems calls addToInventory for the player and returns true.
	bool IsOnItem(item* on_item);
	
	//adds value to gold
	void addGold(int addedValue);
	//adds an item to inventory
	bool addToInventory(item* newItem);
	//sets weapon to equip and places equipped weapon to inventory
	int equipArmor(armor *newArmor);
	//sets armor to equip and places equipped armor to inventory
	int equipWeapon(weapon *newWeapon);
	
	void PrintInventory(WINDOW*);

	//getters
	int getGold();
	armor *getArmor();
	weapon *getWeapon();
	item *getInventory();
private:
	int gold;
	item *inventory[MAX_INVENTORY];
	int current_nitems;
	armor *equippedArmor;
	weapon *equippedWeapon;
};

#endif
