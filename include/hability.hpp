#ifndef __GAME_HABILITY_OBJECT__
#define __GAME_HABILITY_OBJECT__

#include <string>
#include <list>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include "vector.hpp"
#include "gameobject.hpp"
#include "timer.hpp"
#include "components/audio.hpp"
#include "player.hpp"

using namespace engine;

class Hability : public GameObject {
public:
    Hability() : GameObject() {}
    Hability(std::string _name, GameObject * obj, int _x,int _y, int _countdown, int _duration)
        : GameObject(_name,_x,_y), player(obj),countdown(_countdown),duration(_duration){}

    ~Hability() {}

    virtual bool init();
    virtual bool shutdown();
    virtual bool update();
    virtual bool draw();
    bool addHability(std::string hability_name, Hability * hability);
    bool useHabilityQ();
    bool useHabilityW();
    bool useHabilityE();
    bool useHability();

private:
    std::unordered_map<std::string, Hability*> habilities;
    GameObject * player;
    Timer durationTimer;
    Timer countdownTimer;
    int countdown;
    int lastTimeUsed;
    int duration;
};

#endif