#ifndef __GAME_ENEMY_OBJECT__
#define __GAME_ENEMY_OBJECT__

#include <string>
#include <list>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include "vector.hpp"
#include "gameobject.hpp"
#include "components/image.hpp"
#include "player.hpp"
#include "components/text.hpp"

using namespace engine;

class Player;

class Enemy : public GameObject {
public:
    Enemy() : GameObject() {}
    Enemy(std::string _name,int _x,int _y, Player * target)
        : GameObject(_name,_x,_y), m_target(target) {}

    ~Enemy() {}
    int life = 100;
    virtual bool init();
    virtual bool shutdown();
    virtual bool update();
    virtual bool draw();
    void causeDamage();

    //bool changeHability(std::string hability_name);
    //bool changeSprite(std::string sprite);
    //void addHability(std::string hability_name, Hability Hability);
    //void addSprite(std::string hability_name, ImageComponent* sprite);
    //Hability getActiveHability();
    
private:
    Player* m_target;
};

#endif
