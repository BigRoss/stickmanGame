#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include <QDialog>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QTimer>
#include <QString>
#include <QKeyEvent>
#include <sstream>
#include <vector>
#include "drawable.h"
#include "obstacle.h"
#include "stickman.h"
#include "powerup.h"
#include "enemy.h"
#include "stickmanproxy.h"

namespace Ui {
    class GameDialog;
}

class GameDialog : public QDialog
{
    Q_OBJECT

public:
    static int OFFSCREEN_WIDTH_OFFSET;
    explicit GameDialog(QWidget *parent = 0);
    ~GameDialog();
    void toggle_pause();
    void toggle_move(int direction);
    void toggle_jump(); //added to include jump function
    void toggle_collision(); //added to include godmode
    void toggle_powerUp();
    void check_powerUp();

    //Collision methods
    bool isCollision();
    bool powerUpCollision();
    bool enemyCollision();

    bool isRunning(); //added for configurableScene to see if game is running
    void reset_position();
    void check_win_lose();
    void draw_score(); //Onlydraw the score if we can move stickman (backwards compatability)
    void add_drawable(Drawable* drawable);
    void add_obstacle(Obstacle* obstacle);
    void add_stage(std::vector<Obstacle *> stage); //This is used when using multiple stages
    void add_stickman(StickmanProxy* man);
    void add_power_up(PowerUp* powerUp);
    void add_enemy(Enemy* enemy);
    void attach_to_scene(Drawable* iface);
    void set_resolution(int width, int height);
    void set_text();
    void set_scene_background(const QBrush& brush);
    void set_speed(int speed);
    void set_stage3();
    void set_stage2();
    bool check_stage2();
    bool check_stage3();

public slots:
    void nextFrame();

private:
    Ui::GameDialog *ui;
    QGraphicsScene* scene;
    QTimer* timer;
    QGraphicsTextItem* scoreItem;
    QGraphicsTextItem* livesItem;
    QGraphicsTextItem* endItem;
    std::vector<Drawable*> drawableList;
    std::vector< std::vector<Obstacle*> > obstacleList;
    PowerUp* powerUp;
    Enemy* enemy;
    StickmanProxy* stickman;
    int res_width;
    int res_height;
    int speed;
    int counter;
    bool game_running;
    bool game_jump;
    bool stick_move;
    bool s_collision;
    bool activate_powerUp;
    int move_direction;
    int stage_num;
    bool winLose;
    bool stage2;
    bool stage3;
    bool checkpoint;
    //int offscreen_width_offset;

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // GAMEDIALOG_H
