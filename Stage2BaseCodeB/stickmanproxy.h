#ifndef STICKMANPROXY_H
#define STICKMANPROXY_H
#include "positioninterface.h"
#include "drawable.h"
#include "stickman.h"


class StickmanProxy : public Drawable, public PositionInterface
{
public:
    StickmanProxy(std::string size_string);
    ~StickmanProxy();
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
    virtual int get_lives();
    virtual int get_xPos();
    virtual int get_yPos();

    //Properties of stickman:
    virtual void set_size(std::string size);
    virtual void set_start_size(std::string size);
    virtual void set_z(int z);
    virtual void set_movement_speed(int speed);
    virtual void set_lives(int lives);
    virtual void add_lives(int add);
    virtual float get_sizeMult();
    virtual void construct(bool freeVar, int start);

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

    //Move the stickman
    virtual void move();

    //Check if stickman collides:
    virtual bool collidesWithItem(QGraphicsItem* object);
    virtual bool collidesWithPowerUp(QGraphicsEllipseItem* powerUp);
    virtual bool collidesWithCheckpoint(QGraphicsItem* object);
    virtual bool collidesWithEnemy(QGraphicsPixmapItem* enemy);

    //Power up methods:
    virtual bool update_power();
    virtual int get_power_up();
    virtual void use_power_up(int x, int y);
    virtual void set_power_up(int type);
    virtual void reset_size();

    //Method to check whether to pan the screen or not:
    virtual bool check_camera(int res_width);

    //Set resolution width/height;
    void set_resolution_width(int width);
    void set_resolution_height(int height);

    //Get resolution width/height:
    int get_resolution_width();
    int get_resolution_height();

private:
    Stickman m_stickman;
    int resolution_width;
    int resolution_height;
};

#endif // STICKMANPROXY_H
