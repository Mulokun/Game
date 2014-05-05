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
        void setAnimation( AnimationType type );

        sf::Vector2f getPosition( void ) const;
        void move( sf::Vector2f direction );

        void draw( sf::RenderTarget & target );

    private :
        Animation * m_animation;
        std::map< AnimationType, Animation * > m_animationSet;

        sf::Vector2f m_position;
        float m_speed;

};

#endif // _ENTITY_
