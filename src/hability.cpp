#include "gameobject.hpp"
#include "components/image.hpp"
#include "log.h"
#include "vector.hpp"
#include "hability.hpp"
#include "gameglobals.hpp"
#include "game.hpp"

using namespace engine;

bool Hability::init()
{
    engine::GameObject::init(); 
    setState(State::disabled);
    return true;
}

bool Hability::shutdown()
{
    engine::GameObject::shutdown();
    return true;
}

bool Hability::draw()
{
    engine::GameObject::draw();
    return true;
}

bool Hability::update()
{
	if(!durationTimer.getTime()< duration){   
		//quita do scene
		INFO("Finish spell");
		setState(State::disabled);
	}
    return true;
}

bool Hability::addHability(std::string hability_name, Hability * hability)
{
	habilities[hability_name] = hability;
	return true;
}

bool Hability::useHabilityQ(){
	INFO("Using hability Q from " << name());

    auto objects = Game::instance.m_scene->m_objects;
    for (auto id_obj: objects)
    {
        auto obj = id_obj.second;
        if ((dynamic_cast<Enemy*>(obj)) && dynamic_cast<Enemy*>(obj)->life > 0) {
            
            player->physics.collisionBox.x = player->physics.position.getX();
            player->physics.collisionBox.y = player->physics.position.getY();
            player->physics.collisionBox.w = player->w;
            player->physics.collisionBox.h = player->h;

            obj->physics.collisionBox.x = obj->physics.position.getX();
            obj->physics.collisionBox.y = obj->physics.position.getY();
            obj->physics.collisionBox.w = obj->w;
            obj->physics.collisionBox.h = obj->h;
            if(player->physics.detectColision(obj))
            {
                obj->physics.velocity.setX(100);
                dynamic_cast<Enemy*>(obj)->life-=20;
                //m_game_object->setState(GameObject::State::disabled);
            }
        }
    }

	return true;
}

bool Hability::useHabilityW(){
	useHability();
	INFO("Using hability W from " << name());
	return true;
}

bool Hability::useHabilityE(){
	useHability();
	INFO("Using hability E from " << name());
	return true;
}

bool Hability::useHability()
{
    INFO("Start spell");
    //AudioComponent * audio = get_component<AudioComponent>();
    //audio->play(1);
    setState(State::enabled);
    physics.position = player->physics.position;
    physics.velocity = player->physics.velocity;
  	durationTimer.startTimer();
    countdownTimer.startTimer();
    //timer2.startTimer();
  return true;
}