#ifndef HILLS_H
#define HILLS_H

#include <vector>
#include "drawable.h"
#include "positioninterface.h"

class Hills : public Drawable, public PositionInterface
{
public:
    Hills(int width, int height, int length, int xposition, int yposition, int resolution_width, float movement_speed = 0);
    ~Hills();

    void attach_to_scene(QGraphicsScene* scene);
    void draw(QGraphicsScene* scene);
    void draw(QGraphicsScene *scene, bool setting);
    void set_movement_speed(int speed);
    void set_z(int z);
    void reset_position();

private:
    std::vector<QGraphicsItem*> hills;
    int resolution_width;
    int speed;
    int hill_width;
};

#endif // HILLS_H
