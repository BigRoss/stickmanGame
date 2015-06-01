#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <QColor>
#include <vector>
#include "drawable.h"


class Background : public Drawable
{
public:
    Background();
    ~Background();

    void add_background_item(Drawable* item);
    void attach_to_scene(QGraphicsScene* scene);
    void draw(QGraphicsScene *scene);
    void draw(QGraphicsScene *scene, bool setting);
    void reset_position();
    void set_movement_speed(int speed);

    void set_background_color(QColor color);
    QColor get_background_color();


private:
    std::vector<Drawable*> background_items;
    QColor color;
};

#endif // BACKGROUND_H
