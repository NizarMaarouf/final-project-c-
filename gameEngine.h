#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Slot.h"
#include <string>
#include <queue>
#include <fstream>
#include <iostream>

using namespace std;

class Slot;
class Player;

#define N (int)20;
#define MAX_SIZE (int)20;
#define MIN_SIZE (int)5;

class gameEngine
{
	Slot** Board;
	queue<Player*> playersQueue;
	queue<int> cardsDeck;
	int boardSize;

public:
	gameEngine(string fileLocation, int amountOfPlayers);
	int getCard();
	int countLines(string fileLocation);
	void createBoard(string fileLocation);
	int getBoardSize();
	Slot* getLocationSlot(int position);
	int getAmountOfPlayers();
	Player* getNextPlayer();
	void returnPlayertoQueue(Player* p);
	~gameEngine();
};
#endif
