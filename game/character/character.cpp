#include "character.hpp"

#include <cmath>

#include "../../engine/animation.hpp"
#include "../../engine/time.hpp"
#include "../../engine/foo.hpp"

Character::Character( void )
{
    init();
}

Character::~Character( void )
{
    //delete all animation
}


void Character::init( void )
{
    randomizeStat();

    m_position = sf::Vector2i( 0, 0 );
    m_mobility = 5;
    m_timeElapsed = 0;
    m_ready = false;
}


void Character::addAnimation( AnimationType type, std::string animationFile )
{
    m_animationSet[type] = new Animation(animationFile);
}

Animation * Character::getAnimation( AnimationType type )
{
    std::map< AnimationType, Animation * >::iterator it = m_animationSet.find(type);
    if( it != m_animationSet.end() ) {
        return it->second;
    } else {
        return NULL;
    }
}


sf::Vector2i Character::getPosition( void ) const
{
    return m_position;
}

void Character::setPosition( sf::Vector2i position )
{
    m_position = position;
}

void Character::setPosition( int x, int y )
{
    setPosition( sf::Vector2i(x, y) );
}

unsigned int Character::getMobility( void ) const
{
    return m_mobility;
}


void Character::setTimeElapsed( unsigned int time )
{
    m_timeElapsed += time;

    while( m_timeElapsed > Character::WaitingTime ) {
        m_timeElapsed -= Character::WaitingTime;
        if(m_AP < Character::MaxAP) {
            m_AP++;
        }
        m_ready = true;
    }
}

unsigned int Character::getTimeRemain( void ) const
{
    return Character::WaitingTime - m_timeElapsed;
}

bool Character::isReady( void ) const
{
    return m_ready;
}

void Character::endTurn( void )
{
    m_ready = false;
}

unsigned int Character::getAP( void ) const
{
    return m_AP;
}

bool Character::useAP( unsigned int nb )
{
    if(m_AP >= nb) {
        m_AP -= nb;
        return true;
    }
    else { return false; }
}


void Character::randomizeStat( void )
{
    m_statHeight = std::rand() % 6 + 1;
    m_statMind = std::rand() % 6 + 1;
    m_statMuscle = std::rand() % 6 + 1;
    m_statTechnic = std::rand() % 6 + 1;
    m_statWeight = std::rand() % 6 + 1;

    m_currentHP = getMaxHP();
}

unsigned int Character::getMaxHP( void ) const
{
    float coef = 1;
    if(m_statMuscle == 1) { coef = 1.2; }
    else if(m_statMuscle == 2) { coef = 1.1; }

    return 7 + ( m_statHeight * m_statWeight ) * coef; /// Entre 8 et 52 (moy : 18)
}

unsigned int Character::getCurrentHP( void ) const
{
    return m_currentHP;
}

int Character::bonusAvoidChance( void ) const
{
    int chance = 2 + (m_statTechnic - 3);
    if(m_statMind > 3) { chance += (m_statMind - 4); }

    chance += (m_statHeight + m_statWeight - 5) * (-1);

    return chance; /// Entre -7 et 10
}

int Character::bonusHitChance( void ) const
{
    int chance = (-2) + (m_statTechnic - 2);
    if(m_statMind > 3) { chance += (m_statMind - 4); }

    return chance * 2; /// Entre -6 et 8 (2par2)
}

int Character::bonusBaseDamage( void ) const
{
    int damage = (m_statMuscle - 3);
    if(m_statHeight >= 3 && m_statWeight >= 3) { damage += (m_statHeight + m_statWeight) - 6; }

    return damage; /// Entre -2 et 9
}

int Character::bonusResistance( void ) const
{
    int resistance = std::abs(m_statMuscle - 3);
    resistance += (m_statWeight - 3);

    return resistance; /// Entre -2 et 6
}


void Character::takeDamage( unsigned int damage )
{
    if( damage > m_currentHP ) { m_currentHP = 0; }
    else { m_currentHP -= damage; }
}


unsigned int Character::getStatHeight( void ) const
{
    return m_statHeight;
}

unsigned int Character::getStatWeight( void ) const
{
    return m_statWeight;
}

unsigned int Character::getStatMuscle( void ) const
{
    return m_statMuscle;
}

unsigned int Character::getStatTechnic( void ) const
{
    return m_statTechnic;
}

unsigned int Character::getStatMind( void ) const
{
    return m_statMind;
}

unsigned int Character::getStatLevel( void ) const
{
    return ( m_statHeight + m_statMind + m_statMuscle + m_statTechnic + m_statWeight ) / 5;
}

std::string Character::statSymbol( unsigned int value )
{
    switch( value ) {
        case 0 : return "null"; break;
        case 1 : return "--"; break;
        case 2 : return "-"; break;
        case 3 : return "="; break;
        case 4 : return "+"; break;
        case 5 : return "++"; break;
        case 6 : return "*"; break;
        case 7 : return "**"; break;
        case 8 : return "***"; break;
        case 9 : return "*****"; break;
        case 10 : return "*****"; break;
        default : return "??"; break;
    }

    return "??";
}


void Character::equipWeapon( Weapon * weapon )
{
    m_weapon = weapon;
}

Weapon * Character::getWeapon( void ) const
{
    return m_weapon;
}

