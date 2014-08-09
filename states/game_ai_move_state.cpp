#include "game_ai_move_state.hpp"

#include "../engine/state_manager.hpp"


Game_AIMoveState::Game_AIMoveState( GameDatas * gd, Character * selected ) : m_gameDatas(gd), m_selected(selected)
{
    init();
}

Game_AIMoveState::~Game_AIMoveState( void )
{

}

void Game_AIMoveState::init( void )
{

}

void Game_AIMoveState::draw( sf::RenderTarget & window )
{
    m_gameDatas->drawAll( window );
}

void Game_AIMoveState::update( void )
{
    StateManager::popState();
}

void Game_AIMoveState::handleEvent( sf::Event & e )
{

}

void Game_AIMoveState::treatEvent( GameEvent e )
{

}
