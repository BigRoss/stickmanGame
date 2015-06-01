#include "ConfigurableScene.h"
#include <iostream>

ConfigurableScene::ConfigurableScene(QObject *parent, GameDialog *dialogPtr)
    : QGraphicsScene(parent), gameDialog(dialogPtr)
{
}

void ConfigurableScene::keyPressEvent(QKeyEvent *event)
{
    if(gameDialog->check_stage2()){
        if(event->key() == Qt::Key_P)
        {
            qDebug() << "Game is paused";
            gameDialog->toggle_pause();
        }
        //Jump functionality
        if(event->key() == Qt::Key_Space)
        {
            qDebug() << "Player has jumped";
            gameDialog->toggle_jump();
            if (!gameDialog->isRunning()) {
                qDebug() << "Broken out of pause";
                gameDialog->toggle_pause();
            }
        }
        //God mode: Collision toggle
        if (event->key() == Qt::Key_C)
        {
            gameDialog->toggle_collision();
            qDebug() << "Collision toggled";
        }
        //Stage 3 functions
        if(gameDialog->check_stage3()){
            //If the stickman moves:
            if (event->key() == Qt::Key_Left)
            {
                gameDialog->toggle_move(-1);
            }

            if (event->key() == Qt::Key_Right)
            {
                gameDialog->toggle_move(1);
            }

            //Activate the held powerUp
            if(event->key() == Qt::Key_Z){
                gameDialog->toggle_powerUp();
            }
        }
    }
}
