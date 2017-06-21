#ifndef __GAME_HUDLIFEENEMY_OBJECT__
#define __GAME_HUDLIFEENEMY_OBJECT__

#include <string>
#include "gameobject.hpp"
#include "components/image.hpp"
#include "components/customimagecomponent.hpp"
#include "enemy.hpp"

using namespace engine;

class HUDLifeEnemy : public GameObject {
public:
    HUDLifeEnemy() : GameObject() {}
    HUDLifeEnemy(std::string _name,int _x,int _y, Enemy *enemy)
        : GameObject(_name,_x,_y), m_enemy(enemy) {}

    ~HUDLifeEnemy() {}
   
    virtual bool init();
    virtual bool shutdown();
    virtual bool update();
    virtual bool draw();
    void setLifeBar(ImageComponent *life_bar);
    void setLifeBarContent(CustomImageComponent *life_content);

private:
    ImageComponent *m_life_bar;
    CustomImageComponent *m_life_content;
    Enemy *m_enemy;
};

#endif
