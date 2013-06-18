#pragma once
#pragma once

#include <memory>

namespace Math
{
	class Vector
	{
	public:
		/// Vector number-type.
		typedef float Element;
		
		/// Create empty from size, filled with a given value.
		/// \param size		vectors size
		/// \param value	value applied to all elements
		explicit Vector(unsigned int size, Element value = 0);

		/// Copy constructor.
		Vector(const Vector& vector);

		/// Destructor, releases allocated memory.
		~Vector();

		/// Returns number of elements
		unsigned int getNumElements() const { return m_size; }
		
		/// Destroys content of this instance and copies all data from the right one
		/// \param right	assigned Math::Vector
		/// \return Reference to this
		Vector& operator = (const Vector& right);

		/// Returns element at a given position.
		/// \param index	
		/// \return Reference to last element if index is invalid 
		Element operator [] (unsigned int index) const;

		/// Returns reference to element at a given position.
		/// \param index	
		/// \return Reference to last element if index is invalid
		Element& operator [] (unsigned int index);

		// TODO: Insert additional Operators (here or global where necessary)
		// -> Use const wherever possible and useful!
		// -> Where possible use methods in favor of global functions!
		//
		// Vector + Vector
		Vector operator + (const Vector& other) const;
		// Vector - Vector
		Vector operator - (const Vector& other) const;
		// Element * Vector
		Vector operator * (const Element& other) const;
		// Vector * Element
		// See below
		// Vector * Vector (scalar product, element wise multiplication, then sum)
		Element operator * (const Vector& other) const;
		// std::ostream << Vector (output as formated text)

	private:
		/// intern element array
		std::unique_ptr<Element[]> m_elements;

		/// number of elements
		unsigned int m_size;
	};

	static inline Vector operator * (const Vector::Element& left, const Vector& right) {
		return right * left;
	};

	std::ostream& operator<< (std::ostream &out, Vector &vector);
}
