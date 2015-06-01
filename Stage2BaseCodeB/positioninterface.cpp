#include "positioninterface.h"

//PositionInterface constructor (given no values):
PositionInterface::PositionInterface() : xpos(0), ypos(0)
{

}

//PositionInterface constructor (given coordinates):
PositionInterface::PositionInterface(int x, int y) : xpos(x), ypos(y)
{

}

//PositionInterface destructor:
PositionInterface::~PositionInterface()
{
    //No OP
}

//Set the (x,y) position:
void PositionInterface::set_position(int x, int y)
{
    xpos = x;
    ypos = y;
}

//Set just the x-coordinate:
void PositionInterface::set_x(int x)
{
    this->xpos = x;
}

//Set just the y-coordinate:
void PositionInterface::set_y(int y)
{
    this->ypos = y;
}

//Get the x-coordinate:
int PositionInterface::get_x()
{
    return xpos;
}

//Get the y-coordinate:
int PositionInterface::get_y()
{
    return ypos;
}

//Get the z-value;
int PositionInterface::get_z()
{
    return z_value;
}
