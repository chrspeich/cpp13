#include "list.hpp"

namespace Collections
{
	SingleLinkedList::SingleLinkedList() : firstBucket(nullptr)
	{

	}

	SingleLinkedList::~SingleLinkedList()
	{
		if (this->firstBucket != nullptr)
			delete this->firstBucket;
	}

	SingleLinkedList::Bucket::Bucket(IElement& element) : nextBucket(nullptr), element(element)
	{
	}

	SingleLinkedList::Bucket::~Bucket()
	{
		if (this->nextBucket != nullptr)
			delete this->nextBucket;
	}

	SingleLinkedList::Bucket* SingleLinkedList::Bucket::getNext() const
	{
		return this->nextBucket;
	}

	void SingleLinkedList::Bucket::setNext(SingleLinkedList::Bucket* bucket)
	{
		this->nextBucket = bucket;
	}

	IElement& SingleLinkedList::Bucket::getElement() const
	{
		return this->element;
	}

	void SingleLinkedList::insert( const IElement& newElement )
	{
		if (this->firstBucket == nullptr) {
			this->firstBucket = new Bucket(const_cast<IElement&>(newElement));
		}
		else {
			Bucket* lastBucket = this->firstBucket;

			while (lastBucket->getNext() != nullptr)
				lastBucket = lastBucket->getNext();

			lastBucket->setNext(new Bucket(const_cast<IElement&>(newElement)));
		}

		this->m_numElements++;
	}

	SingleLinkedList::Iterator::Iterator(Bucket* bucket) : currentBucket(bucket)
	{
	}



	IElement* SingleLinkedList::Iterator::next()
	{
		if (this->currentBucket != nullptr)
			this->currentBucket = this->currentBucket->getNext();

		return this->current();
	}

	IElement* SingleLinkedList::Iterator::current() const
	{
		if (this->currentBucket != nullptr) {
			return &this->currentBucket->getElement();
		}
		else {
			return nullptr;
		}
	}

	ICollection::IIterator* SingleLinkedList::getIterator() const
	{
		return new Iterator(this->firstBucket);
	}
}