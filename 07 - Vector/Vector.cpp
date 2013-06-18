#include "Vector.h"
#include <cassert>
#include <sstream>

namespace Math
{
	Vector::Vector(unsigned int size, Element value) : m_elements(new Element[size]), m_size(size)
	{
		for (unsigned int i = 0; i < size; i++)
			this->m_elements[i] = value;
	}

	Vector::Vector(const Vector& vector) : Vector(vector.getNumElements())
	{
		*this = vector;
	}

	Vector::~Vector()
	{
		// Unique seems to handle this for us
		this->m_elements.reset();
	}

	Vector& Vector::operator = (const Vector& right)
	{
		//assert(this->getNumElements() == right.getNumElements());

		for (unsigned int i = 0; i < right.getNumElements(); i++) {
			this->m_elements[i] = right[i];
		}

		return *this;
	}

	Vector::Element Vector::operator [] (unsigned int index) const
	{
		if (index >= this->getNumElements())
			index = this->getNumElements() - 1;

		return this->m_elements[index];
	}

	Vector::Element& Vector::operator [] (unsigned int index)
	{
		if (index >= this->getNumElements())
			index = this->getNumElements() - 1;

		return this->m_elements[index];
	}

	std::ostream& operator<< (std::ostream &out, Vector &vector)
	{
		out << "(";

		for (unsigned int i = 0; i < vector.getNumElements(); i++) {
			out << vector[i];

			if (i != vector.getNumElements() - 1)
				out << ", ";
		}

		out << ")";

		return out;
	}

	Vector Vector::operator + (const Vector& other) const
	{
		//assert(this->getNumElements() == other.getNumElements());

		Vector v(this->getNumElements());

		for (unsigned int i = 0; i < this->getNumElements(); i++) {
			v[i] = (*this)[i] + other[i];
		}

		return v;
	}

	Vector Vector::operator - (const Vector& other) const
	{
		//assert(this->getNumElements() == other.getNumElements());

		Vector v(this->getNumElements());

		for (unsigned int i = 0; i < this->getNumElements(); i++) {
			v[i] = (*this)[i] - other[i];
		}

		return v;
	}

	Vector Vector::operator * (const Element& other) const
	{
		Vector v(this->getNumElements());

		for (unsigned int i = 0; i < this->getNumElements(); i++) {
			v[i] = (*this)[i] * other;
		}

		return v;
	}

	Vector::Element Vector::operator * (const Vector& other) const
	{
		//assert(this->getNumElements() == other.getNumElements());

		Element result = 0;

		for (unsigned int i = 0; i < this->getNumElements(); i++) {
			result += (*this)[i] * other[i];
		}

		return result;
	}
}