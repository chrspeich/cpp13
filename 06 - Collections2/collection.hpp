#pragma once

#include "element.hpp"

namespace Collections
{

	/**
	 * Interface for the most elementary operations of a collection/container.
	 */
	class ICollection
	{
	protected:
		unsigned int m_numElements;

		ICollection() : m_numElements(0)	{}

	public:
		/// \brief Implementation of a destructor to remove everything
		///		stored in this container.
		virtual ~ICollection() {}

		/// \brief Inserts this element into the collection.
		/// \param [in] newElement Element to be inserted.
		///		This method uses `clone()` so you can do what you want with
		///		your original and it can be a stack-variable too.
		virtual void insert( const IElement& newElement ) = 0;

		unsigned int getNumElements() const		{ return m_numElements; }

		class IIterator
		{
		public:
			/// \brief Goes to the next element in the collection.
			/// \return The next/new element or nullptr at the end.
			virtual IElement* next() = 0;

			/// \brief Access the current element without changing the iterator
			///
			virtual IElement* current() const = 0;

			virtual ~IIterator() {}
		};

		/// \brief Creates a one-time iterator.
		///
		virtual IIterator* getIterator() const = 0;
	};
};