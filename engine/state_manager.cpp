#include "state_manager.hpp"

#include "state.hpp"

StateManager * StateManager::singleton = NULL;

void StateManager::kill( void )
{
    if(StateManager::singleton)
    {
        for(unsigned int i = 0; i < StateManager::singleton->m_stateManaged.size(); ++i) {
            delete StateManager::singleton->m_stateManaged.top();
            StateManager::singleton->m_stateManaged.pop();
        }

        delete StateManager::singleton;
        StateManager::singleton = NULL;
    }
}


StateManager::StateManager( void ) : m_current(NULL), m_pop(false) { }

StateManager::~StateManager( void )
{
    while( ! m_stateManaged.empty() )
    {
        State * s = m_stateManaged.top();
        delete s;
        s = NULL;
        m_stateManaged.pop();
    }
}


void StateManager::update( void )
{
    if(StateManager::singleton == NULL)
    {
        StateManager::singleton = new StateManager;
    }

    if(StateManager::singleton->m_current) {
        StateManager::singleton->m_current->update();
    }
}

void StateManager::draw( sf::RenderTarget & window )
{
    if(StateManager::singleton == NULL)
    {
        StateManager::singleton = new StateManager;
    }

    if(StateManager::singleton->m_current) {
        StateManager::singleton->m_current->draw( window );
    }
}

void StateManager::handleEvent( sf::Event & e )
{
    if(StateManager::singleton == NULL)
    {
        StateManager::singleton = new StateManager;
    }

    if(StateManager::singleton->m_current) {
        StateManager::singleton->m_current->handleEvent( e );
    }
}

void StateManager::addState( State * s )
{
    if(StateManager::singleton == NULL)
    {
        StateManager::singleton = new StateManager;
    }

    StateManager::singleton->m_stateManaged.push( s );
}


void StateManager::popState( unsigned int popNb )
{
    if(StateManager::singleton == NULL)
    {
        StateManager::singleton = new StateManager;
    }

    StateManager::singleton->m_pop = popNb;
}

void StateManager::deleteState( void )
{
    if(StateManager::singleton == NULL)
    {
        StateManager::singleton = new StateManager;
    }

    while( StateManager::singleton->m_pop > 0 )
    {
        StateManager::singleton->m_pop--;

        State * s = StateManager::getCurrent();
        if(s)
        {
            delete s;
            s = NULL;
            StateManager::singleton->m_stateManaged.pop();
            if (!StateManager::singleton->m_stateManaged.empty())
            {
                StateManager::singleton->m_current = StateManager::singleton->m_stateManaged.top();
            }
        }
    }
}


State * StateManager::getCurrent( void )
{
    if(StateManager::singleton == NULL)
    {
        StateManager::singleton = new StateManager;
    }

    return StateManager::singleton->m_current;
}

void StateManager::setCurrent( void )
{
    if(StateManager::singleton == NULL)
    {
        StateManager::singleton = new StateManager;
    }

    StateManager::deleteState();

    if(!isEmpty())
    {
        StateManager::singleton->m_current = StateManager::singleton->m_stateManaged.top();
    }
    else
    {
        StateManager::singleton->m_current = NULL;
    }
}

bool StateManager::isEmpty( void )
{
    if(StateManager::singleton == NULL)
    {
        StateManager::singleton = new StateManager;
    }

    return StateManager::singleton->m_stateManaged.empty();
}

