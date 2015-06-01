#ifndef POWERUP_H
#define POWERUP_H

#include "drawable.h"
#include <QGraphicsEllipseItem>

class PowerUp : public Drawable
{
public:
    PowerUp(int resWidth, int resHeight);
    ~PowerUp();
    void draw(QGraphicsScene* scene);
    void draw(QGraphicsScene* scene, bool setting);
    void attach_to_scene(QGraphicsScene* scene);
    void reset_position();
    void set_movement_speed(int speed);
    void check_spawn();
    void randomize_pos();
    void randomize_type();
    int get_type();
    void set_spawn();
    bool get_spawn();
    QGraphicsEllipseItem* get_power_up();

private:
    QGraphicsEllipseItem* powerUp;
    int resolution_width;
    int resolution_height;
    int spawn;
    int dx;
    int dy;
    int type;
    bool collision;
};

#endif // POWERUP_H
