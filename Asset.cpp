#include "Asset.h"
#include <iostream>
#include <string>
#include <time.h>
using namespace std;

const float interest = INTEREST;

Asset::Asset(string name, int number, string city, int price, int rent) : Slot(name, number)
{
	this->city = city;
	this->price = price;
	this->rent = rent;
	this->owner = NULL; //free
	this->yearsMortgaged = 0;
}


bool Asset::operator==(const Asset& asset) {
	if (asset.getCity() ==  this->city)
	{
		if(this->slotName == asset.getName())
			return true;
		return false;
	}
	return false;
}

//func called if player wants to check mortgage asset
int Asset::checkMortgagedPrice()
{
	return (this->price * this->yearsMortgaged * interest);
}

/*function will check if asset is mortgaged and ownd by the player - if true and player can pay mortgage asset will by active.
if asset is free and player can buy - asset will by added to player.
if asset is owned by another player, player will pay rent, if player can't pay game end
returns false if game ends*/

bool Asset::buyAsset(Player* p)
{
	string answer;
	//buy free asset
	if (owner == NULL)
	{
		cout << "Asset has no owner \nprice:" << price << endl;
		cout << "does Player " << p->getPlayerName() << " want to buy this asset?\n"<<"yes or no?" << endl;
		cin >> answer;
		if (p->getBalance() >= price && answer == "yes")
		{
			p->addAsset(this);
			p->setBalance(-(price));
			owner = p;
			cout << p->getPlayerName() << " now own " << this->getName() << " in " << city << "\nplayer balance: " << p->getBalance() << endl;
			return true;
		}
		cout << p->getPlayerName() << (answer == "no" ? " doesn't want to buy this asset" : " does not have enough money to buy this asset") << endl;
		return true; //continue game.
	}
	//pay rent
	else if (owner != p)
	{
		cout << "asset is owned by " << owner->getPlayerName() << endl;
		if (p->payRent(rent)) //if rent not payed - game over for player!
		{
			if (this->getYearsMortgaged() == 0)
				owner->setBalance(rent);
			return true;
		}
		return false;
	}
	cout << "asset is owned by " << owner->getPlayerName() << endl;
	return true; // game continues
}

bool Asset::play(Player* p)
{
	this->printSlot();
	return buyAsset(p);
}

void Asset::printSlot()
{
	cout << "slot name: " << this->getName() << "\ntype: Asset" << " in " << city << "\
			\nrent: " << rent << "\nprice: " << price << "\nOwner: " << (owner? owner->getPlayerName() : "No Owner") << endl;
}


int Asset::mortgagedAsset()
{
	this->addYear();
	return this->price;
}

void Asset::freeAssetMortagaged()
{
	this->yearsMortgaged = 0;
}

void Asset::freeAsset()
{
	this->freeAssetMortagaged();
	this->owner = NULL;
}