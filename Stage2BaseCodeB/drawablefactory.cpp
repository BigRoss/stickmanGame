#include "drawablefactory.h"


DrawableFactory::DrawableFactory()
{

}

DrawableFactory::~DrawableFactory()
{

}

//Make a background asset:
Drawable* DrawableFactory::make_background_asset(DrawableAssetType type,
                                                 int width,
                                                 int height,
                                                 int length,
                                                 int xposition,
                                                 int yposition,
                                                 int resolution_width,
                                                 float movement_speed,
                                                 QColor color)
{
    if(CLOUD == type)
    {
        return new Cloud(width, height, length, xposition, yposition, resolution_width, movement_speed);
    }
    else if(HILLS == type)
    {
        return new Hills(width, height, length, xposition, yposition, resolution_width, movement_speed);
    }
    if (OBSTACLE == type)
    {
        return new Obstacle(width, height, xposition, yposition, resolution_width, movement_speed, color);
    }
    else
    {
        return nullptr;
    }
}

//Make an obstacle asset (currently only takes OBSTACLE but could extend):
Obstacle* DrawableFactory::make_obstacle_asset(DrawableAssetType type,
                                               int width,
                                               int height,
                                               int length,
                                               int xposition,
                                               int yposition,
                                               int resolution_width,
                                               float movement_speed,
                                               QColor color)
{
    if (OBSTACLE == type)
    {
        return new Obstacle(width, height, xposition, yposition, resolution_width, movement_speed, color);
    }
    else
    {
        return nullptr;
    }
}


//Make background:
Background* DrawableFactory::make_background()
{
    return new Background();
}

