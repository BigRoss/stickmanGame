#include "Obstacle.h"
#include <QDebug>


/*
 * Initialises and constructs a Obstacle object
 */
Obstacle::Obstacle(int width, int height, int xposition, int yposition, int resolution_width, float movement_speed, QColor color) :
    PositionInterface(xposition, yposition),
    resolution_width(resolution_width),
    speed(movement_speed),
    color(color),
    x_start(xposition),
    obWidth(width)
{
    item = new QGraphicsRectItem(0, 0, width, height);
    item->setBrush(QBrush(QColor(color)));
    obstacle = item;
    obstacle->setX(xposition);
    obstacle->setY(yposition);
    obstacle->setZValue(22);
}

//Destructor for Obstacle object
Obstacle::~Obstacle()
{
    delete obstacle;
}

//Get the width of the obstacle
int Obstacle::get_width(){
    return obWidth;
}

/*
 * Sets the movement speed of the Obstacle (+ left, - right)
 */
void Obstacle::set_movement_speed(int speed)
{
    this->speed = speed;
}

/*
 * Attaches the drawable object to the scene graph
 */
void Obstacle::attach_to_scene(QGraphicsScene* scene)
{
    scene->addItem(obstacle);
}

/*
 * Renders the objects in the scene
 */
void Obstacle::draw(QGraphicsScene *scene)
{
    //Only draw the obstacle if it has been set to visible
    if(obstacle->isVisible()){
        int x = obstacle->x() - speed;
        obstacle->setX(x);
    }
}


//Added if you want to be able to toggle some setting for Obstacles (for extensibility)
void Obstacle::draw(QGraphicsScene *scene, bool setting) {}

/*
 * Sets the z depth
 */
void Obstacle::set_z(int z)
{
    obstacle->setZValue(z);
}

//Sets the xposition:
void Obstacle::set_x(int x)
{
    obstacle->setX(x);
}

//Sets the yposition:
void Obstacle::set_y(int y)
{
    qDebug() << y + obstacle->boundingRect().height();
    obstacle->setY(y);
}

//If the obstacle goes out of bounds, return true:
bool Obstacle::out_of_bounds() {
    if (-(obstacle->x()) > obstacle->boundingRect().width() + resolution_width/2) {
        return true;
    }
    else {
        return false;
    }
}

//Reset the obstacle to it's original position:
void Obstacle::reset_position() {
    obstacle->setX(x_start);
}

//returns a pointer to the QGraphicsItem
QGraphicsItem* Obstacle::get_obstacle() {
    return obstacle;
}
