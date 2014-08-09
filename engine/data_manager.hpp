#ifndef _DATA_MANAGER_
#define _DATA_MANAGER_


#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


class DataManager
{

    public :

        static void kill( void );

        // Font :

        static sf::Font * addFont( const std::string path );
        static sf::Font * getFont( const std::string path );

        // Graphics :

        static sf::Texture * getTexture( const std::string path );
        static sf::Texture * addTexture( const std::string path );

        static sf::Sprite * addSprite( const std::string path );
        static sf::Sprite * addSprite( const std::string path, sf::FloatRect r );
        static sf::Sprite * getSprite( const std::string path );
        static sf::Sprite * getSprite( const std::string path, sf::FloatRect r );

        // Audios :

        static sf::SoundBuffer * getSoundBuffer( const std::string path );
        static sf::SoundBuffer * addSoundBuffer( const std::string path );


    private :
        DataManager( void );
        ~DataManager( void );

        static DataManager * singleton;

        std::map<std::string, sf::Texture*> m_textures;
        std::map<std::string, sf::Sprite*> m_sprites;
        std::map<std::string, sf::SoundBuffer*> m_sounds;
        std::map<std::string, sf::Font *> fonts;

};

#endif // _DATA_MANAGER_
