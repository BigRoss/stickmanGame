#include "powerup.h"
#include <cstdlib>
#include <QDebug>
#include <ctime>

PowerUp::PowerUp(int resWidth, int resHeight) : resolution_width(resWidth), resolution_height(resHeight), spawn(false),
    dx(10), dy(10), type(0), collision(false)
{
    std::srand(std::time(0)); // use current time as seed for random generator

    powerUp = new QGraphicsEllipseItem(0, 0, 20, 20);
    randomize_pos();
    randomize_type();

    //Powerups must be seen at all times, set z-value appropriately
    powerUp->setZValue(100);
}

PowerUp::~PowerUp()
{
    delete powerUp;
}

//Randomize the position of the powerup
void PowerUp::randomize_pos(){
    //Spawn the powerup's at a random place on the screen
    //-20 from res_height as we don't want to spawn powerup half off of the window
    int xpos = (std::rand() % resolution_width) - (resolution_width / 2);
    int ypos = std::rand() % (resolution_height - 20);
    powerUp->setPos(xpos, ypos);
}

//Get a number from 1-3 to determine the type of power Up
void PowerUp::randomize_type(){
    //Choose what colour based on what power up it is:
    int randVar = std::rand();
    randVar = randVar % 12;
    if(randVar == 0){
        //White: Type 0 Power guy
        powerUp->setBrush(QBrush(QColor(255, 255, 255, 255)));
        type = 0;
    }
    else if(randVar <= 4){
        //Red: Type 1 Giant
        powerUp->setBrush(QBrush(QColor(255, 0, 0, 255)));
        type = 1;
    }
    else if(randVar <= 8){
        //Green: Type 2 Large
        powerUp->setBrush(QBrush(QColor(0, 255, 0, 255)));
        type = 2;
    }
    else{
        //Blue: Type 3 Tiny
        powerUp->setBrush(QBrush(QColor(0, 0, 255, 255)));
        type = 3;
    }
}

void PowerUp::draw(QGraphicsScene* scene){

    //If we can spawn a power up:
    if(spawn){
        //Make it visible
        powerUp->setVisible(true);

        //Check if beyond any boundaries:
        if( powerUp->x() - powerUp->boundingRect().width() <= -(resolution_width / 2) + powerUp->boundingRect().width() && dx < 0){
            dx = -dx;
        }
        if(powerUp->x() - powerUp->boundingRect().width() >= resolution_width / 2 && dx > 0){
            dx = -dx;
        }
        if( (powerUp->y() + powerUp->boundingRect().height() >= resolution_height && dy > 0) || (powerUp->y() <= 0 && dy < 0)){
            dy = -dy;
        }
        //Change x,y coordinates
        powerUp->setX(powerUp->x() + dx);
        powerUp->setY(powerUp->y() + dy);

    }
    else{
        powerUp->setVisible(false);
    }
}

void PowerUp::check_spawn(){
    std::srand(std::time(0)); // use current time as seed for random generator
    int randVar = std::rand() % 20;
    if(randVar <= 2){
        spawn = true;
    }
}

void PowerUp::set_spawn(){
    spawn = !spawn;
    if(!spawn){
        //If the spawn has been set to false then randomize new values for the next powerUp
        randomize_pos();
        randomize_type();
    }
}

bool PowerUp::get_spawn(){
    return spawn;
}

void PowerUp::draw(QGraphicsScene* scene, bool setting){
}

void PowerUp::attach_to_scene(QGraphicsScene* scene){
    scene->addItem(powerUp);
}

void PowerUp::reset_position(){
    spawn = false;
}

//Leave this function empty, there is only one movespeed for the powerup set in the constructor
void PowerUp::set_movement_speed(int moveSpeed){
}

int PowerUp::get_type(){
    return type;
}

QGraphicsEllipseItem* PowerUp::get_power_up(){
    return powerUp;
}
