#include "game_datas.hpp"

#include "../engine/animation.hpp"

GameDatas::GameDatas( void )
{

}

GameDatas::~GameDatas( void )
{

}


void GameDatas::drawAll( sf::RenderTarget & window )
{
    level.draw( window );
    drawAllEntities( window );
    level.drawRoof( window );
}

void GameDatas::drawAllEntities( sf::RenderTarget & window )
{
    drawPlayerEntities( window );
    drawEnemyEntities( window );
}

void GameDatas::drawPlayerEntities( sf::RenderTarget & window )
{
    for(unsigned int i = 0; i < playerEntities.size(); ++i) {
        Animation * a = playerEntities[i]->getAnimation(ANI_STAY);
        if(a) {
            sf::Sprite * s = a->update();
            if(s) {
                s->setPosition( playerEntities[i]->getPosition().x * Tileset::SizeTile,  playerEntities[i]->getPosition().y * Tileset::SizeTile );
                window.draw(*s);
            }
        }
    }
}

void GameDatas::drawEnemyEntities( sf::RenderTarget & window )
{
    for(unsigned int i = 0; i < enemyEntities.size(); ++i) {
        Animation * a = enemyEntities[i]->getAnimation(ANI_STAY);
        if(a) {
            sf::Sprite * s = a->update();
            if(s) {
                s->setPosition( enemyEntities[i]->getPosition().x * Tileset::SizeTile,  enemyEntities[i]->getPosition().y * Tileset::SizeTile );
                window.draw(*s);
            }
        }
    }
}
