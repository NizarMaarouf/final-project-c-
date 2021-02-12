#include "Instruction.h"
#include <iostream>
using namespace std;

const int start_amount = START_AMOUNT;
Instruction::Instruction(string name, int number, bool isJail, bool isStart) :Slot(name, number)
{
	jail = isJail;
	start = isStart;
}

void Instruction::goToJail(Player* p)
{
	p->goToJail();
}

void Instruction::ChangeBalance(Player* p, int amount)
{
	p->setBalance(amount);
}

bool Instruction::play(Player* p)
{
	int number;
	printSlot();
	if (jail) goToJail(p);
	else if (start) ChangeBalance(p, start_amount);
	else {
		number = getCard(p);
		if (number > 0)
			cout << "Get More " << number << endl;
		else
			cout << "Give Back " << (-number) << endl;
		ChangeBalance(p, number);
	}
	return true; // continue game
}

void Instruction::printSlot()
{
	cout << "slot name " << this->getName() << "\ntype: Instruction" << endl;
}

int Instruction::getCard(Player* p)
{
	return p->getCard();
}
