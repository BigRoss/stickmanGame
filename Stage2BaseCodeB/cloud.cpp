#include "cloud.h"
#include <QDebug>


/*
 * Initialises and constructs a cloud object
 */
Cloud::Cloud(int width, int height, int length, int yposition, int xposition, int resolution_width, float movement_speed) :
    PositionInterface(xposition, yposition),
    resolution_width(resolution_width*2),
    speed(movement_speed),
    x_start(xposition)
{
    item = nullptr;
    int bumps = length/width;
    for(int i = 0; i < bumps; i++)
    {
        QGraphicsEllipseItem* item = new QGraphicsEllipseItem(0+(i*width/2), 50, width, height);
        item->setStartAngle(0);
        item->setX(xposition);
        item->setY(yposition);
        item->setZValue(-22);
        item->setSpanAngle(2880); //360*8
        item->setBrush(Qt::white);
        cloud_bumps.push_back(item);
    }
}

//Cloud destructor:
Cloud::~Cloud()
{
    for(unsigned int i = 0; i < cloud_bumps.size(); i++)
    {
        delete cloud_bumps[i];
    }
    cloud_bumps.clear();
}

/*
 * Sets the movement speed of the cloud (+ left, - right)
 */
void Cloud::set_movement_speed(int speed)
{
    this->speed = speed;
}

/*
 * Attaches the drawable object to the scene graph
 */
void Cloud::attach_to_scene(QGraphicsScene* scene)
{
    for(unsigned long i = 0; i < cloud_bumps.size(); i++)
    {
        scene->addItem(cloud_bumps[i]);
    }
}

/*
 * Resets position of the cloud to initial position
 */
void Cloud::reset_position(){
    for(unsigned int i = 0; i < cloud_bumps.size(); i++)
    {
        QGraphicsItem* item = cloud_bumps[i];
        item->setX(x_start);
    }
}

/*
 * Renders the objects in the scene, clouds will move regardless of whether stickman is moving
 */
void Cloud::draw(QGraphicsScene *scene)
{
    for(unsigned int i = 0; i < cloud_bumps.size(); i++)
    {
        QGraphicsItem* item = cloud_bumps[i];
        int x = (((int)(item->x()-(resolution_width/2))%resolution_width)-speed)+(resolution_width/2);
        item->setX(x);
    }
}

//Added if you want to be able to change what happens to clouds based on some boolean input
void Cloud::draw(QGraphicsScene *scene, bool setting) {}

/*
 * Sets the z depth
 */
void Cloud::set_z(int z)
{
    for(unsigned int i = 0; i < cloud_bumps.size(); i++)
    {
        cloud_bumps[i]->setZValue(z);
    }
}
