#pragma once

#include <cstdlib>
#include <cstring>
#include "collection.hpp"

using namespace std;

namespace Collections
{
	class ArrayList: public ICollection
	{
		IElement** elements;
		unsigned int reservedElements;
	public:
		ArrayList() : ICollection(), elements(nullptr), reservedElements(0) {
			this->reserve(8);
		};

		ArrayList(const ArrayList& other) : ICollection(), elements(nullptr), reservedElements(other.reservedElements)
		{
			m_numElements = other.m_numElements;
			this->elements = reinterpret_cast<IElement**>(malloc(this->reservedElements * sizeof(IElement*)));
			memcpy(this->elements, other.elements, this->reservedElements * sizeof(IElement*));
		}

		ArrayList(const ICollection& other) : ArrayList()
		{
			IIterator* iter = other.getIterator();

			IElement* element;
			while ((element = iter->next()))
				insert(*element);

			delete iter;
		}

		virtual ~ArrayList()
		{
			if (this->elements)
				free(this->elements);
		}

		/// \brief Gets an element by index
		/// \param index	Arrayindex of the inquired element. Will check validity only in debug-mode!
		/// \return Inquired element or nullptr
		IElement* get(unsigned int index) const;

		/// \brief Sets an element by index.
		/// \remarks Will delete the old element
		/// \param index	Arrayindex of the array element that will be overwritten. Will check validity only in debug-mode!
		void set(const IElement& newElement, unsigned int index);

		/// \brief Reserves memory for a given number of elements.
		/// \details This method preserves all previous inserted data. It can
		///		be used to resize the array.
		/// \remarks If the list is already bigger, this function will do nothing
		void reserve(unsigned int reservation);

		virtual void insert( const IElement& newElement );

		class Iterator : public IIterator
		{
			unsigned int idx;
			const ArrayList& list;
		public:
			Iterator(const ArrayList& list) : list(list){};
			virtual IElement* next()
			{
				idx++;


				return this->current();
			}

			virtual IElement* current() const
			{
				if (idx <= list.getNumElements())
					return list.get(idx);
				else
					return nullptr;
			}

			virtual ~Iterator() {}
		};

		virtual IIterator* getIterator() const
		{
			return new Iterator(*this);
		}
	};
};