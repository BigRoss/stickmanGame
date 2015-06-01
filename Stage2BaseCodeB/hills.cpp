#include "hills.h"
#include <QDebug>

//Constructor for Hills Obstacle:
Hills::Hills(int width, int height, int length, int xposition, int yposition, int resolution_width, float movement_speed) :
    PositionInterface(xposition, yposition),
    resolution_width(resolution_width*2),
    speed(movement_speed),
    hill_width(width)
{
    unsigned int hills_count = length/width;
    int current_x = 0;
    for(unsigned long i = 0; i < hills_count; i++)
    {
        QPolygonF triangle;
        QGraphicsPolygonItem* item = nullptr;
        triangle.append(QPointF(-width ,0));
        triangle.append(QPointF(0,-width));
        triangle.append(QPointF(width, 0));
        triangle.append(QPointF(-width,0));
        item = new QGraphicsPolygonItem(triangle);
        item->setBrush(Qt::green);
        item->setY(this->ypos-2);
        item->setX(current_x);
        current_x += width;
        hills.push_back(item);
    }
}

//Destructor for Hills Obstacle:
Hills::~Hills()
{
    for(unsigned int i = 0; i < hills.size(); i++)
    {
        delete hills[i];
    }
    hills.clear();
}

//Set the Hills Object's movement speed:
void Hills::set_movement_speed(int speed)
{
    this->speed = speed;
}

//Attach the Hills Object to the given scene (referenced in gamedialog):
void Hills::attach_to_scene(QGraphicsScene* scene)
{
    for(unsigned int i = 0; i < hills.size(); i++)
    {
        hills[i]->setZValue((i%2)+7);
        scene->addItem(hills[i]);
    }
}

//Reset position for of the hills, used when restarting on stickman death:
void Hills::reset_position(){
    int current_x = 0;
    for(unsigned int i = 0; i < hills.size(); i++){
        hills[i]->setX(current_x);
        current_x += hill_width;
    }
}

//Draw the Hills Object:
void Hills::draw(QGraphicsScene* scene)
{
    //Eliminate the N operation or reduce the size at least
    for(unsigned int i = 0; i < hills.size(); i++)
    {//fixed an error here
        hills[i]->setX((((int) hills[i]->x()-(resolution_width/2))%resolution_width - speed)+ (resolution_width/2) );
    }
}

//Dummy function at the moment, use for extensibility:
void Hills::draw(QGraphicsScene* scene, bool setting) {}

//Set the z value:
void Hills::set_z(int z)
{
    for(unsigned int i = 0; i < hills.size(); i++)
    {
        hills[i]->setZValue(z+(i%2));
    }
}
