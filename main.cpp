#include <iostream>
#include <cstdlib>
#include <ctime>
#include <typeinfo>
#include "Slot.h"
#include "Asset.h"
#include "Player.h"
#include "gameEngine.h"


using namespace std;

const string path = "board.txt";


void main()
{
	gameEngine* game;
	string answer;
	Player* currentPlayer;
	int playersAmount;
	cout << "How Many Players want to play?" << endl;
	cin >> playersAmount;
	while (playersAmount < 2)
	{
		cout << "Not Enough Players, try Again\n"<<  "How Many Players want to play?" <<endl;
		cin >> playersAmount;
	}
	game = new gameEngine(path, playersAmount);

	while (game->getAmountOfPlayers() >= 2)
	{
		currentPlayer = game->getNextPlayer();
		cout << "\ndoes player " << currentPlayer->getPlayerName() << " wants to keep playing?\n" << "yes or no?" << endl;
		cin >> answer;
		if (!(answer.compare("yes")))
		{
			if (currentPlayer->drawDice())
				game->returnPlayertoQueue(currentPlayer);
			else {
				cout << "player " << currentPlayer->getPlayerName() << " lost the game" << endl;
				delete currentPlayer;
			}
		}
		else
		{
			cout << "player " << currentPlayer->getPlayerName() << " lost the game"<<endl;
			delete currentPlayer;
		}
	}
	currentPlayer = game->getNextPlayer();
	cout << "the winner is " << currentPlayer->getPlayerName() << endl;
	delete currentPlayer;
	delete game;
}