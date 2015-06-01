#ifndef ENEMY_H
#define ENEMY_H

#include "drawable.h"
#include "Obstacle.h"

class Enemy : public Drawable
{
public:
    Enemy(int start_y, int resWidth, int resHeight);
    virtual void draw(QGraphicsScene* scene);
    virtual void draw(QGraphicsScene* scene, bool setting);
    virtual void attach_to_scene(QGraphicsScene* scene);
    virtual void reset_position();
    virtual void set_y(int y);
    virtual void set_x(int x);
    virtual void set_movement_speed(int speed);
    virtual void check_spawn();
    virtual void get_stage(std::vector<Obstacle *> obstacleList);
    virtual bool get_spawn();
    virtual int get_speed();
    virtual QGraphicsPixmapItem* get_enemy();
    virtual bool collisionWithItem();
    ~Enemy();

private:
    QGraphicsPixmapItem* current_enemy;
    QGraphicsPixmapItem* enemy1;
    QGraphicsPixmapItem* enemy2;
    QGraphicsPixmapItem* enemy3;
    std::vector<Obstacle*> obstacleList;
    int start_y;
    int resWidth;
    int resHeight;
    int speed;
    float jump_velocity;
    bool spawn;
    bool onTop;
};

#endif // ENEMY_H
