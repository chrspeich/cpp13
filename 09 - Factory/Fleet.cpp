#include "Fleet.h"
#include "SpaceShipFactory.h"

#include <fstream>
#include <assert.h>
#include <sstream>

Fleet::Fleet(const std::string& fleetFilename)
{
	// TODO:
	// * Open textfile in "fleetFilename"
	// * Parse line by line:
	// ** Seperate in shipname and parameter at the first ' '
	// ** call SpaceShipFactory::getInstance().buildSpaceShip
	// ** push into m_spaceShips if a new ship was successfully created
	std::ifstream infile(fleetFilename);
	std::string line;

	while (std::getline(infile, line))
	{
		std::stringstream stream(line);
		std::string spaceship;
		std::string parameter;

		stream >> spaceship;
		std::getline(stream, parameter);

		m_spaceShips.push_back(SpaceShipFactory::getInstance().buildSpaceShip(spaceship, parameter));
	}
}