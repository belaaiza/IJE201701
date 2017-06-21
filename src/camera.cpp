#include "camera.hpp"
#include "player.hpp"
#include "gameglobals.hpp"
#include "log.h"

using namespace engine;

Camera* Camera::instance;

Camera::Camera(GameObject *focus){
	m_focus = focus;
	cameraX = cameraY = 0;
}

bool Camera::update()
{
	cameraX= globals::window_size.first / 2 - m_focus->physics.position.getX();
	cameraY= globals::window_size.second / 2 - m_focus->physics.position.getY();

	if(cameraX > 0){
		cameraX = 0;
	}

	if(cameraY > 0){
		cameraY = 0;
	}

	if( cameraX < globals::window_size.first - globals::level_size.first)
	{
		cameraX = globals::window_size.first - globals::level_size.first;
	}

	if( cameraY < globals::window_size.second - globals::level_size.second)
	{
		cameraY = globals::window_size.second - globals::level_size.second;
	}
}

int Camera::getX(){
	return cameraX;
}

int Camera::getY(){
	return cameraY;
}

Camera* Camera::getInstance(){
	if(instance == nullptr){
		instance = new Camera(nullptr);
	}
	
	return instance;
}

void Camera::setFocus(GameObject *focus){
	m_focus = focus;
}