#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <vector>
#include "drawable.h"
#include "positioninterface.h"

class Obstacle : public Drawable, public PositionInterface
{
public:
    Obstacle(int width, int height, int xposition, int yposition, int resolution_width, float movement_speed = 0, QColor color = "#123456");
    ~Obstacle();

    void attach_to_scene(QGraphicsScene* scene);
    void draw(QGraphicsScene *scene);
    void draw(QGraphicsScene *scene, bool setting);
    void set_movement_speed(int speed);
    void set_z(int z);
    void set_x(int x);
    void set_y(int y);
    int get_width();
    bool out_of_bounds();
    void reset_position();
    QGraphicsItem* get_obstacle();

private:
    QGraphicsItem* obstacle;
    QGraphicsRectItem* item;
    int resolution_width;
    float speed;
    QColor color;
    int x_start;
    int obWidth;
};


#endif // OBSTACLE_H
