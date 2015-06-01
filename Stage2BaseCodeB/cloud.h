#ifndef CLOUD_H
#define CLOUD_H

#include <vector>
#include "drawable.h"
#include "positioninterface.h"

class Cloud : public Drawable, public PositionInterface
{
public:
    Cloud(int width, int height, int length, int xposition, int yposition, int resolution_width, float movement_speed = 0);
    ~Cloud();

    void attach_to_scene(QGraphicsScene* scene);
    void draw(QGraphicsScene *scene);
    void draw(QGraphicsScene *scene, bool setting);
    void set_movement_speed(int speed);
    void set_z(int z);
    void reset_position();

private:
    std::vector<QGraphicsItem*> cloud_bumps;
    QGraphicsEllipseItem* item;
    int resolution_width;
    float speed;
    int x_start;
};


#endif // CLOUD_H
