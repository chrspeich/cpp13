#include "bitarray.hpp"
#include <cassert>
#include <string>
#include <iostream>

/// \brief A helper function to display the content of an BitArray.
/// \details To get the correct output of an array getSize() and get()
///		must be implemented correct. You can "test" you get().. if you
///		know what should be shown.
/// \param [in] array The array to be displayed.
/// \param [in] binaryRepresentation If true each bit of the array is shown
///		with an 0 or 1. If false a hexa decimal representation is printed.
///
///		Example [true]:		[7] 0110 001\n
///		Example [false]:	[7] 62
void outputHelper( const BiA::BitArray& array, bool binaryRepresentation )
{
	int len = BiA::getSize( array );
	// print array length
	std::cout << '[' << len << ']';
	if( binaryRepresentation )
	{
		// Just write each bit
		for( int i=0; i<len; ++i )
		{
			if( (i&3)==0 ) std::cout << ' ';
			std::cout << BiA::get(array, i);
		}
	} else
	{
		for( int i=0; i<len; i+=4 )
		{
			if( (i&15)==0 ) std::cout << ' ';
			unsigned char fourBitValue = (BiA::get(array, i) << 3) | (BiA::get(array, i+1) << 2) | (BiA::get(array, i+2) << 1) | BiA::get(array, i+3);
			// Create ASCII code for hexadecimal digit
			std::cout << char(fourBitValue + ((fourBitValue < 10) ? 48 : 87));
		}
	}
	std::cout << '\n';
}

/// \brief The main method contains a testing environment.
/// \details If your implementation runs through it is potential correct.
///		The main intention of this code is to help you implementing the
///		functions.
///
///		You can change the code and add further case to make individual tests.
int main()
{
	// Create and fill
	BiA::BitArray A1 = BiA::create( 17 );
	BiA::BitArray A2 = BiA::create( 91 );
	uint32_t initializationA1[] = { 0x0000a8c3 };
	for( int i=0; i<17; ++i )
		BiA::set( A1, i, (initializationA1[0] >> i)&1 );
	outputHelper( A1, true );
	outputHelper( A1, false );

	uint32_t initializationA2[] = { 0x98affa34, 0xaffeaffe, 0x07bcdef1 };
	for( int i=0; i<91; ++i )
		BiA::set( A2, i, (initializationA2[i/32] >> (i&0x1f))&1 );

	// Change a bit
	BiA::toggle( A1, 12 );
	BiA::toggle( A1, 17 );
	BiA::toggle( A2, 2 );
	BiA::toggle( A2, 18 );
	BiA::toggle( A2, 63 );
	BiA::set( A1, 1, BiA::get( A2, 23 ) );
	BiA::set( A2, 11, BiA::get( A1, 3 ) );

	BiA::BitArray A3 = BiA::concatenate( A1, A2 );
	uint32_t expectedResult[] = { 108, 0xe460b8c3, 0x5ffd3157, 0xbde25ffd, 0x00000f79 };
	// If the program stops here one or more of your operators didn't
	// work.
	for (int i = 0; i < std::min((unsigned long)BiA::getSize(A3)+1, sizeof(expectedResult)/sizeof(*expectedResult)); i++) {
		for (int j = 0; j < 32; j++)
			printf("%c", (A3[i] >> j)&0x1 ? '1' : '0');
		printf(" ? ");
		for (int j = 0; j < 32; j++)
			printf("%c", (expectedResult[i] >> j)&0x1 ? '1' : '0');
		printf("\n");
	}
	assert( memcmp( A3, expectedResult, 4*5 ) == 0 );

	// If you get a segmentation/.. error here you have written into the
	// wrong memory before.
	delete[] A1;
	delete[] A2;
	delete[] A3;

	return 0;
}