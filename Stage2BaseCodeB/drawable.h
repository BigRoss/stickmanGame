#ifndef DRAWABLEINTERFACE_H
#define DRAWABLEINTERFACE_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>

class Drawable
{
public:
    virtual ~Drawable() = 0;
    virtual void draw(QGraphicsScene* scene) = 0;
    virtual void draw(QGraphicsScene* scene, bool setting) = 0;
    virtual void attach_to_scene(QGraphicsScene* scene) = 0;
    virtual void reset_position() = 0;
    virtual void set_movement_speed(int speed) = 0;

};

#endif // DRAWABLEINTERFACE_H
