#ifndef CONFIGURABLESCENE_H
#define CONFIGURABLESCENE_H

#include "gamedialog.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QKeyEvent>

class ConfigurableScene : public QGraphicsScene
{
public:
    ConfigurableScene(QObject *parent = 0, GameDialog* dialogPtr = 0);

    void keyPressEvent(QKeyEvent *event);
private:
    GameDialog* gameDialog;
};

#endif // CONFIGURABLESCENE_H
