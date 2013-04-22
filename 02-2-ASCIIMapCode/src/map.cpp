#include <stdlib.h>
#include <iostream>


const int WHITE_NOISE_SIZE = 16;
const int MAP_SIZE_Y = 25;
const int MAP_SIZE_X = 80;
int MOVE=1;

/// \brief A non changing 1D helper "texture"
/// \details This array is filled by the createSomeMap method.
unsigned char whiteNoise[WHITE_NOISE_SIZE];

/// \brief Generates one column of the terrain.
/// \details This method is bugfree. It must not be touched to solve the
///		exersise.
///
///		The static keyword makes the fillColumn method only visible in this
///		file.
/// \param destination An array or a part of an array with the size of
///		MAP_SIZE_Y to capture the new column.
/// \param mapXCoordinate Generating a column with the same X coordinate will
///		always produce the same pattern.
static void fillColumn( char* destination, unsigned int mapXCoordinate )
{
	// Fractal noise for terrain height
	int numSky = ( whiteNoise[ (mapXCoordinate/16) % WHITE_NOISE_SIZE ]*4
				 + whiteNoise[ (mapXCoordinate/8) % WHITE_NOISE_SIZE ]*2
				 + whiteNoise[ (mapXCoordinate/4) % WHITE_NOISE_SIZE ]
				 + whiteNoise[ (mapXCoordinate/2) % WHITE_NOISE_SIZE ]/2
				 ) / 100 + 3;

	for( int y=0; y<MAP_SIZE_Y; ++y )
	{
		if( y < numSky ) destination[y] = (y>10) ? 2 : 0;
		else if( y < numSky+1 && y <= 10 ) destination[y] = 1;
		else if( whiteNoise[ mapXCoordinate % WHITE_NOISE_SIZE ]/15 == y-5 ) destination[y] = 4;
		else destination[y] = 3;
	}
}

/// \brief Creates a 2D array and fills it with some ASCII graphics.
/// \details This also fills the whiteNoise array which is used for the
///		fillColumn method.
char* createSomeMap()
{
	for( int i=0; i<WHITE_NOISE_SIZE; ++i )
		// BUGFIX use the standard way for rand numbers in a range
		whiteNoise[i] = rand() % 255;

	char* map = new char[MAP_SIZE_X * MAP_SIZE_Y];
	// Create and fill the map
	for( int x=0; x< MAP_SIZE_X; ++x )
	{
		fillColumn(map + (x * MAP_SIZE_Y), x);
	}
	return map;
}

/// \brief Creates a picture of the map by using different characters for
///		different materials.
const char ASCII_ART[] = {' ', '+', '-', '#', 'o'};
void drawMap( char* map )
{
	for( int y=0; y<MAP_SIZE_Y; ++y )
	{
		for( int x=0; x<MAP_SIZE_X; ++x )
		{
			std::printf( "%c", ASCII_ART[ static_cast<int>(map[x * MAP_SIZE_Y + y]) ] );
		}
		std::cout << '\n';
	}
}

/// \brief Somehow moves the map by one.
///
void moveMap( char* map )
{
	memmove(map, map + MAP_SIZE_Y, MAP_SIZE_Y * (MAP_SIZE_X-1));
	// Move white noise
	memmove(whiteNoise, whiteNoise + 1, WHITE_NOISE_SIZE - 1);
	whiteNoise[WHITE_NOISE_SIZE - 1] = rand() % 255;
	fillColumn(map + MAP_SIZE_Y * (MAP_SIZE_X-1), MAP_SIZE_X-1);
}

void freeMap( char* map )
{
	delete[] map;
}