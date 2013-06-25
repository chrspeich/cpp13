#include <string>
#include <cstdlib>
#include "SpaceShipFactory.h"
#include "SpaceShips.h"
#include "Fleet.h"

using namespace std;

int main()
{
	// Register SpaceShips by using the SpaceShipFactory::getInstance().registerSpaceShip with lambda functions.

	// TODO: Register TieFighter with SpaceShipFactory::getInstance().registerSpaceShip
	// The string parameter contains the pilot.
	SpaceShipFactory::getInstance().registerSpaceShip("TieFighter", [](const string& args) {
		return shared_ptr<SpaceShip>(new TieFighter(args));
	});
	
	// TODO: Register DeathStar
	// The string parameter has to be interpreted a float, determining its buildProgress
	SpaceShipFactory::getInstance().registerSpaceShip("DeathStar", [](const string& args) {
		return shared_ptr<SpaceShip>(new DeathStar(atof(args.c_str())));
	});

	// TODO: Register Destroyer
	// The string parameter has to be interpreted a int, determining the number of lasers
	// Note that the a appropriate parameterized instance of the "Destroyer"-class should be created.
	SpaceShipFactory::getInstance().registerSpaceShip("Destroyer", [](const string& args) {
		return shared_ptr<SpaceShip>(new Destroyer(false, atoi(args.c_str())));
	});

	// TODO: Register LargeDestroyer
	// The string parameter has to be interpreted a int, determining the number of lasers.
	// Note that the a appropriate parameterized instance of the "Destroyer"-class should be created.
	SpaceShipFactory::getInstance().registerSpaceShip("LargeDestroyer", [](const string& args) {
		return shared_ptr<SpaceShip>(new Destroyer(true, atoi(args.c_str())));
	});

	// Loads fleet from file
	Fleet imperialFleet("imperialships.txt");
}