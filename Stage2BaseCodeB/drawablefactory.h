#ifndef DRAWABLEFACTORY_H
#define DRAWABLEFACTORY_H

#include "drawable.h"
#include "cloud.h"
#include "hills.h"
#include "obstacle.h"
#include "background.h"
#include <iostream>
#include <QColor>

//typedef enum DrawableAssetType DrawableAssetType;
enum DrawableAssetType { CLOUD, HILLS, OBSTACLE };

class DrawableFactory
{
public:
    DrawableFactory();
    ~DrawableFactory();

    Drawable* make_background_asset(DrawableAssetType type,
                                    int width,
                                    int height,
                                    int length,
                                    int xposition,
                                    int yposition,
                                    int resolution_width,
                                    float movement_speed = 0,
                                    QColor color = "#FFFFFF");
    Obstacle* make_obstacle_asset(DrawableAssetType type,
                                  int width,
                                  int height,
                                  int length,
                                  int xposition,
                                  int yposition,
                                  int resolution_width,
                                  float movement_speed = 0,
                                  QColor color = "#FFFFFF");
    Background* make_background();
};

#endif // DRAWABLEFACTORY_H
