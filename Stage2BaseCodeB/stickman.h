#ifndef STICKMAN_H
#define STICKMAN_H

#include <iostream>
#include "drawable.h"
#include "positioninterface.h"

class StickmanState; //Forward declare StickmanState so we can put a pointer to it in Stickman

class Stickman : public Drawable, public PositionInterface
{
public:
    Stickman(std::string size_string);
    ~Stickman();

    //Horizontal starting position:
    virtual void set_start_x(int x);
    virtual int get_start_x();

    //Vertical starting position:
    virtual void set_start_y(int y);
    virtual int get_start_y();

    //Positional information:
    virtual int get_top_y();
    virtual int get_bottom_y();
    virtual int get_left_x();
    virtual int get_right_x();
    virtual int get_height();
    virtual int get_width();
    virtual int get_speed();
    virtual int get_xPos();
    virtual int get_yPos();
    virtual float get_gravity();
    virtual float get_start_jump_velocity();
    virtual float& get_jump_velocity();

    //Properties of stickman:
    virtual void set_size(std::string size);
    virtual void set_start_size(std::string size);
    virtual void add_lives(int add);
    virtual int get_lives();
    virtual float get_sizeMult();
    virtual void set_z(int z);
    virtual void set_lives(int lives);
    virtual void set_movement_speed(int speed);
    virtual void construct(bool freeVar, int start);

    //Get the parts of the stickman:
    virtual QGraphicsItem* get_head();
    virtual QGraphicsItem* get_body();
    virtual QGraphicsItem* get_left_leg();
    virtual QGraphicsItem* get_right_leg();
    virtual QGraphicsItem* get_left_arm();
    virtual QGraphicsItem* get_right_arm();

    //Drawing functions of stickman:
    virtual void attach_to_scene(QGraphicsScene* scene);
    virtual void remove_from_scene(QGraphicsScene* scene);
    virtual void draw(QGraphicsScene *scene);
    virtual void draw(QGraphicsScene *scene, bool game_jump);

    //Set movement properties of stickman:
    virtual void reset_position();
    virtual void set_x(int x);
    virtual void set_y(int y);
    virtual void set_collision(bool setting);
    virtual void set_gravity(float given_gravity);
    virtual void set_vertical_velocity(float vertical_velocity);
    virtual bool check_camera(int res_width);

    //Move stickman left/right:
    virtual void move();

    //Check if stickman collides:
    virtual bool collidesWithItem(QGraphicsItem* object);
    virtual bool collidesWithPowerUp(QGraphicsEllipseItem* powerUp);
    virtual bool collidesWithCheckpoint(QGraphicsItem* object);
    virtual bool collidesWithEnemy(QGraphicsPixmapItem* enemy);
    virtual bool get_collision();

    //PowerUp methods:
    virtual bool update_power();
    virtual void change_state();
    virtual int get_power_up();
    virtual void set_power_up(int type);
    virtual void use_power_up(int x, int y);
    virtual void reset_size();
private:

    StickmanState* current_state;

    QGraphicsItem* head;
    QGraphicsItem* body;
    QGraphicsItem* left_arm;
    QGraphicsItem* right_arm;
    QGraphicsItem* left_lower_leg;
    QGraphicsItem* right_lower_leg;

    int x_start;
    int y_start;
    int lives;
    int powerType;
    int move_direction;
    float velocity;
    float left_speed;
    float right_speed;
    float size_multiplier;

    float gravity;
    float start_jump_velocity;
    float jump_velocity;

    bool jump;
    bool stick_move;
    bool collision;
    int start_size;
};

//Stickman State behavioural design pattern, classes here to reduce high number of extra .h files:
class StickmanState
{
public:
    StickmanState();

    virtual ~StickmanState();

    //Change the stickman size depending on which state the stickman is in
    virtual void changeSize(int x, int y) = 0;

    //Decrement the powerup duration
    virtual void update_power() = 0;

    //Check for collision, giant stickman will not colllide with anything and will destroy obstacles
    virtual bool collidesWithItem(QGraphicsItem* object) = 0;

    //Check for collision with enemy, the 'power' stickman will kill the enemy
    virtual bool collidesWithEnemy(QGraphicsPixmapItem *enemy) = 0;

    //Each stickman will have a different movespeed, tiny will be the fastest
    virtual int set_movement_speed(int velocity) = 0;

    //Get the remaining power up time
    virtual int get_timer() = 0;
//    virtual void use_power() = 0; //Use the stickman power!
};

class StickmanStateNormal : public StickmanState
{
public:
    StickmanStateNormal(Stickman* stickman);
    virtual void changeSize(int x, int y);
    virtual void update_power();
    virtual bool collidesWithItem(QGraphicsItem* object);
    virtual bool collidesWithEnemy(QGraphicsPixmapItem *enemy);
    virtual int set_movement_speed(int velocity);
    virtual int get_timer();
    ~StickmanStateNormal();
private:
    Stickman* m_stickman;
    int m_timer;
};

class StickmanStateLarge : public StickmanState
{
public:
    StickmanStateLarge(Stickman* stickman);
    virtual void changeSize(int x, int y);
    virtual void update_power();
    virtual bool collidesWithItem(QGraphicsItem* object);
    virtual bool collidesWithEnemy(QGraphicsPixmapItem *enemy);
    virtual int set_movement_speed(int velocity);
    virtual int get_timer();
    ~StickmanStateLarge();
private:
    Stickman* m_stickman;
    int m_timer;
};

class StickmanStateGiant : public StickmanState
{
public:
    StickmanStateGiant(Stickman* stickman);
    virtual void changeSize(int x, int y);
    virtual void update_power();
    virtual bool collidesWithItem(QGraphicsItem* object);
    virtual bool collidesWithEnemy(QGraphicsPixmapItem *enemy);
    virtual int set_movement_speed(int velocity);
    virtual int get_timer();
    ~StickmanStateGiant();
private:
    Stickman* m_stickman;
    int m_timer;
};

class StickmanStateTiny : public StickmanState
{
public:
    StickmanStateTiny(Stickman* stickman);
    virtual void changeSize(int x, int y);
    virtual void update_power();
    virtual bool collidesWithItem(QGraphicsItem* object);
    virtual bool collidesWithEnemy(QGraphicsPixmapItem *enemy);
    virtual int set_movement_speed(int velocity);
    virtual int get_timer();
    ~StickmanStateTiny();
private:
    Stickman* m_stickman;
    int m_timer;
};

class StickmanStatePower : public StickmanState
{
public:
    StickmanStatePower(Stickman* stickman);
    virtual void changeSize(int x, int y);
    virtual void update_power();
    virtual bool collidesWithItem(QGraphicsItem* object);
    virtual bool collidesWithEnemy(QGraphicsPixmapItem *enemy);
    virtual int set_movement_speed(int velocity);
    virtual int get_timer();
    ~StickmanStatePower();
private:
    Stickman* m_stickman;
    int m_timer;
};


#endif // STICKMAN_H
