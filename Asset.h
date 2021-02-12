#ifndef ASSET_H
#define ASSET_H
#include "Slot.h"
#include <string>
#include "Instruction.h"
using namespace std;

class Slot;
class Player;

#define INTEREST (float)0.05 // iterest rate is: 5%

class Asset : public Slot
{
	string city;
	int price; 
	int rent; 
	Player* owner; // NULL - free, if ownd by a player will contain pointer to the player.
	int yearsMortgaged;

public:
	Asset(string name, int number, string city, int price, int rent);
	string getCity() const { return this->city; }
	int getYearsMortgaged() { return this->yearsMortgaged; }
	int getPrice() const { return this->price; }
	bool operator==(const Asset& asset);
	int checkMortgagedPrice();// return the price to free the mortgaged asset.
	bool buyAsset(Player* p); //buy free asset or pay rent. 
	bool play(Player* p); //returns true if game is still on,call buyAsset(player * p). 
	void printSlot();
	void addYear() { this->yearsMortgaged += 1; }
	int mortgagedAsset();
	void freeAssetMortagaged();
	void freeAsset();
};
#endif

