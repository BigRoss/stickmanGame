#include "stickman.h"

StickmanStateLarge::StickmanStateLarge(Stickman* stickman) : m_stickman(stickman), m_timer(100)
{

}

void StickmanStateLarge::changeSize(int x, int y){
    m_stickman->set_size("large");
    m_stickman->construct(true, x);
    m_stickman->set_y(y);
    m_stickman->set_x(x);
}

bool StickmanStateLarge::collidesWithItem(QGraphicsItem *object){
    QGraphicsItem* head = m_stickman->get_head();
    QGraphicsItem* body = m_stickman->get_body();
    QGraphicsItem* left_arm = m_stickman->get_left_arm();
    QGraphicsItem* right_arm = m_stickman->get_right_arm();
    QGraphicsItem* left_lower_leg = m_stickman->get_left_leg();
    QGraphicsItem* right_lower_leg = m_stickman->get_right_leg();
    float& jump_velocity = m_stickman->get_jump_velocity();
    bool collision = m_stickman->get_collision();
    //Collision with obstacles turned on:
    if (collision && object->isVisible()) {
        object->setOpacity(1.0); //Set all objects to have 100% opacity
        //Case when collision:
        if (head->collidesWithItem(object) || body->collidesWithItem(object) || left_arm->collidesWithItem(object)
                || right_arm->collidesWithItem(object) || left_lower_leg->collidesWithItem(object) || right_lower_leg->collidesWithItem(object))
        {
            //Case when you land on top of the obstacle:
            if((object->y() - 10 <= m_stickman->get_bottom_y()) && (m_stickman->get_top_y() <= object->y())
                    && (object->x() < m_stickman->get_right_x()) && (jump_velocity <= 0))
            {
                m_stickman->set_y(object->y() - (m_stickman->get_height()));
                jump_velocity = 0;
                return false;
            }
            //Case when you hit your head on the obstacle:
            else if (object->y() + object->boundingRect().height() <= m_stickman->get_bottom_y()
                     && m_stickman->get_top_y() <= object->y() + object->boundingRect().height()
                     && object->x() < m_stickman->get_right_x() && jump_velocity >= 0) {
                if(body->collidesWithItem(object) || left_arm->collidesWithItem(object) || right_arm->collidesWithItem(object)){
                    //Can still collide in some cases, especially when stickman is giant so double check
                    return true;
                }
                m_stickman->set_y(object->y() + object->boundingRect().height() + 1);
                jump_velocity = 0;
                return false;
            }
            else if(jump_velocity >= 0 && m_stickman->get_bottom_y() <= m_stickman->get_start_y()){
                if(head->collidesWithItem(object) || body->collidesWithItem(object) || left_arm->collidesWithItem(object)
                        || right_arm->collidesWithItem(object)){
                    return true;
                }
                //this takes care of a small bug which detected a collision whenever the stickman
                //jumped off an obstacle.
                return false;
            }
            else {
                return true;
            }
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

bool StickmanStateLarge::collidesWithEnemy(QGraphicsPixmapItem *enemy){
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

//Large stickman will just have a normal velocity
int StickmanStateLarge::set_movement_speed(int velocity){
    return velocity ;
}

void StickmanStateLarge::update_power(){
    m_timer--;
}

int StickmanStateLarge::get_timer(){
    return m_timer;
}

StickmanStateLarge::~StickmanStateLarge()
{

}

