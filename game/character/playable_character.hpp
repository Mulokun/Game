#ifndef _PLAYABLE_CHARACTER_
#define _PLAYABLE_CHARACTER_


class PlayableCharacter : public Character
{
    public :
         PlayableCharacter( void );
         ~PlayableCharacter( void );

    private :

        SkillTree * m_skillTree;
        unsigned short int m_experience;
        unsigned short int m_level;

};

#endif // _PLAYABLE_CHARACTER_
