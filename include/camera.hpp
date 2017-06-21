#ifndef __CAMERA__
#define __CAMERA__

#include <string>
#include "gameobject.hpp"
#include "components/image.hpp"
#include "player.hpp"

using namespace engine;

class Camera {
public:
    Camera(GameObject *focus);

    ~Camera() {}

    bool update();
    int getX();
    int getY();
    static Camera* getInstance();
    void setFocus(GameObject* focus);
    
private:
	static Camera *instance;
	GameObject *m_focus;
	int cameraX;
	int cameraY;
};

#endif
