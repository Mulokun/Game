#include "game_move_state.hpp"

#include "SFML/Audio.hpp"

#include "../engine/animation.hpp"
#include "../engine/state_manager.hpp"
#include "../engine/data_manager.hpp"


Game_MoveState::Game_MoveState( GameDatas * gameDatas, Entity * selected, std::vector< sf::Vector2i > path ) : m_gameDatas(gameDatas)
{
    init();

    m_selected = selected;
    m_path = path;
}

Game_MoveState::~Game_MoveState( void ) { }

void Game_MoveState::init( void )
{

}

void Game_MoveState::draw( sf::RenderTarget & window )
{
    m_gameDatas->level.draw( window );
    m_gameDatas->level.drawRoof( window );

    for(unsigned int i = 0; i < m_gameDatas->entities.size(); ++i) {
        Animation * a = m_gameDatas->entities[i]->getAnimation(STAY);
        if(a) {
            sf::Sprite * s = a->update();
            if(s) {
                s->setPosition( m_gameDatas->entities[i]->getPosition().x * Tileset::SizeTile,  m_gameDatas->entities[i]->getPosition().y * Tileset::SizeTile );
                window.draw(*s);
            }
        }
    }
}

void Game_MoveState::update( void )
{

}

void Game_MoveState::handleEvent( sf::Event & e )
{
    if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
    {
        StateManager::popState();
    }
}
