#include <iostream>

#include "arraylist.hpp"
#include "list.hpp"
#include "duck.hpp"

void outputDucks(const Collections::ICollection& duckcollection)
{
	std::cout << "The list contains " << duckcollection.getNumElements() << " ducks.\n";
	auto it = duckcollection.getIterator();
	while(it->current())
	{
		reinterpret_cast<Duck*>(it->current())->quack();
		it->next();
	}
	delete it;
}

int main()
{
	Duck linkedListDuck("quack->quack");
	Duck arrayDuck("quackquack");

	// add ducks
	Collections::SingleLinkedList singleLinkedList;
	for( int i=0; i<5; ++i )
		singleLinkedList.insert( linkedListDuck );
	Collections::ArrayList arrayList;
	for( int i=0; i<5; ++i )
		arrayList.insert( arrayDuck );

	// do some explicit ducking
	reinterpret_cast<Duck*>(arrayList.get(1))->quack();
	reinterpret_cast<Duck*>(arrayList.get(3))->quack();

	// reset an element
	arrayList.set(Duck("kuckuk!"), 3);

	// output per iterator
	outputDucks(arrayList);

	// swap!
	std::cout << "\nSwapping\n";
	Collections::ArrayList arrayListFromLinkedList(singleLinkedList);
	Collections::SingleLinkedList singleLinkedListFromArrayList(arrayList);

	// output per loop
	for(unsigned int i=0; i<arrayListFromLinkedList.getNumElements(); ++i)
		reinterpret_cast<Duck*>(arrayList.get(i))->quack();

	return 0;
}