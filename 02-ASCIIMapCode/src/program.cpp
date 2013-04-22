#include <iostream>
#include <ctime>

char** createSomeMap();
void freeMap( char** );
void drawMap( char** );
void moveMap( char** );


int main()
{
	// Don't call srand() somewhere else.
	// Use a constant number instead of clock() if you wanna see the
	// same landscape each time (e.g. for debugging purposes)
	srand( clock() );

	char** map = createSomeMap();

	do
	{
		drawMap( map );
		moveMap( map );
	} while( std::cin.get() == '\n' );

	return 0;
}