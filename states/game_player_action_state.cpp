#include "game_player_action_state.hpp"

#include "../engine/data_manager.hpp"
#include "../engine/state_manager.hpp"
#include "../engine/ui/widget.hpp"
#include "../engine/configuration.hpp"


Game_PlayerActionState::Game_PlayerActionState( GameDatas * gd, Character * selected ) : m_gameDatas(gd), m_selected(selected)
{
    init();
}

Game_PlayerActionState::~Game_PlayerActionState( void )
{

}


void Game_PlayerActionState::init( void )
{
    m_ui = new UI(this);

    Widget * w = NULL;
    GameEvent e;

    w = new Widget();
    w->setName("attack");
    w->setBackground( DataManager::getSprite("data/other/icon_attack.png") );
    sf::Vector2f p( m_selected->getPosition() );
    p.x *= Tileset::SizeTile;
    p.y *= Tileset::SizeTile;
    p.y -= 64;
    w->setPositionAbsolute(p);
    e.type = EV_ATTACK;
    w->setEvent(e);
    m_ui->addWidget(w);

    w = new Widget();
    w->setName("obj");
    w->setBackground( DataManager::getSprite("data/other/icon_obj.png") );
    p = sf::Vector2f(m_selected->getPosition());
    p.x *= Tileset::SizeTile;
    p.y *= Tileset::SizeTile;
    p.x -= 64;
    w->setPositionAbsolute(p);
    e.type = EV_USE_OBJ;
    w->setEvent(e);
    m_ui->addWidget(w);

    w = new Widget();
    w->setName("skill");
    w->setBackground( DataManager::getSprite("data/other/icon_skill.png") );
    p = sf::Vector2f(m_selected->getPosition());
    p.x *= Tileset::SizeTile;
    p.y *= Tileset::SizeTile;
    p.x += 64;
    w->setPositionAbsolute(p);
    e.type = EV_USE_SKILL;
    w->setEvent(e);
    m_ui->addWidget(w);

    w = new Widget();
    w->setName("end_turn");
    w->setBackground( DataManager::getSprite("data/other/icon_pass.png") );
    p = sf::Vector2f(m_selected->getPosition());
    p.x *= Tileset::SizeTile;
    p.y *= Tileset::SizeTile;
    p.y += 64;
    w->setPositionAbsolute(p);
    e.type = EV_END_TURN;
    w->setEvent(e);
    m_ui->addWidget(w);

    m_actionSelected = NULL;
}

void Game_PlayerActionState::draw( sf::RenderTarget & window )
{
    m_gameDatas->drawAll( window );
    m_ui->draw( window );

    /// Cursor

    if(m_actionSelected) {
        sf::RectangleShape r;
        r.setSize( sf::Vector2f(30, 30) );
        r.setFillColor( sf::Color::Transparent );
        r.setOutlineThickness(2);
        r.setOutlineColor(sf::Color::Green);
        r.setPosition(m_actionSelected->getPosition());
        window.draw(r);
    }
}

void Game_PlayerActionState::update( void )
{

}

void Game_PlayerActionState::handleEvent( sf::Event & e )
{
    if(e.type == sf::Event::KeyPressed) {

        if(e.key.code == Configuration::KEY_UP) {
            m_actionSelected = m_ui->getWidget("attack");
        }
        if(e.key.code == Configuration::KEY_DOWN) {
            m_actionSelected = m_ui->getWidget("end_turn");
        }
        if(e.key.code == Configuration::KEY_LEFT) {
            m_actionSelected = m_ui->getWidget("obj");
        }
        if(e.key.code == Configuration::KEY_RIGHT) {
            m_actionSelected = m_ui->getWidget("skill");
        }
        if(e.key.code == Configuration::KEY_A) {
            if(m_actionSelected) {
                addEvent(m_actionSelected->getEvent());
            }
        }
        if(e.key.code == Configuration::KEY_B) {
            StateManager::popState(2);
        }
    }
}

void Game_PlayerActionState::treatEvent( GameEvent e )
{
    if(e.type == EV_END_TURN) {
        m_selected->endTurn();
        StateManager::popState(3);
    }
}

