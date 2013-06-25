#include "SpaceShipFactory.h"

// If SpaceShips.h would be not included, the SpaceShip's destructor would be unknown.
// This leads normally to a warning
#include "SpaceShips.h"

std::shared_ptr<SpaceShip> SpaceShipFactory::buildSpaceShip(const std::string& spaceShipTypeName, const std::string& parameter)
{
	auto creator = m_createSpaceShipFuncRegister[spaceShipTypeName];
	return creator(parameter);
}

void SpaceShipFactory::registerSpaceShip(const std::string& spaceShipTypeName, const CreateSpaceShipFunc& createSpaceShipFunc)
{
	m_createSpaceShipFuncRegister.insert(
		std::make_pair<std::string, CreateSpaceShipFunc>((std::string)spaceShipTypeName, (CreateSpaceShipFunc)createSpaceShipFunc));
}
