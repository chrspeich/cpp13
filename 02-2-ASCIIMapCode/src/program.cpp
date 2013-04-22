#include <iostream>
#include <ctime>

char* createSomeMap();
void freeMap( char* );
void drawMap( char* );
void moveMap( char* );


int main()
{
	// Don't call srand() somewhere else.
	// Use a constant number instead of clock() if you wanna see the
	// same landscape each time (e.g. for debugging purposes)
	// BUGFIX: clock does NOT give back a the current time as probbably wanted
	// it givs back the time consumed by this process, as main is the first function called
	// it will always be quite close to 0 and more or less constant.
	// For proper initialization use time(NULL) which will truly depend on the current time
	srand( time(NULL) );

	char* map = createSomeMap();

	do
	{
		drawMap( map );
		moveMap( map );
	} while( std::cin.get() == '\n' );

	freeMap(map);

	return 0;
}