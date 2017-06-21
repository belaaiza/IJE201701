#include "game.hpp"
#include "gameobject.hpp"
#include "scene.hpp"
#include "components/image.hpp"
#include "components/text.hpp"
#include "components/audio.hpp"
#include "components/animation.hpp"
#include "components/moveDirectionals.hpp"
#include "components/moveSS.hpp"
#include "components/animationcontroller.hpp"
#include "components/customimagecomponent.hpp"
#include "player.hpp"
#include "gamescene.hpp"
#include "menuscene.hpp"
#include "gameover.hpp"
#include "hability.hpp"
#include "hudlife_enemy.hpp"
#include "tilemap.hpp"
#include "tileset.hpp"
#include "log.h"
#include "gameglobals.hpp"
#include "hudlife.hpp"
#include "hudinstrument.hpp"
#include "enemy.hpp"
#include <cstdio>

using namespace std;
using namespace engine;

int main(int, char**)
{
    // Configure game
    Game::instance.set_properties(globals::game_name, globals::window_size);

    // Setup scenes
    MenuScene menu("Menu");
    MenuScene GameoverScene("Gameover");
    MenuScene VictoryScene("Victory");
    GameScene room1("stage_1_room_1");
    
    /* Gamescene*/
    Game::instance.add_scene(menu);
    Game::instance.add_scene(room1);
    Game::instance.add_scene(GameoverScene);
    Game::instance.add_scene(VictoryScene);

    Player player(globals::player,0,globals::window_size.second/2);
    player.xF = 0; player.yF = 0;

    MoveDirectionals move(player);

    //Declaring instruments
    Hability hability1("spellQBanjo",&player,0,0,3000,3000);
    Hability hability2("spellWBanjo",&player,0,0,5000,5000);
    Hability hability3("spellEBanjo",&player,0,0,5000,1000);
   
    player.addHability(globals::banjo, &hability1);
    player.addHability(globals::eletric_guitar, &hability2);
    player.addHability(globals::accordion, &hability3);

    ImageComponent banjoImage(player, "girl2.png", 4, 4, true);
    ImageComponent eletricGuitarImage(player, "girl3.png", 4, 4, true);
    ImageComponent accordionImage(player, "girl4.png", 4, 4, true);

    /*int count = 0;
    vector<Enemy*> enemies;
    vector<ImageComponent*> images;
    char aux[10];
    int x = 600;
    int y = 100;
    for(int i=0; i<3; i++){
        for(int j=4; j>=0; j--){
            string name = "enemy";
            sprintf(aux, "%d", count);
            name+=aux;

            Enemy enemy(name, x, y, &player);
            enemies.push_back(&enemy);
            enemies[count]->xF=0; enemies[count]->yF=0;

            ImageComponent enemyImage(*enemies[count], "ghost.png", 4, 4, true);
            images.push_back(&enemyImage);
            enemies[count]->add_component(*images[count]);

            room1.add_game_object(*enemies[count]);

            count++;

            y+=100;
        }

        y=100;
        x+=100;
    }*/

    Enemy enemy("enemy", 600, 250, &player, 100);
    enemy.xF = 0; enemy.yF = 0;
    ImageComponent enemyImage(enemy, "ghost.png", 4, 4, true);
    enemy.add_component(enemyImage);

    Enemy enemy1("enemy1", 670, 100, &player, 100);
    enemy1.xF = 0; enemy1.yF = 0;
    ImageComponent enemyImage1(enemy1, "ghost1.png", 4, 4, true);
    enemy1.add_component(enemyImage1);

    Enemy enemy2("enemy2", 670, 400, &player, 100);
    enemy2.xF = 0; enemy2.yF = 0;
    ImageComponent enemyImage2(enemy2, "ghost2.png", 4, 4, true);
    enemy2.add_component(enemyImage2);

    Enemy enemy3("enemy3", 720, 300, &player, 100);
    enemy3.xF = 0; enemy3.yF = 0;
    ImageComponent enemyImage3(enemy3, "ghost3.png", 4, 4, true);
    enemy3.add_component(enemyImage3);

    Enemy boss("enemy4", 900, 250, &player, 200);
    boss.xF = 0; boss.yF = 0;
    ImageComponent bossImage(boss, "boss.png", 4, 2, true);
    boss.add_component(bossImage);

    HUDInstrument HUDInstrument("hudinstrument", globals::window_size.first-250, globals::window_size.second-120, &player);
    HUDInstrument.xF = 0; HUDInstrument.yF = 0;
    ImageComponent banjoActiveHUD(HUDInstrument, "hud_instruments_0.png", 1, 1);
    ImageComponent eletricGuitarActiveHUD(HUDInstrument, "hud_instruments_1.png", 1, 1);
    ImageComponent accordionActiveHUD(HUDInstrument, "hud_instruments_2.png", 1, 1);

    HUDInstrument.addHUD(globals::banjo, &banjoActiveHUD);
    HUDInstrument.addHUD(globals::eletric_guitar, &eletricGuitarActiveHUD);
    HUDInstrument.addHUD(globals::accordion, &accordionActiveHUD);

    HUDInstrument.add_component(banjoActiveHUD);
    HUDInstrument.add_component(eletricGuitarActiveHUD);
    HUDInstrument.add_component(accordionActiveHUD);

    player.addSprite(globals::banjo, &banjoImage);
    player.addSprite(globals::eletric_guitar, &eletricGuitarImage);
    player.addSprite(globals::accordion, &accordionImage);

    player.add_component(banjoImage);
    player.add_component(eletricGuitarImage);
    player.add_component(accordionImage);

    player.add_component(move);


    //add to scene
    room1.add_game_object(hability1);
    room1.add_game_object(hability2);
    room1.add_game_object(hability3);
    room1.add_game_object(enemy);
    room1.add_game_object(enemy1);
    room1.add_game_object(enemy2);
    room1.add_game_object(enemy3);
    room1.add_game_object(boss);
    room1.add_game_object(player);

    GameObject playbutton("playbutton",(globals::window_size.first/2)-50,(globals::window_size.second/2)-50);
    ImageComponent playImage(playbutton,"playbutton.png",1,1);
    playbutton.xF = 0; playbutton.yF = 0;
    playbutton.add_component(playImage);
    menu.add_game_object(playbutton);

    GameObject gameover("gameover",(globals::window_size.first/2)-100,(globals::window_size.second/2)-100);
    ImageComponent gameoverImage(gameover,"gameover.png",1,1);
    gameover.xF = 0; gameover.yF = 0;
    gameover.add_component(gameoverImage);
    GameoverScene.add_game_object(gameover);

    GameObject victory("victory",(globals::window_size.first/2)-100,(globals::window_size.second/2)-100);
    ImageComponent victoryImage(victory,"victory.png",1,1);
    victory.xF = 0; victory.yF = 0;
    victory.add_component(victoryImage);
    VictoryScene.add_game_object(victory);

    Camera::getInstance()->setFocus(&player);

    TileMap tilemap("assets/mapa1.txt", "mapa", 0, 0, Camera::getInstance());
    TileSet tileset(32, 32, tilemap, "tilesheet.png", 1, 1);
    tilemap.setTileSet(tileset);
    tilemap.add_component(tileset);

    HUDLife hudlife("hudlife", 0, 0, &player);
    hudlife.xF = 0; hudlife.yF = 0;
    ImageComponent lifeBar(hudlife, "hud_life.png", 1, 1);
    CustomImageComponent lifeBarContent(hudlife, "hud_life_full.png", 1, 1);
    hudlife.setLifeBar(&lifeBar);
    hudlife.setLifeBarContent(&lifeBarContent);
    hudlife.add_component(lifeBar);
    hudlife.add_component(lifeBarContent); 

    AudioComponent music(tilemap,"fase.mp3",true, true);
    tilemap.add_component(music);

    room1.add_game_object(tilemap); 
    room1.add_game_object(hudlife);
    //room1.add_game_object(HUDInstrument);

    // Game loop
    Game::instance.run();
    return 0;
}
