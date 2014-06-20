#ifndef _ENTITY_
#define _ENTITY_


#include <string>
#include <SFML/Graphics.hpp>


class Animation;


typedef enum {
    STAY,
    UP,
    DOWN,
    LEFT,
    RIGHT
} AnimationType;


class Entity
{

    public :
        Entity( void );
        ~Entity( void );

        //void initAnimtion( std::string animationsInitFile );
        void addAnimation( AnimationType type, std::string animationFile );
        Animation * getAnimation( AnimationType type );

        sf::Vector2i getPosition( void ) const;
        void setPosition( sf::Vector2i position );
        void setPosition( int x, int y );
        unsigned int getMobility( void ) const;

        void setTimeElapsed( unsigned int time );
        unsigned int getTimeRemaining( void ) const;
        unsigned int getAP( void ) const;

    private :
        std::map< AnimationType, Animation * > m_animationSet;

        sf::Vector2i m_position;
        unsigned int m_mobility;

        static const unsigned int MaxAP = 4;
        static const unsigned int WaitingTime = 100;
        unsigned int m_AP;
        unsigned int m_timeElapsed;
};

#endif // _ENTITY_
