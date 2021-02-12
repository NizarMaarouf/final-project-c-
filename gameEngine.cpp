#include "gameEngine.h"
#include "Instruction.h"
#include "Asset.h"
#include <time.h>

const int max_size = MAX_SIZE;
const int min_size = MIN_SIZE;
const int n = N;


gameEngine::gameEngine(string fileLocation, int amountOfPlayers)
{
	Player* temp;
	string name;
	int number;
	this->boardSize= countLines(fileLocation);
	Board = new Slot * [boardSize];
	try {
		this->createBoard(fileLocation);
	}
	catch(exception& e){
		cout << e.what() << endl;
		return;
	}
	for (int i = 0; i < amountOfPlayers; i++)
	{
		cout << "Type your name: ";
		cin >> name;
		temp = new Player(name, this);
		this->playersQueue.push(temp);
	}
	for (int i = 0; i < n; i++)
	{
		number = (rand() % 701) -(350);
		this->cardsDeck.push(number);
	}
}


void gameEngine::createBoard(string fileLocation)
{
	char buf[min_size], sign[min_size], name[max_size], city[max_size], number[max_size];
	int rent, price, i = 0;
	string name1, city1, buf1;
	filebuf  file;
	file.open(fileLocation, std::ios::in);
	if (!file.is_open())
	{
		throw exception{ " wrong file" };
		
	}

	std::istream is(&file);

	buf[0] = '\0';
	city[0] = '\0';
	sign[0] = '\0';
	name[0] = '\0';
	while (!is.eof())
	{
		is.clear();
		is.getline(buf, min_size, ',');
		buf1 = buf;
		if (buf1.find("I") != std::string::npos)
		{
			is.getline(sign, min_size, ',');
			is.getline(name, max_size, '\n');
			name1 = name;
			switch (sign[0]) {
			case 'S':
				Board[i] = new Instruction(name1, (i + 1), false, true);
				i++;
				break;
			case 'J':
				Board[i] = new Instruction(name1, (i + 1), true, false);
				i++;
				break;
			default:
				Board[i] = new Instruction(name1, (i + 1), false, false);
				i++;
				break;
			}
		}
		else if (buf1.find("P") != std::string::npos)
		{
			is.getline(city, max_size, ',');
			city1 = city;
			is.getline(name, max_size, ',');
			name1 = name;
			is.getline(number, max_size, ',');
			price = atoi(number);
			number[0] = '\0';
			is.getline(number, max_size, '\n');
			rent = atoi(number);
			number[0] = '\0';
			Board[i] = new Asset(name1, (i + 1), city1, price, rent);
			i++;
		}
		else if (is.eof())
			break;
		else
			throw exception{ "error,every line needs to start with P or I"};

		//clearing the strings
		buf[0] = '\0';
		city[0] = '\0';
		sign[0] = '\0';
		name[0] = '\0';
	}
}

void gameEngine::returnPlayertoQueue(Player* p)
{
	this->playersQueue.push(p);
}


int gameEngine::countLines(string fileLocation)
{
	int count = 0;
	string line;
	ifstream file(fileLocation);
	while(getline(file, line))
	{
		count++;
	}	
	return count;
}

int gameEngine::getCard()
{
	int temp = cardsDeck.front();
	cardsDeck.pop();
	cardsDeck.push(temp);
	return temp;
}


int gameEngine::getBoardSize()
{
	return this->boardSize;
}

Slot* gameEngine::getLocationSlot(int position)
{
	return Board[position];
}

int gameEngine::getAmountOfPlayers()
{
	return this->playersQueue.size();
}

Player* gameEngine::getNextPlayer()
{
	Player* temp = this->playersQueue.front();
	this->playersQueue.pop();
	return temp;
}


gameEngine::~gameEngine()
{
	int size = this->getBoardSize();
	this->cardsDeck.empty();
	this->playersQueue.empty();
	for (int i = 0; i < size; i++)
	{
		delete Board[i];
	}
	delete[] Board;
}
