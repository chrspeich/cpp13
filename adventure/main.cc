#include <iostream>
#include <cassert>

using namespace std;

typedef enum {
	Forest,
	Path,
	Sword,
	Cookie,
	Monster
} GameTile;

const uint8_t kGameSize = 10;

GameTile tiles[kGameSize][kGameSize] = {
	Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest,
	Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest,
	Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest,
	Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest,
	Forest, Forest, Forest, Forest, Path, Path, Path, Forest, Forest, Forest,
	Forest, Forest, Forest, Forest, Forest, Cookie, Forest, Forest, Forest, Forest,
	Forest, Forest, Forest, Forest, Forest, Monster, Forest, Forest, Forest, Forest,
	Forest, Forest, Forest, Path, Cookie, Path, Forest, Forest, Forest, Forest,
	Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest,
	Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest
};

struct Poistion {
	uint8_t x;
	uint8_t y;
}  currentPosition = {.x = 4, .y = 4};

int8_t myLive = 100;
int8_t monsterLive = 100;

void monsterMayHit()
{
	if (rand() % 10 == 5) {
		cout << "The monster takes a bite and you loos some of you health" << endl;
		myLive -= 34;
	}
}

void runGame()
{
	bool needFights = false;
	string action;

	switch(tiles[currentPosition.y][currentPosition.x]) {
	case Path:
		cout << "You're in a forest" << endl;
		break;
	case Sword:
		cout << "You found a sword and picked it up" << endl;
		break;
	case Cookie:
		cout << "You found a cookie and refilled your health" << endl;
		myLive = 100;
		break;
	case Monster:
		cout << "You encountered a evil monster who wants to steal your cookies" << endl;
		needFights = true;
		monsterMayHit();
		break;
	default:
		assert(false);
	}

	getline(cin, action);

	if (myLive <= 0) {
		cout << "You died" << endl;

		exit(0);
	}

	if (needFights) {
		if (action == "hit with sword") {
			if (rand() % 10 != 5) {
				cout << "You hit the monster with your sword and it lost some health" << endl;
				monsterLive -= 34;
			}
			else {
				cout << "You missed the monster" << endl;
			}

			if (monsterLive <= 0) {
				cout << "You defeated the monster" << endl;
				tiles[currentPosition.y][currentPosition.x] = Path;
			}
		}
		else {
			cout << "You can not do that!" << endl;
		}
	}
	else if (action == "go north") {
		if (currentPosition.y == 0 || tiles[currentPosition.y - 1][currentPosition.x] == Forest) {
			cout << "You can not go there!" << endl;
		}
		else {
			currentPosition.y--;
		}
	}
	else if (action == "go south") {
		if (currentPosition.y == kGameSize-1 || tiles[currentPosition.y + 1][currentPosition.x] == Forest) {
			cout << "You can not go there!" << endl;
		}
		else {
			currentPosition.y++;
		}
	}
	else if (action == "go east") {
		if (currentPosition.x == kGameSize-1 || tiles[currentPosition.y][currentPosition.x + 1] == Forest) {
			cout << "You can not go there!" << endl;
		}
		else {
			currentPosition.x++;
		}
	}
	else if (action == "go west") {
		if (currentPosition.x == 0 || tiles[currentPosition.y][currentPosition.x - 1] == Forest) {
			cout << "You can not go there!" << endl;
		}
		else {
			currentPosition.x--;
		}
	}
	else {
		cout << "You can not do that!" << endl;
	}

	cout << endl;
}

int main(int argc, char** argv)
{
	srand(time(NULL));

	cout << "Welcome to a adventure." << endl;

	while(true)
		runGame();

	return 0;
}