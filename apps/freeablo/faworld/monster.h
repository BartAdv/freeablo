#ifndef W_MONSTER_H
#define W_MONSTER_H

#include "actor.h"
#include "monsterstats.h"
namespace DiabloExe
{
    struct Monster;
}

namespace FAWorld
{
    class Monster: public Actor
    {
        public:
            Monster(const DiabloExe::Monster& monster, Position pos, ActorStats * stats=nullptr);
            std::string getDieWav();
            std::string getHitWav();
            FARender::FASpriteGroup getCurrentAnim();
            MonsterStats * mStats;
            int32_t getCurrentHP();
            void takeDamage(double amount);



        private:
            std::string mAnimPath;
            std::string mSoundPath;

    };
}

#endif     
