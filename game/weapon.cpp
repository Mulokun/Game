#include "weapon.hpp"

Weapon::Weapon( void ) : init()
{

}

Weapon::~Weapon( void )
{

}

void Weapon::init( std::string name, unsigned int range, unsigned int radius, unsigned int damage, unsigned int accuraty, unsigned int criticalChance )
{
    m_name = name;
    m_range = range;
    m_radius = radius;
    m_damage = damage;
    m_accuraty = accuraty;
    m_criticalChance = criticalChance;
}

void Weapon::setSprite( sf::Sprite * s )
{
    m_sprite = s;
}

void Weapon::loadFromFile( const std::string fileName )
{

}


int Weapon::getRange( void ) const
{
    return m_range;
}

int Weapon::getRadius( void ) const
{
    return m_radius;
}

int Weapon::getDamage( void ) const
{
    return m_damage;
}

int Weapon::getAccuraty( void ) const
{
    return m_accuraty;
}


int Weapon::damage( Character * owner, Character * target )
{
    return m_damage + owner->bonusDamage() + target->bonusResistance();
}

int Weapon::hitChance( Character * owner, Character * target )
{
    return m_accuraty + owner->bonusHitChance() + target->bonusAvoidChance();
}

