#include "components/image.hpp"

#include "game.hpp"
#include "log.h"
#include "sdl_log.h"
#include "camera.hpp"

using namespace engine;

bool ImageComponent::init()
{
    INFO("Init ImageComponent");

    if (m_path == "")
    {
        WARN("Invalid path for image!");
        return false;
    }
    auto image = Game::instance.asset_manager().load_image(m_path);
    m_texture = image->texture;
    m_game_object->set_size(image->w/i, image->h/j);
    INFO("PATH "<< m_path << "OBJECT "<<m_game_object->name());

    return true;
}

bool ImageComponent::shutdown()
{
    INFO("Shutdown ImageComponent");

    m_texture = NULL;

    return true;
}

void ImageComponent::draw()
{
    int x = m_game_object->physics.position.getX();
    int y = m_game_object->physics.position.getY();
    if(m_follows_camera){
        x+=Camera::getInstance()->getX();
        y+=Camera::getInstance()->getY();
    }

    SDL_Rect renderQuad = {
        x,
        y,
        m_game_object->w,
        m_game_object->h
    };
    SDL_Rect frameQuad = {
        m_game_object->xF,
        m_game_object->yF,
        m_game_object->w,
        m_game_object->h
    };

    SDL_RenderCopyEx(Game::instance.canvas(), m_texture, &frameQuad, &renderQuad, 0, 0, SDL_FLIP_NONE);
}

