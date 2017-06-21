#ifndef __GAME_PLAYER_OBJECT__
#define __GAME_PLAYER_OBJECT__

#include <string>
#include <list>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include "vector.hpp"
#include "gameobject.hpp"
#include "components/image.hpp"
#include "hability.hpp"
#include "components/text.hpp"
#include "enemy.hpp"

using namespace engine;

class Hability;

class Player : public GameObject {
public:
    Player() : GameObject() {}
    Player(std::string _name,int _x,int _y)
        : GameObject(_name,_x,_y) {}

    ~Player() {}
    int life = 100;
    virtual bool init();
    virtual bool shutdown();
    virtual bool update();
    virtual bool draw();

    bool moveDown();
    bool moveUp();
    bool moveRight();
    bool moveLeft();
    bool changeHability(std::string hability_name);
    bool changeSprite(std::string sprite);
    bool handlePlayer();
    void addHability(std::string hability_name, Hability *Hability);
    void addSprite(std::string hability_name, ImageComponent *sprite);
    Hability* getActiveHability();
    
private:
    std::unordered_map<std::string, Hability*> habilities;
    std::unordered_map<std::string, ImageComponent*> sprites;
    Hability* active_hability;
    ImageComponent* active_sprite;
    int defaultVel = 5;
};

#endif
