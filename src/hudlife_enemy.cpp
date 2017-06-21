#include "gameobject.hpp"
#include "log.h"
#include "hudlife_enemy.hpp"

using namespace engine;

bool HUDLifeEnemy::init()
{
    engine::GameObject::init();
    return true;
}

bool HUDLifeEnemy::shutdown()
{
    engine::GameObject::shutdown();
    return true;
}

bool HUDLifeEnemy::draw()
{
    double new_width = ((w-110) * m_enemy->life) / 100.0;
    double new_heith = h*0.5;
    physics.position.setX(m_enemy->physics.position.getX() / 2);
    physics.position.setY(m_enemy->physics.position.getY() + 50);
    m_life_content->setWidth(new_width);
    m_life_content->setHeight(new_heith);
    m_life_content->setX(physics.position.getX()+55);
    m_life_content->setY(physics.position.getY()+10);
    engine::GameObject::draw();

    return true;
}

bool HUDLifeEnemy::update()
{
    engine::GameObject::update();
    return true;
}

void HUDLifeEnemy::setLifeBar(ImageComponent *life_bar){
    m_life_bar = life_bar;
}

void HUDLifeEnemy::setLifeBarContent(CustomImageComponent *life_content){
    m_life_content = life_content;
}