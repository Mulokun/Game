#ifndef _WEAPON_
#define _WEAPON_


class Weapon
{

    public :
        Weapon( void );
        ~Weapon( void );

        void init( std::string name = "noname", unsigned int range = 0, unsigned int radius = 1, unsigned int damage = 0, unsigned int accuraty = 100, unsigned int criticalChance = 0 );
        void setSprite( sf::Sprite * s );
        void loadFromFile( const std::string fileName );

        int getRange( void ) const;
        int getRadius( void ) const;
        int getDamage( void ) const;
        int getAccuraty( void ) const;
        //int getCriticalChance( void ) const;

        int damage( Character * owner, Character * target );
        int hitChance( Character * owner, Character * target );

    private :

        std::string m_name;
        sf::Sprite * m_sprite;

        unsigned int m_range;
        unsigned int m_radius; /// min = 1
        unsigned int m_damage;
        unsigned int m_accuraty;
        unsigned int m_criticalChance;

};

#endif // _WEAPON_
