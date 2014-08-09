#ifndef _CHARACTER_
#define _CHARACTER_


#include <string>
#include <SFML/Graphics.hpp>


class Animation;


typedef enum {
    ANI_STAY,
    ANI_UP,
    ANI_DOWN,
    ANI_LEFT,
    ANI_RIGHT
} AnimationType;


class Character
{

    public :

        Character( void );
        ~Character( void );

        void init( void );

        /// -----------
        /// Animation :

    public :
        //void initAnimation( std::string animationsInitFile );
        void addAnimation( AnimationType type, std::string animationFile );
        Animation * getAnimation( AnimationType type );
    private :
        std::map< AnimationType, Animation * > m_animationSet;


        /// -----------
        /// Mobility :

    public :
        void setPosition( sf::Vector2i position );
        void setPosition( int x, int y );
        sf::Vector2i getPosition( void ) const;
        unsigned int getMobility( void ) const;
    private :
        sf::Vector2i m_position;
        unsigned int m_mobility;

        /// -----------
        /// AP :

    public :
        void setTimeElapsed( unsigned int time );
        unsigned int getTimeRemain( void ) const;
        bool useAP( unsigned int nb );
        unsigned int getAP( void ) const;
        void endTurn( void );
        bool isReady( void ) const;
    private :
        static const unsigned int MaxAP = 4;
        static const unsigned int WaitingTime = 100;
        unsigned int m_AP;
        unsigned int m_timeElapsed;
        bool m_ready;

        /// -----------
        /// Stats :
        /*
        **  Toutes les stats ont une valeur entre 1 et 6,
        **  Représenté en jeu par "--" pour 1, "-" pour 2, "=" pour 3, "+" pour 4, "++" pour 5 et "*" pour 6.
        */

    public :
        void randomizeStat( void );
        unsigned int getMaxHP( void ) const;
        unsigned int getCurrentHP( void ) const;
        int bonusAvoidChance( void ) const;
        int bonusHitChance( void ) const;
        int bonusBaseDamage( void ) const;
        int bonusResistance( void ) const;
        void takeDamage( unsigned int damage );
        unsigned int getStatHeight( void ) const;
        unsigned int getStatWeight( void ) const;
        unsigned int getStatMuscle( void ) const;
        unsigned int getStatTechnic( void ) const;
        unsigned int getStatMind( void ) const;
        unsigned int getStatLevel( void ) const;
        static std::string statSymbol( unsigned int value );
    private :
        short int m_statHeight;
        short int m_statWeight;
        short int m_statMuscle;
        short int m_statTechnic;
        short int m_statMind;
        unsigned int m_currentHP;
        unsigned int m_HPMax;

        /// ----------
        /// Skill / Weapon

    public :
        void equipWeapon( Weapon * weapon );
        Weapon * getWeapon( void ) const;
    private :
        Weapon * m_weapon;
};

#endif // _ENTITY_
