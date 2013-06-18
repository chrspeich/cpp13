#include "profiler.hpp"
#include <chrono>
#include <iostream>


void heavyWork1()
{
	PROFILE
	std::cout << "I am working\n";
}

int heavyWork2( int n )
{
	PROFILE
	int sum = 0;
	for( int i=0; i<n; ++i )
		sum += i;
	return sum;
}


int main()
{
	PROFILE

	freopen("cerroutput.txt", "wb", stderr);

	std::cerr << "Your clock has " << std::chrono::high_resolution_clock::period::den / std::chrono::high_resolution_clock::period::num
		<< " ticks per second\n\n";

	for( int i=0; i<1000; ++i )
	{
		heavyWork1();
		std::cout << heavyWork2(i) << std::endl;
	}

	return 0;
}