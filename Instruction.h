#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "Slot.h"
#include <string>
using namespace std;

class Slot;
class gameEngine;
#define START_AMOUNT (int)350;

class Instruction : public Slot {
	bool jail;
	bool start;
public:
	Instruction(string name, int number, bool isJail, bool isStart);
	void goToJail(Player* p);
	void ChangeBalance(Player* p, int amount);
	bool play(Player* p); //returns true if game is still on.
	void printSlot();
	int getCard(Player* p);

};

#endif

