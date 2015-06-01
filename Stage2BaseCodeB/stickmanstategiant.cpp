#include "stickman.h"

StickmanStateGiant::StickmanStateGiant(Stickman *stickman) : m_stickman(stickman), m_timer(100)
{

}

void StickmanStateGiant::changeSize(int x, int y){
    m_stickman->set_size("giant");
    m_stickman->construct(true, x);
    m_stickman->set_y(y);
    m_stickman->set_x(x);
}

//The giant stickman should destroy obstacles on impact
bool StickmanStateGiant::collidesWithItem(QGraphicsItem *object){
    QGraphicsItem* head = m_stickman->get_head();
    QGraphicsItem* body = m_stickman->get_body();
    QGraphicsItem* left_arm = m_stickman->get_left_arm();
    QGraphicsItem* right_arm = m_stickman->get_right_arm();
    QGraphicsItem* left_lower_leg = m_stickman->get_left_leg();
    QGraphicsItem* right_lower_leg = m_stickman->get_right_leg();
    bool collision = m_stickman->get_collision();

    //Collision with obstacles turned on:
    if (collision && object->isVisible()) {
        object->setOpacity(1.0); //Set all objects to have 100% opacity
        //Case when collision:
        if (head->collidesWithItem(object) || body->collidesWithItem(object) || left_arm->collidesWithItem(object)
                || right_arm->collidesWithItem(object) || left_lower_leg->collidesWithItem(object) || right_lower_leg->collidesWithItem(object))
        {
            object->setVisible(false); //Set the object to invisible, pretty much destroy the obstacle from the stage
            return false;
        }
        //Case when there's no collision:
        else {
            return false;
        }
    }
    //Collision with obstacles turned off:
    else {
        object->setOpacity(0.25); //Set all objects to have 25% opacity
        return false;
    }
}

bool StickmanStateGiant::collidesWithEnemy(QGraphicsPixmapItem *enemy){
    QGraphicsItem* head = m_stickman->get_head();
    QGraphicsItem* body = m_stickman->get_body();
    QGraphicsItem* left_arm = m_stickman->get_left_arm();
    QGraphicsItem* right_arm = m_stickman->get_right_arm();
    QGraphicsItem* left_lower_leg = m_stickman->get_left_leg();
    QGraphicsItem* right_lower_leg = m_stickman->get_right_leg();
    if (head->collidesWithItem(enemy) || body->collidesWithItem(enemy) || left_arm->collidesWithItem(enemy)
            || right_arm->collidesWithItem(enemy) || left_lower_leg->collidesWithItem(enemy) || right_lower_leg->collidesWithItem(enemy))
    {
        return true;
    }
    return false;
}

//Giant will be the slowest
int StickmanStateGiant::set_movement_speed(int velocity){
    return (velocity / 2) ;
}

void StickmanStateGiant::update_power(){
    m_timer--;
}

int StickmanStateGiant::get_timer(){
    return m_timer;
}

StickmanStateGiant::~StickmanStateGiant()
{

}

