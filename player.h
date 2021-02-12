#ifndef PLAYER_H
#define PLAYER_H

#include "Slot.h"
#include <string>

using namespace std;

class Asset;
class Slot;
class gameEngine;

#define START_AMOUNT (int)350;

class Player {
	string name;
	int balance;
	bool indicator; //Indicator true incase he's in jail, false incase he isn't in jail.
	int position; //index on the board - start at 1
	Asset** assetList;
	int assetCount;
	gameEngine* game;
public:

	Player(string name, gameEngine* game);
	bool operator!=(const Player& p);
	void goToJail();//update the indicator if the player's in jail.
	string getPlayerName()const;
	int getBalance()const;
	bool setBalance(int amout);
	bool getIndicator();
	int getPosition();
	void addAsset(Asset* a);
	bool payRent(int amount); //returns false - game over;
	void LookToFreeAsset(); //if mortgaged asset found on assetList - call the same func in Board.
	void updateCurrLocation(int idx); //every time player passes start call updateAssetValue().
	bool drawDice();//returns true if player is not in jail and can play nect turn.
	bool lookForAssetToMortgage();
	void changeBalance(int amount);
	int getCard();
	void addYearstoAssets();
	~Player();
};

#endif

