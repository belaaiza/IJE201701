#include "gameobject.hpp"
#include "player.hpp"
#include "components/text.hpp"
#include "components/image.hpp"
#include "log.h"
#include "vector.hpp"
#include "keyword.hpp"
#include "gameglobals.hpp"
#include <sstream>
#include "game.hpp"
#include "hability.hpp"

#define nframes 4

using namespace engine;

bool Player::init()
{
    engine::GameObject::init();

    for(auto hability : habilities){
        hability.second->init();
    }

    active_hability = habilities[globals::banjo];
    active_sprite = sprites[globals::banjo];

    sprites[globals::eletric_guitar]->setState(Component::State::disabled);
    sprites[globals::accordion]->setState(Component::State::disabled);

    //INFO("x"<<physics.collisionBox.x<<"  y"<<physics.collisionBox.y <<"  w"<<physics.collisionBox.w<< "    h"<< physics.collisionBox.h)
    return true;
}

bool Player::shutdown()
{
    engine::GameObject::shutdown();
    return true;
}

bool Player::draw()
{
    engine::GameObject::draw();
    return true;
}

bool Player::update()
{
    handlePlayer();

    GameObject::update();
    
    int collisionAdjust = 0;
    physics.collisionBox.x = physics.position.getX() + collisionAdjust;
    physics.collisionBox.y = physics.position.getY() + collisionAdjust;
    physics.collisionBox.w = w - collisionAdjust;
    physics.collisionBox.h = h - collisionAdjust;

    return true;
}
bool Player::moveDown(){
    // Update Velocity
    int componentX = 0;
    int componentY = defaultVel;

    Vector2D move(componentX,componentY);
    physics.velocity = move;

    if(physics.position.getY() + h >= globals::level_size.second)
    {
        physics.velocity.setY(0);
    }
    // Update Frame
    int xFrame = (((xF/w)+1)%nframes)*w;
    int yFrame = 0*h;

    xF = xFrame;
    yF = yFrame;
    return true;
}

bool Player::moveUp(){
    // Update Velocity
    int componentX = 0;
    int componentY = -1*defaultVel;

    Vector2D move(componentX,componentY);
    physics.velocity = move;

    if(physics.position.getY() < 0)
    {
        physics.velocity.setY(0);
    }
    // Update Frame
    int xFrame = (((xF/w)+1)%nframes)*w;
    int yFrame = 3*h;

    xF = xFrame;
    yF = yFrame;
    return true;
}

bool Player::moveLeft(){
    // Update Velocity
    int componentX = -1*defaultVel;

    int componentY = 0;

    Vector2D move(componentX,componentY);
    physics.velocity = move;

    if(physics.position.getX() < 0)
    {
        physics.velocity.setX(0);
    }
    // Update Frame
    int xFrame = (((xF/w)+1)%nframes)*w;
    int yFrame = 1*h;

    xF = xFrame;
    yF = yFrame;
//}
    return true;
}

bool Player::moveRight(){
    // Update Velocity

    int componentX = defaultVel;
    int componentY = 0;

    Vector2D move(componentX,componentY);
    physics.velocity = move;

    INFO("X = " << physics.position.getX() << " XMap = " << globals::level_size.first);

    if(physics.position.getX() + w >= globals::level_size.first)
    {
        //Move back
        physics.velocity.setX(0);
    }
    // Update Frame
    int xFrame = (((xF/w)+1)%nframes)*w;
    int yFrame = 2*h;

    xF = xFrame;
    yF = yFrame;
    return true;
}

bool Player::changeHability(std::string hability_name){
    INFO("Changing Hability to " << hability_name);
    Hability* hability = habilities[hability_name];
    bool isHabilityNull = true;

    active_hability = hability;
    changeSprite(hability_name);

    return isHabilityNull;
}

bool Player::changeSprite(std::string sprite_name){
    INFO("Changing Sprite to " << sprite_name);
    ImageComponent* sprite = sprites[sprite_name];
   
    active_sprite->setState(Component::State::disabled);
    sprite->setState(Component::State::enabled);
    active_sprite = sprite;

    return true;
}

bool Player::handlePlayer(){
    
    if(Input::keyPressed(Input::ONE))
    {
        changeHability(globals::banjo);
    }
    if(Input::keyPressed(Input::TWO))
    {
        changeHability(globals::eletric_guitar);
    }
    if(Input::keyPressed(Input::THREE))
    {
        changeHability(globals::accordion);
    }
    if(Input::keyPressed(Input::Q))
    {
        active_hability->useHabilityQ();
    }
    if(Input::keyPressed(Input::W))
    {
        active_hability->useHabilityW();
    }
    if(Input::keyPressed(Input::E))
    {
        active_hability->useHabilityE();
    }
    
    return true;
}

void Player::addHability(std::string hability_name, Hability *hability){
    habilities[hability_name] = hability;
}

void Player::addSprite(std::string hability_name, ImageComponent * sprite){
    sprites[hability_name] = sprite;
}

Hability * Player::getActiveHability(){
    return active_hability;
}