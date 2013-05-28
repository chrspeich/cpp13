#include "arraylist.hpp"
#include <cassert>
#include <algorithm>

using namespace std;

namespace Collections
{
	IElement* ArrayList::get(unsigned int index) const
	{
		assert(index < this->reservedElements);
		return this->elements[index];
	}

	void ArrayList::set(const IElement& newElement, unsigned int index)
	{
		assert(index < this->reservedElements);
		this->elements[index] = const_cast<IElement*>(&newElement);
		this->m_numElements = max(index, this->m_numElements);
	}

	void ArrayList::insert( const IElement& newElement )
	{
		// Resize the array if needed
		if (this->m_numElements >= this->reservedElements)
			this->reserve(2*this->reservedElements);

		this->elements[this->m_numElements] = const_cast<IElement*>(&newElement);
		this->m_numElements++;
	}

	void ArrayList::reserve(unsigned int reservation)
	{
		if (this->reservedElements < reservation) {
			this->reservedElements = reservation; // We should probabbly allocate more
			this->elements = reinterpret_cast<IElement**>(realloc(this->elements, this->reservedElements * sizeof(IElement*)));
			assert(this->elements);
		}
	}
};
