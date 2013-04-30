#include <string>
#include <cstdlib>
#include "bitarray.hpp"


BiA::BitArray BiA::create( int numElements )
{
	// 1 - size variable
	// numElements/32 - number of uint32_t for all bits rounded down
	// round up:  (numElements+31)/32
	int numInts = 1 + ((numElements+31)/32);
	BitArray theNewOne = new uint32_t[numInts];
	theNewOne[0] = numElements;
	memset( theNewOne+1, 0, numInts*4-4 );
	return theNewOne;
}

namespace BiA {

int getSize( const BitArray& array )
{
	return array[0];
}

bool get( const BitArray& array, int index )
{
	uint32_t bucket = index/32;
	index %= 32;

	// All elements after the last are false
	if (bucket >= getSize(array))
		return false;

	return (array[bucket + 1] >> index) & 0x1;
}

void set( BitArray& array, int index, bool value )
{
	uint32_t bucket = index/32;
	index %= 32;

	// All elements after the last are ignored
	if (bucket >= getSize(array))
		return;

	if (value)
		array[bucket + 1] |= 1 << index;
	else
		array[bucket + 1] &= ~(1 << index);
}

void toggle( BitArray& array, int index )
{
	set(array, index, !get(array, index));
}

BitArray concatenate( const BitArray& array1, const BitArray& array2 )
{
	BitArray array = create(getSize(array1) + getSize(array2));

	// Copy the first bit array
	memcpy(array+1, array1+1, getSize(array1) * sizeof(*array1));
	if (getSize(array1) % 32 == 0) // Great size is properly aligned, just copy this over
		memcpy(array+1+getSize(array1) * sizeof(*array1), array2+1, getSize(array2) * sizeof(*array2));
	else {// Damn... the alignement is wrong, so we do a expensive bit-wise copy
		for (uint32_t i = 0; i < getSize(array2); i++) {
			set(array, getSize(array1) + i, get(array2, i));
		}
	}

	return array;
}

void or2( BitArray& array1, const BitArray& array2 )
{
	// Need to resize first array
	if ((getSize(array1)+31)/32 < (getSize(array2)+31)/32) {
		BitArray array1Old = array1;

		array1 = create(getSize(array2));

		memcpy(array1+1, array1Old+1, getSize(array1Old)*sizeof(*array1Old));

		delete[] array1;
	}

	for (int i = 0; i < getSize(array1); ++i)
		array1[i+1] |= array2[i+1];
}

}
