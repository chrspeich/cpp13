#pragma once

#include "element.hpp"
#include <string>

/**
* A sweet quacking, probably yellow, duck.
* Does duck things.
*/
class Duck : public Collections::IElement
{
public:
	Duck(const std::string& quackingPhrase) : 
		m_quacking(quackingPhrase)
	{}

	/// \brief Making some duckish sounds
	///
	void quack() const;

	/// \brief Create a copy of this duck on the heap (new).
	///
	virtual IElement* clone() const override;

private:
	const std::string m_quacking;
};