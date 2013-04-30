#pragma once

#include <cstdint>

namespace BiA
{
	/// \brief The bitarray is based on a very simple integer array.
	/// \details The first 32Bit-int denotes the size of the array!
	///		Afterward ceil(size/32) further ints are following.
	typedef uint32_t* BitArray;

	/// \brief Creates a bitarray with at least enough space for numElements
	/// bits.
	/// \details You have to delete the BitArray with delete!
	///
	///		 Create sets all bits to 0.
	BitArray create( int numElements );

	/// \brief Returns the number of elements in the array.
	///
	int getSize( const BitArray& array );

	/// \brief Check if the bit is set to 1.
	///
	bool get( const BitArray& array, int index );

	/// \brief Set a bit to a value (true=1/false=0)
	///
	void set( BitArray& array, int index, bool value );

	/// \brief Invert the bit at index.
	///
	void toggle( BitArray& array, int index );

	/// \brief Create a new array containing all elements of the two arrays
	///		from input.
	BitArray concatenate( const BitArray& array1, const BitArray& array2 );

	/// \brief Combine two arrays with a logically or.
	/// \details If the arrays have a different size use the larger one as
	///		reference. The smaller array is continued with zeros.
	///
	///		The result has to be written into array1. If array 1 is the smaller
	///		one you must replace its memory. Make sure there is no memory
	///		leak or access voilation.
	///
	///		Remark: this function is bad software design. Returning a new array
	///		would be a better choice, but the exercise gain is higher in that
	///		way.
	// BUGFIX: or is a reserved keyword in C/C++ and can not be used as function name here
	void or2( BitArray& array1, const BitArray& array2 );
};