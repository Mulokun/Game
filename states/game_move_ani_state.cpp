#include "game_move_ani_state.hpp"

#include "SFML/Audio.hpp"

#include "../engine/animation.hpp"
#include "../engine/state_manager.hpp"
#include "../engine/data_manager.hpp"
#include "../engine/time.hpp"
#include "../engine/foo.hpp"

#include "game_player_action_state.hpp"


Game_MoveAniState::Game_MoveAniState( GameDatas * gd, Character * selected, std::vector< sf::Vector2i > path ) : m_gameDatas(gd), m_selected(selected), m_path(path), m_speed(3.0f)
{
    init();
}

Game_MoveAniState::~Game_MoveAniState( void ) { }

void Game_MoveAniState::init( void )
{
    m_currentPosition = sf::Vector2f( m_selected->getPosition().x * Tileset::SizeTile, m_selected->getPosition().y * Tileset::SizeTile );
    m_path.erase(m_path.begin());
    m_it = 0;
}

void Game_MoveAniState::draw( sf::RenderTarget & window )
{
    m_gameDatas->level.draw( window );

    for(unsigned int i = 0; i < m_gameDatas->playerEntities.size(); ++i) {
        if(m_gameDatas->playerEntities[i] != m_selected) {
            Animation * a = m_gameDatas->playerEntities[i]->getAnimation(ANI_STAY);
            if(a) {
                sf::Sprite * s = a->update();
                if(s) {
                    s->setPosition( m_gameDatas->playerEntities[i]->getPosition().x * Tileset::SizeTile,  m_gameDatas->playerEntities[i]->getPosition().y * Tileset::SizeTile );
                    window.draw(*s);
                }
            }
        }
    }

    for(unsigned int i = 0; i < m_gameDatas->enemyEntities.size(); ++i) {
        if(m_gameDatas->enemyEntities[i] != m_selected) {
            Animation * a = m_gameDatas->enemyEntities[i]->getAnimation(ANI_STAY);
            if(a) {
                sf::Sprite * s = a->update();
                if(s) {
                    s->setPosition( m_gameDatas->enemyEntities[i]->getPosition().x * Tileset::SizeTile,  m_gameDatas->enemyEntities[i]->getPosition().y * Tileset::SizeTile );
                    window.draw(*s);
                }
            }
        }
    }

    /// Draw animated entity

    sf::Vector2f positionToGo = sf::Vector2f( m_path[m_it].x * Tileset::SizeTile, m_path[m_it].y * Tileset::SizeTile );
    sf::Vector2f directionToGo = direction(m_currentPosition, positionToGo);
    Animation * a = m_selected->getAnimation(ANI_STAY);

    if( std::abs((int)directionToGo.x) > std::abs((int)directionToGo.y) ) {
        if(directionToGo.x > 0) {
            a = m_selected->getAnimation(ANI_RIGHT);
        } else {
            a = m_selected->getAnimation(ANI_LEFT);
        }
    } else {
        if(directionToGo.y > 0) {
            a = m_selected->getAnimation(ANI_DOWN);
        } else {
            a = m_selected->getAnimation(ANI_UP);
        }
    }

    if(a) {
        sf::Sprite * s = a->update();
        if(s) {
            s->setPosition( m_currentPosition );
            window.draw(*s);
        }
    }

    m_gameDatas->level.drawRoof( window );
}

void Game_MoveAniState::update( void )
{
    if(m_it >= m_path.size()) {
        //StateManager::popState(2);
        StateManager::addState( new Game_PlayerActionState(m_gameDatas, m_selected) );
        /// TODO : changer pour ajouter un autre state ...
    } else {
        sf::Vector2f positionToGo( m_path[m_it].x * Tileset::SizeTile, m_path[m_it].y * Tileset::SizeTile );
        float distanceTotal = m_speed * Time::deltaTime();

        if(distanceEuclidienne(positionToGo, m_currentPosition) <= distanceTotal) {
            positionToGo = sf::Vector2f( m_path[m_it].x * Tileset::SizeTile, m_path[m_it].y * Tileset::SizeTile );
            m_selected->setPosition(m_path[m_it]);
            distanceTotal -= distanceEuclidienne(positionToGo, m_currentPosition);
            m_currentPosition = positionToGo;
            m_it++;
        } else {
            sf::Vector2f directionToGo = normalize( direction(m_currentPosition, positionToGo) );
            m_currentPosition.x += directionToGo.x * distanceTotal;
            m_currentPosition.y += directionToGo.y * distanceTotal;
        }
    }
}

void Game_MoveAniState::handleEvent( sf::Event & e )
{

}

void Game_MoveAniState::treatEvent( GameEvent e )
{

}
