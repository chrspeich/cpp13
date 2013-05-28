#include <iostream>

#include "duck.hpp"

// Making some duckish sounds
void Duck::quack() const
{
	std::cout << m_quacking << std::endl;
}

// Create a copy of this duck on the heap (new).
Collections::IElement* Duck::clone() const
{
	return new Duck(m_quacking);
}