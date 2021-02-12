#pragma once
#include "Player.h"
#include <string>
using namespace std;

class Player;
class Slot
{
protected:
	int slotNumber;
	string slotName;
public:
	Slot(string name, int number);
	Slot(Slot& s) { throw exception{ "Can't Copy Slots" }; }
	virtual bool play(Player* p) = 0;
	virtual void printSlot() = 0;
	string getName() const { return slotName; }
	int getNumber() const { return slotNumber; }
};
