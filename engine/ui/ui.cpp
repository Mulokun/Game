#include "ui.hpp"

#include <fstream>
#include <iostream>

#include "widget.hpp"
#include "../state.hpp"

UI::UI( State * parent ) : m_parentState(parent) { }

UI::~UI( void ) { }

void UI::addWidget( Widget * w )
{
    this->m_contents.push_back( w );
}

void UI::draw( sf::RenderTarget & window )
{
    for( std::list< Widget* >::iterator i = this->m_contents.begin(); i != this->m_contents.end(); i++ )
    {
        window.draw( * (*i) );
    }
}

Widget * UI::getWidget( std::string name )
{
    Widget * w = NULL;

    for( std::list< Widget* >::iterator i = this->m_contents.begin(); i != this->m_contents.end(); i++ )
    {
        if( (*i)->getName() == name )
        {
            w = (*i);
        }
    }

    return w;
}
