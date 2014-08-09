#ifndef _CORE_GAME_EVENT_
#define _CORE_GAME_EVENT_

typedef enum GameType{
    EV_ATTACK,
    EV_END_TURN,
    EV_USE_OBJ,
    EV_USE_SKILL,
    EV_DEFAULT
} GameType;


typedef struct GameEvent {
    GameType type;
    int number;
    std::string text;
} GameEvent;

#endif // _CORE_GAME_EVENT_
