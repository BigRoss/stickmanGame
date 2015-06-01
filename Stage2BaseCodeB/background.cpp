#include "background.h"
#include "QDebug"

Background::Background()
{

}

Background::~Background()
{
    for(unsigned int i = 0; i < background_items.size(); i++)
    {
        delete background_items[i];
    }
}

/*
 * Adds a background item to be rendered, ie clouds, hills and etc
 *  @param item, DrawableInterface Item will be added to the list of background items
 */
void Background::add_background_item(Drawable* item)
{
    background_items.push_back(item);
}

/*
 * Attaches its background items to the graphics scene
 * @param scene, QGraphicsScene* object must be passed
 */
void Background::attach_to_scene(QGraphicsScene* scene)
{

    if(scene->backgroundBrush() != color)
        scene->setBackgroundBrush(color);
    for(unsigned int i = 0; i < background_items.size(); i++)
    {
        background_items[i]->attach_to_scene(scene);

    }
}

/*
 * Sets the background colour,
 * @param color, color that the background will be set to
 * @param scene, QGraphics scene object
 */
void Background::set_background_color(QColor color)
{
    this->color = color;
}

/*
 * Returns the background color
 */
QColor Background::get_background_color()
{
    return color;
}

//Reset positions of background objects:
void Background::reset_position(){
    for(unsigned int i = 0; i < background_items.size(); i++)
    {
        background_items[i]->reset_position();
    }
}

//Draws the background:
void Background::draw(QGraphicsScene* scene)
{
    for(unsigned int i = 0; i < background_items.size(); i++)
    {
        background_items[i]->draw(scene);
    }
}

void Background::set_movement_speed(int speed){
    for(unsigned int i = 0; i < background_items.size(); i++)
    {
        background_items[i]->set_movement_speed(speed);
    }
}

//Added if you want to be able to change what happens to the background based on some boolean input:
void Background::draw(QGraphicsScene *scene, bool setting) {}


