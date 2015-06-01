#include "enemy.h"
#include <cstdlib>
#include <QDebug>
#include <ctime>

Enemy::Enemy(int start_y, int resWidth, int resHeight) : start_y(start_y), resWidth(resWidth), resHeight(resHeight),
    jump_velocity(6), spawn(false), onTop(false)
{

    //fox art from http://opengameart.org/content/kit-the-firefox-mascot

    //Load up all of the images as we will to alternate between them for animation
    QImage image1("img/jump1.png");
    enemy1 = new QGraphicsPixmapItem(QPixmap::fromImage(image1));
    QImage image2("img/jump2.png");
    enemy2 = new QGraphicsPixmapItem(QPixmap::fromImage(image2));
    QImage image3("img/jump3.png");
    enemy3 = new QGraphicsPixmapItem(QPixmap::fromImage(image3));

    this->start_y = start_y  - enemy1->boundingRect().height() / 2;
    //Enemy will start outside of the screen to the left and on the same y position as the stickman
    this->set_x(-resWidth / 2);
    this->set_y(this->start_y);
    enemy1->setZValue(100);
    enemy1->setVisible(false);

    enemy2->setZValue(100);
    enemy2->setVisible(false);

    enemy3->setZValue(100);
    enemy3->setVisible(false);

    current_enemy = enemy1;
}

void Enemy::draw(QGraphicsScene* scene){
    if(spawn && current_enemy->isVisible()){
        //Reset the onTop variable once we hit the ground
        if(current_enemy->y() == start_y){
            onTop = false;
        }
        //Animate the stickman, use different images for different jump velocites
        if(jump_velocity <= 0 || onTop){
            //If on top of an obstacle use this image
            current_enemy->setVisible(false);
            current_enemy = enemy3;
            current_enemy->setVisible(true);
        }
        else if(jump_velocity > 1 && jump_velocity <= 5){
            current_enemy->setVisible(false);
            current_enemy = enemy2;
            current_enemy->setVisible(true);
        }
        else{
            current_enemy->setVisible(false);
            current_enemy = enemy1;
            current_enemy->setVisible(true);
        }

        //Move stickman horizontally, if the stickman goes out of bounds reset it
        this->set_x(current_enemy->x() + speed);
        if(current_enemy->x() + speed >= resWidth / 2){
            reset_position();
        }

        //Make the enemy jump
        if(current_enemy->y() <= start_y) {
            this->set_y(current_enemy->y() - jump_velocity);
            jump_velocity -= 9.8 * 1 / 32;
        }
        else {
            jump_velocity = 6;
            this->set_y(start_y);
        }
        //Make sure to check collision with obstacles, to walk on them or jump below them
        collisionWithItem();
    }
    else{
        //If the spawn variable is false don't show the enemy
        current_enemy->setVisible(false);
    }
}

//Check collision with obstacles
bool Enemy::collisionWithItem(){
    int bottom_y = current_enemy->y() + current_enemy->boundingRect().height();
    int right_x = current_enemy->x() + current_enemy->boundingRect().width();

    //Loop through all of the obstacles in the satge to check for collisions
    for(unsigned int i = 0; i < obstacleList.size(); i++){
        QGraphicsItem* object = obstacleList[i]->get_obstacle();
        if(current_enemy->collidesWithItem(object) && object->isVisible()){

            //Case when enemy lands on top of the obstacle:
            if((object->y() <= bottom_y) && (current_enemy->y() <= object->y())
                    && (object->x() < right_x) && (jump_velocity <= 0))
            {
                onTop = true;
                this->set_y(object->y() - (current_enemy->boundingRect().height()));
                jump_velocity = 0;
            }
            //Case when enemy hits its head on the obstacle:
            else if (object->y() + object->boundingRect().height() <= bottom_y
                     && current_enemy->y() <= object->y() + object->boundingRect().height()
                     && object->x() < right_x && jump_velocity >= 0) {
                onTop = false;
                this->set_y(object->y() + object->boundingRect().height() + 1);
                jump_velocity = 0;
            }
            else{
                //Otherwise if it's a normal collision reset the position of the enemy
                reset_position();
            }
        }
    }
}

void Enemy::draw(QGraphicsScene* scene, bool setting){

}

//Attach the images to the scene, only one will be visible at a time though
void Enemy::attach_to_scene(QGraphicsScene* scene){
    scene->addItem(enemy1);
    scene->addItem(enemy2);
    scene->addItem(enemy3);
}

//Check if we can spawn an enemy using a random number generator
void Enemy::check_spawn(){
    std::srand(std::time(0));
    int randVar = std::rand() % 20;
    //If we get the spawn and there is no current enemy that is visible, spawn a new enemy
    if(randVar <= 3 && !current_enemy->isVisible()){
        spawn = true;
        //Everytime we spawn a new enemy reset the x/y positions
        this->set_x(-resWidth / 2);
        this->set_y(this->start_y);
        current_enemy->setVisible(true);
    }
}

//Get the stage from the dialog
void Enemy::get_stage(std::vector<Obstacle*> obstacleList){
    this->obstacleList = obstacleList;
}

//Return the spawn variable
bool Enemy::get_spawn(){
    return spawn;
}

int Enemy::get_speed(){
    return speed;
}

//Reset the spawn and position of the enemy:
void Enemy::reset_position(){
    onTop = false;
    spawn = false;
    this->set_x(-resWidth / 2);
    this->set_y(start_y);
}

void Enemy::set_y(int y){
    enemy1->setY(y);
    enemy2->setY(y);
    enemy3->setY(y);
}

void Enemy::set_x(int x){
    enemy1->setX(x);
    enemy2->setX(x);
    enemy3->setX(x);
}

//Set the movespeed
void Enemy::set_movement_speed(int speed){
    this->speed = speed;
}

//Return the QGraphicsPixmapItem of the current enemy
QGraphicsPixmapItem* Enemy::get_enemy(){
    return current_enemy;
}


Enemy::~Enemy()
{
    delete enemy1;
    delete enemy2;
    delete enemy3;
}

