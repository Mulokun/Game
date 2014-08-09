#ifndef _CORE_WIDGET_
#define _CORE_WIDGET_


#include <SFML/Graphics.hpp>

#include "../foo.hpp"
#include "../game_event.hpp"


class Animation;


class Widget : public sf::Drawable
{

    public :
        Widget( void );
        virtual ~Widget( void );

        //virtual void loadFromFile( const std::string & path, const std::string & name );

        void setName( std::string name );
        std::string getName( void ) const;

        /*
        void setPadding( float x, float y );
        void setPadding( sf::Vector2f p );
        void setSize( float x, float y );
        void setSize( sf::Vector2f p );

        void setBorder( Something * );
            |-> List de sf::Drawable, pour draw les bord, angle, ... pour aller avec une taille variable
        */
        void setBackground( sf::Sprite * s );
        void setAnimation( Animation * a );
        Animation * getAnimation( void ) const;
        void setText( sf::Text * s );
        sf::Text * getText( void ) const;
/*
        void setOverBackground( sf::Sprite * s );
        void setOverAnimation( Animation * a );
        Animation * getOverAnimation( void ) const;
        void setOverText( sf::Text * s );
        sf::Text * getOverText( void ) const;
*/
        void setPositionRelative( RelativePosition p );
        void setPositionAbsolute( float x, float y );
        void setPositionAbsolute( sf::Vector2f p );
        void move( float x, float y );
        void move( sf::Vector2f p );
        sf::Vector2f getPosition( void ) const;

        sf::FloatRect getBounds( void );

        void update( void );

        void setShow( bool b );
        bool isShow( void ) const;

        void setEvent( GameEvent e );
        GameEvent getEvent() const;

        bool isOver( const sf::Vector2i & p ) const;
        bool isSetelected() const;
        void select( bool b );
        GameEvent active() const;


    protected :

        //! Inherited from sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        std::string m_name;

        sf::Sprite * m_background;
        sf::Vector2f m_backgroundPosition;
        sf::Text * m_text;
        Animation * m_animation;
/*
        sf::Sprite * m_overBackground;
        sf::Text * m_overText;
        Animation * m_overAnimation;
*/
        sf::Vector2f m_position;

        sf::FloatRect m_bounds;
        sf::FloatRect m_parentBounds;

        bool m_selected;
        GameEvent m_event;

        bool m_show;

};

#endif // _CORE_WIDGET_
