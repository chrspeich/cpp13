#pragma once

#include <string>
#include <vector>
#include <memory>

// predeclaration saves us from including the SpaceShips.h
class SpaceShip;

/// A Fleet, basically a collection of Spaceships and some fleetwide properties
class Fleet
{
public:
	/// Create from fleetfile.
	/// \param fleetFilename	Filename of txt file containing a fleet description
	Fleet(const std::string& fleetFilename);

private:
	std::vector<std::shared_ptr<SpaceShip>> m_spaceShips;
};

