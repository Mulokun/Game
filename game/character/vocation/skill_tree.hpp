#ifndef _SKILL_TREE_
#define _SKILL_TREE_

class SkillTree
{
    private :

        std::vector< Skill * > m_skills[10];

    public :

        SkillTree( void );
        ~SkillTree( void );

        void init( void ) = 0;
        std::vector< Skill * > getSkillsAtLevel( unsigned int level );

};

#endif // _SKILL_TREE_

