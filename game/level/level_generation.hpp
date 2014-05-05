#ifndef _LEVEL_GENERATION_H_
#define _LEVEL_GENERATION_H_

#include <string>

class Level;

Level * generateLevel( const std::string pathTileset, unsigned int width, unsigned int height );


#endif // _LEVEL_GENERATION_H_
