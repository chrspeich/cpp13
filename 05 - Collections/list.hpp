#pragma once

// QUESTION: can the following line be replaced with class
// ICollection predeclaration?
#include "collection.hpp"

namespace Collections
{
	class SingleLinkedList : public ICollection {
		class Bucket {
		private:
			Bucket* nextBucket;
			IElement& element;

		public:
			Bucket(IElement& element);
			~Bucket();

			Bucket* getNext() const;
			void setNext(Bucket* bucket);
			IElement& getElement() const;
		};

		Bucket* firstBucket;
	public:
		SingleLinkedList();
		~SingleLinkedList();

		void insert( const IElement& newElement );

		class Iterator : public IIterator
		{
			Bucket* currentBucket;
		protected:
			Iterator(Bucket* bucket);
			friend class SingleLinkedList;
		public:
			IElement* next();

			IElement* current() const;
		};

		IIterator* getIterator() const;
	};
}
