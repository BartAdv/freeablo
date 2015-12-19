#ifndef ACTOR_H
#define ACTOR_H

#include "position.h"

#include "../farender/renderer.h"
#include "../fasavegame/savegame.h"
#include <boost/format.hpp>
#include <misc/misc.h>
#include <map>

namespace FAWorld
{
    class ActorStats;
    class World;

    namespace AnimState
    {
        enum AnimState
        {
            walk,
            idle,
            attack,
            dead,
            hit
        };
    }    
    class Actor : public NetObject
    {
        public:
            Actor(const std::string& walkAnimPath="",
                  const std::string& idleAnimPath="",
                  const Position& pos = Position(0,0),
                  const std::string& dieAnimPath="",
                  ActorStats* stats=nullptr);

            void update(bool noclip, size_t ticksPassed);
            void setStats(ActorStats* stats);
            virtual ~Actor();

            virtual std::string getDieWav(){return "";}
            virtual std::string getHitWav(){return "";}
            virtual void setSpriteClass(std::string className){UNUSED_PARAM(className);}
            bool mAnimPlaying = false;
            bool isAttacking = false;
            virtual FARender::FASpriteGroup getCurrentAnim();
            void setAnimation(AnimState::AnimState state, bool reset=false);
            void setWalkAnimation(const std::string path);
            void setIdleAnimation(const std::string path);            
            AnimState::AnimState getAnimState();

            virtual void setLevel(GameLevel* level);
            GameLevel* getLevel();

            virtual bool attack(Actor * enemy)
            {
                UNUSED_PARAM(enemy);
                return false;
            }
            Position mPos;            
        //private: //TODO: fix this
            FARender::FASpriteGroup mWalkAnim;
            FARender::FASpriteGroup mIdleAnim;
            FARender::FASpriteGroup mDieAnim;
            FARender::FASpriteGroup mAttackAnim;
            FARender::FASpriteGroup mHitAnim;
        
            size_t mFrame;
            virtual void die();
            std::pair<size_t, size_t> mDestination;
            std::pair<size_t, size_t>& destination()
            {
                return mDestination;
            }

            bool isDead() const;
            bool isEnemy() const;
            std::map<AnimState::AnimState, size_t> mAnimTimeMap;
            ActorStats * mStats=nullptr;
            virtual size_t getWriteSize();
            virtual bool writeTo(ENetPacket *packet, size_t& position);
            virtual bool readFrom(ENetPacket *packet, size_t& position);

        protected:
            GameLevel* mLevel = NULL;

            bool mIsDead = false;
            friend class boost::serialization::access;

            template<class Archive>
            void save(Archive & ar, const unsigned int version) const
            {
                UNUSED_PARAM(version);

                ar & this->mPos;
                ar & this->mFrame;
                ar & this->mAnimState;
                ar & this->mDestination;
            }

            template<class Archive>
            void load(Archive & ar, const unsigned int version)
            {
                UNUSED_PARAM(version);

                ar & this->mPos;
                ar & this->mFrame;
                ar & this->mAnimState;
                ar & this->mDestination;
            }

            bool canIAttack(Actor * actor);

            BOOST_SERIALIZATION_SPLIT_MEMBER()
            AnimState::AnimState mAnimState;
            bool mIsEnemy;
    };
}

#endif
