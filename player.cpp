#include "Player.h"
#include "Asset.h"
#include "gameEngine.h"
#include <iostream>
#include <time.h>
using namespace std;


int start_amount = START_AMOUNT;

Player::Player(string name, gameEngine* game)
{
	this->name = name;
	balance = start_amount;
	indicator = false;
	position = 1; //slot index = 1;
	assetList = new Asset * [1];
	assetCount = 0;
	this->game = game;
}

bool Player::operator !=(const Player& p)
{
	if (name != p.name)//same player name = same plyaer.
		return true;
	return false;
}

void Player::goToJail()
{
	indicator = true;
}

string Player::getPlayerName() const
{
	return name;
}

int Player::getBalance() const
{
	return balance;
}

bool Player::setBalance(int amount)
{
	this->changeBalance(amount);
	if (amount > 0)
		this->LookToFreeAsset();
	else if(balance < 0)
		return (this->lookForAssetToMortgage());
	return true;
}

bool Player::getIndicator()
{
	return indicator;
}

int Player::getPosition()
{
	return position;
}

void Player::addAsset(Asset* a)
{
	Asset** tmp = new Asset * [assetCount + 1];
	int i;
	for (i = 0; i < assetCount; i++)
		tmp[i] = assetList[i];
	tmp[i] = a;
	assetCount++;
	if (!assetList)delete[] assetList;
	assetList = tmp;
}

//if player doesn't have enoght money in balanca - call mortgagedAsset() in Board. if player stiil canot pay - game over - return false.
bool Player::payRent(int amount)	
{
	
	Asset* tmp = NULL;
	cout << "player needs to pay rent of: " << amount << "\nplayers balance: " << balance << endl;
	if (setBalance(-(amount))) //pay rent
	{
		cout << name << " payed rent, new balance: " << balance << endl;
		return true;
	}
	return false;
	
}

/*called from mortgaged asset if player paid for morgage*/
void Player::LookToFreeAsset()
{
	int tempAmount;
	for (int i = 0; i < assetCount; i++)
	{
		if (assetList[i]->getYearsMortgaged() > 0)
		{
			tempAmount = assetList[i]->checkMortgagedPrice();
			if (tempAmount < balance)
			{
				changeBalance(-(tempAmount));
				assetList[i]->freeAssetMortagaged();
				cout << "player " << this->getPlayerName() << "has free the asset:" << endl;
				assetList[i]->printSlot();
			}
		}
	}
}

void Player::updateCurrLocation(int idx)
{
	bool passSatrt = false;
	position += idx;
	if (position > game->getBoardSize()) //pass start
	{
		passSatrt = true;
		position -= game->getBoardSize();
		balance += start_amount;
		this->addYearstoAssets();
	}

	if (passSatrt)
		cout << name << " passed start colect 350" << endl;
	cout << "new position: " << position << endl;
}

bool Player::drawDice()
{
	srand(time(NULL));
	if (indicator)// player in jail.
	{
		indicator = false;// out of jail.
		cout << name << " is out of jail" << endl;
		return true; // end turn.
	}
	int draw = (rand() % 5) + 1; // random number between 1 and 6;
	cout << name << " is in position: " << position << endl;
	updateCurrLocation(draw);
	return game->getLocationSlot(position - 1)->play(this); //play slot.
}

bool Player::lookForAssetToMortgage()
{
	int ind = 0;
	int assetPrice;
	while (balance < 0)
	{
		if (ind >= assetCount)
		{
			cout << "player don't have asset to mortgage" << endl;
			return false;
		}
		assetPrice = assetList[ind]->getPrice();
		if (assetList[ind]->getYearsMortgaged() > 0) //asset already moetgaged.
			ind++;
		else //enter if there are asset in list to mortgage. 
		{
			assetPrice = assetList[ind]->mortgagedAsset();
			cout << "player mortggage assest:" << endl;
			assetList[ind]->printSlot();
			changeBalance(assetPrice);
			ind++;
		}
	}
	return true;

}

void Player::changeBalance(int amount)
{
	balance = balance + amount;
}

int Player::getCard()
{
	return game->getCard();
}

void Player::addYearstoAssets()
{
	for (int i = 0; i < assetCount; i++)
	{
		if (assetList[i]->getYearsMortgaged() > 0)
			assetList[i]->addYear();
	}
}

Player::~Player()
{
	for (int i = 0; i < assetCount; i++)
	{
		assetList[i]->freeAsset();
	}
	delete[] assetList;
}
