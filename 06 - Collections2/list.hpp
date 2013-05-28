#pragma once

#include "collection.hpp"

namespace Collections
{
	class SingleLinkedList: public ICollection
	{
		struct ListEntry
		{
			ListEntry* next;
			IElement* data;

			ListEntry( ListEntry* next, IElement* data ) : next(next), data(data)		{}
			~ListEntry()	{ delete data; }
		};

		ListEntry* m_first;
	public:
		SingleLinkedList() : m_first(nullptr)		{}
		SingleLinkedList(const SingleLinkedList& other) : ICollection()
		{
			IIterator* iter = other.getIterator();

			IElement* element;
			while ((element = iter->next()))
				insert(*element);

			delete iter;
		}

		SingleLinkedList(const ICollection& other) : ICollection()
		{
			IIterator* iter = other.getIterator();

			IElement* element;
			while ((element = iter->next()))
				insert(*element);

			delete iter;
		}

		~SingleLinkedList();

		/// \brief Inserts elements at the front of the list.
		///
		virtual void insert( const IElement& newElement ) override;

		class ListIterator: public IIterator
		{
			ListEntry* m_current;
		public:
			ListIterator( ListEntry* start ) : m_current(start)		{}

			/// \brief Goes to the next element in the collection.
			/// \return The next/new element or nullptr at the end.
			virtual IElement* next() override;

			/// \brief Access the current element without changing the iterator
			///
			virtual IElement* current() const override;
		};

		/// \brief Creates a one-time iterator.
		///
		virtual IIterator* getIterator() const override;
	};
};