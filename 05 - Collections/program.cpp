#include <iostream>

#include "list.hpp"
#include "duck.hpp"

/// \brief Copies objects between arbitrary collections.
/// \details This is an example test method - don't ask why to copy each second
///		element.
/// \param [in] input The original collection from which objects should be
///		copied.
/// \param [out] output An existing collection. If the collection already
///		contains elements the ones from the input are added and the old remain.
void copyEverySecondObject(const Collections::ICollection& input, Collections::ICollection& output)
{
	auto it = input.getIterator();
	while(it->current())
	{
		output.insert(*it->current());
		// Up to two steps (at least one)
		if(it->next()) it->next();
	}
	delete it;
}


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
	Duck duckChild("quack");
	Duck duckMother("QUACKQUACKQUACK");

	// add ducks
	Collections::SingleLinkedList duckList;
	for( int i=0; i<5; ++i )
		duckList.insert( duckChild );
	duckList.insert(duckMother);

	// do some ducking
	outputDucks(duckList);

	// the wolf
	std::cout << "The wolf attacks!\n";
	Collections::SingleLinkedList reducedDuckList;
	copyEverySecondObject(duckList, reducedDuckList);

	// do some ducking
	outputDucks(reducedDuckList);

	return 0;
}