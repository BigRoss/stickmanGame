#include "gamedialog.h"
#include "hills.h"
#include "configurablescene.h"
#include "ui_gamedialog.h"
#include "config.h"

#include <QPolygon>
#include <QAbstractScrollArea>
#include <QDebug>
#include <exception>
#include <stdlib.h>

int GameDialog::OFFSCREEN_WIDTH_OFFSET = 300;

//Constructor for GameDialog Class:
GameDialog::GameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameDialog),
    res_width(400),
    res_height(300),
    speed(0),
    counter(0),
    game_running(false),
    game_jump(false),
    stick_move(false),
    s_collision(true),
    activate_powerUp(false),
    move_direction(1),
    stage_num(0),
    winLose(false),
    stage2(false),
    stage3(false),
    checkpoint(false)
{
    scene = new ConfigurableScene(this, this);
    timer = new QTimer(this);

    this->setFixedWidth(res_width);
    this->setFixedHeight(res_height);
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(-OFFSCREEN_WIDTH_OFFSET, 0, res_width+OFFSCREEN_WIDTH_OFFSET, res_height);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    set_resolution(res_width, res_height);
    timer->start(32);
}

//Set the speed of stickman/hills etc
void GameDialog::set_speed(int moveSpeed){
    speed = moveSpeed;
}

//Set the stage3 boolean to true
void GameDialog::set_stage3(){
    stage3 = true;
}

//Set the stage2 boolean to true
void GameDialog::set_stage2(){
    stage2 = true;
}

//Return the stage2 and 3 set variables
bool GameDialog::check_stage2(){
    return stage2;
}

bool GameDialog::check_stage3(){
    return stage3;
}

//Destructor for GameDialog class:
GameDialog::~GameDialog()
{
    if(stage3){
        delete scoreItem;
        delete livesItem;
        delete endItem;
        delete enemy;
        delete powerUp;
    }
    scene->clear();
    delete ui;
    delete timer;
}

//Set the resolution given input:
void GameDialog::set_resolution(int width, int height)
{
    this->setFixedSize(width, height);
    ui->graphicsView->setFixedSize(width, height);
    scene->setSceneRect(-OFFSCREEN_WIDTH_OFFSET, 0, width+OFFSCREEN_WIDTH_OFFSET, height);
    res_width = width;
    res_height = height;
}

//Set the scene's background:
void GameDialog::set_scene_background(const QBrush& brush)
{
    scene->setBackgroundBrush(brush);
}

//Add a Drawable item to the drawableList:
void GameDialog::add_drawable(Drawable* drawable)
{
    drawableList.push_back(drawable);
}

//Add a stage to the obstacleList
void GameDialog::add_stage(std::vector<Obstacle*> stage){
    obstacleList.push_back(stage);
}

//Add the stickman
void GameDialog::add_stickman(StickmanProxy* man) {
    stickman = man;
}

//Add a power up:
void GameDialog::add_power_up(PowerUp* powerUp){
    this->powerUp = powerUp;
}

//Add an enemy
void GameDialog::add_enemy(Enemy *enemy){
    this->enemy = enemy;
}

//update to the next frame:
void GameDialog::nextFrame() {
    update();
}

//Attach the iface to the scene:
void GameDialog::attach_to_scene(Drawable* iface)
{
    iface->attach_to_scene(scene);
}

bool GameDialog::isRunning(){
    return game_running;
}

//Paint the objects to the screen:
void GameDialog::paintEvent(QPaintEvent *event)
{
    if(stage3){
        //Draw the score and stickman lives
        draw_score();

        //Check the win or lose conditions to end the game
        check_win_lose();
    }

    //Only play if player hasn't won/lost
    if(!winLose){

        //Only check obstacles if in stage 2 or 3
        if(stage2 || stage3){
            unsigned long num_out_of_bounds = 0;
            for(unsigned int i = 0; i < obstacleList[stage_num].size(); i++){
                //Check if the obstacles go out of bounds
                if (obstacleList[stage_num][i]->out_of_bounds()) {
                    num_out_of_bounds += 1;
                }
                //Also increase num_out_of_bounds if the stickman touches the checkpoint
                if(checkpoint){
                    num_out_of_bounds++;
                }
            }

            //If all obstacles in stage are done set all of the obstacles to not be drawn, then change to next stage
            if (num_out_of_bounds >= obstacleList[stage_num].size()) {
                if(stage3){
                    qDebug() << "Finished Stage";
                    //Set obstacles in current stage to be invisible and load the next stage
                    for(unsigned int i = 0; i < obstacleList[stage_num].size(); i++){
                        (obstacleList[stage_num][i]->get_obstacle())->setVisible(false);
                    }
                    stage_num++; //Increment stage number
                    //Reset the enemy
                    enemy->reset_position();

                    //Set the inStage variable of the obstacles in the next stage to true to show the obstacles
                    for(unsigned int i = 0; i < obstacleList[stage_num].size(); i++){
                        (obstacleList[stage_num][i]->get_obstacle())->setVisible(true);
                    }
                    //Stop the next stage from moving, it will move once the user presses something
                    for(unsigned int i = 0; i < drawableList.size(); i++){
                        drawableList[i]->set_movement_speed(0);
                    }
                    checkpoint = false;
                }
                else{
                    //For stage 2 functionality just reset the obstacles once the stage is finished
                    for(unsigned int i = 0; i < obstacleList[0].size(); i++){
                        obstacleList[0][i]->reset_position();
                    }
                }
            }
        }


        //Draw the game as per usual:
        if(game_running)
        {
            bool pan_camera = false;
            //Move the stickman if the user issued a move command:
            if(stick_move && stage3){
                stickman->move();
                //Only move the sickman on the screen if it is inside the panning distance,
                //If it is beyond the camera panning distance don't move the stickman, only move bg
                stickman->set_movement_speed(move_direction * speed);
                if(stickman->check_camera(res_width)){
                    stickman->set_movement_speed(0);
                    pan_camera = true;
                }
            }
            if(stage3){
                //Check powerup stuff
                check_powerUp();

                //Check for enemy collision
                enemy->check_spawn();
                if(enemyCollision()){
                    qDebug() << "Hit enemy";
                }
                int origSpeed = enemy->get_speed();
                if(pan_camera){
                    //Make it so that the enemy doesn't look like it's speeding up relative to the bg when
                    //we are panning the camera
                    enemy->set_movement_speed(enemy->get_speed() - move_direction * speed);
                }

                //Give the enemy the correct stage for collision and draw it
                enemy->get_stage(obstacleList[stage_num]);
                enemy->draw(scene);
                enemy->set_movement_speed(origSpeed);
            }

            if (!isCollision()){ //If no collision draw all items:
                for(unsigned long i = 0; i < drawableList.size(); i++)
                {
                    //Move the background when the stickman moves
                    if(stick_move && i != 0){
                        drawableList[i]->set_movement_speed(0);
                        if(pan_camera){
                            //only move bg and obstacles if the stickman has hit the boundaries of his movement
                            drawableList[i]->set_movement_speed(move_direction * speed);
                        }
                    }
                    if (game_jump && i == 0) {
                        drawableList[i]->draw(scene, game_jump);
                        toggle_jump();
                    } else {
                        drawableList[i]->draw(scene);
                    }
                    if(stage3){
                        drawableList[i]->set_movement_speed(0);
                    }
                }
                //Set stick_move to false so stickman doesn't continue moving
                stick_move = false;
            }
            else { //If collision only draw the stickman:
                if (game_jump) {
                    drawableList[0]->draw(scene, game_jump);
                    toggle_jump();
                }
                else {
                    drawableList[0]->draw(scene);
                }
            }

            //Increment the counter to keep track of score
            counter++;
        }
    }
    else{
        //If the player has won or lost make objects and stickman invisible but continue drawing the background
        for(unsigned int i = 0; i < obstacleList[stage_num].size(); i++){
            (obstacleList[stage_num][i]->get_obstacle())->setVisible(false);
        }
        //Set the stickman far behind so it can't be seen and set visibility of other obejcts to invisible
        stickman->set_y(-500);
        powerUp->get_power_up()->setVisible(false);
        enemy->get_enemy()->setVisible(false);
        scoreItem->setVisible(false);
        livesItem->setVisible(false);
        for(unsigned int i = 1; i < drawableList.size(); i++){
            drawableList[i]->set_movement_speed(10);
            drawableList[i]->draw(scene);
        }
    }
}


//Check if there's a collision between the stickman and any object in the obstacleList:
bool GameDialog::isCollision() {
    //Only check for collision if it is stage2 or 3
    if(stage2 || stage3){
        //Checks for collision with obstacles on the current stage
        for(unsigned long i = 0; i < obstacleList[stage_num].size(); i++) {
            QGraphicsItem* obs = obstacleList[stage_num][i]->get_obstacle();
            if(stage3){
                //Check for checkpoints in stage 3 mode
                if((i == obstacleList[stage_num].size() - 1)){
                    //If collision with checkpoint (last obstacle in a stage)
                    if(stickman->collidesWithCheckpoint(obs)){
                        stickman->add_lives(1);
                        counter += 150; //Add 200 to the counter at the end of each stage
                        checkpoint = true;
                        return true;
                    }
                }
                else if (stickman->collidesWithItem(obs)) {
                    //Reset the stage and decrement stickman lives
                    reset_position();
                    counter -= 150; //-150 points from the score if we lose a life from an obstacle
                    stickman->add_lives(-1);
                    return true;
                }
            }
            else if(stage2){
                //If we are in stage2 then we just do simple collision and return true
                if(stickman->collidesWithItem(obs)){
                    return true;
                }
            }
        }
        return false;
    }
    else{
        return false;
    }

}

//Check for a powerUp collision and store it in the stickman
bool GameDialog::powerUpCollision(){
    if(!powerUp->get_spawn()){
        //If there is no powerUp spawned return false
        return false;
    }
    if(stickman->collidesWithPowerUp(powerUp->get_power_up())){
        //Collision with a powerUp
        stickman->set_power_up(powerUp->get_type());
        powerUp->set_spawn(); //Turn the spawn off so the power up dissapears
        return true;
    }
    return false;
}

//Check for a collision with an enemy
bool GameDialog::enemyCollision(){
    if(stickman->collidesWithEnemy(enemy->get_enemy())){
        //Reset everything and decrement stickman lives
        reset_position();
        counter -= 100; //-100 points from the score if we lose a life
        stickman->add_lives(-1);
        return true;
    }
    return false;
}

//Reset the positions of all the drawables and obstacles on the stage for when the stickman dies
void GameDialog::reset_position(){
    qDebug() << "Reset Position";

    for(unsigned int i = 0; i < drawableList.size(); i++){
        drawableList[i]->reset_position();
    }

    //Also must reset the enemy
    if(stage3){
        enemy->reset_position();
    }

    stickman->remove_from_scene(scene); //Must remove, edit stickman and reattach to scene when resetting size
    stickman->reset_size();
    this->attach_to_scene(stickman);

    //Reset position of all obstacles in the current stage
    for(unsigned int i = 0; i < obstacleList[stage_num].size(); i++){
        obstacleList[stage_num][i]->reset_position();
    }
}

//Check if the user has won/lost and display appropriate message and stop the game
void GameDialog::check_win_lose(){

    int lastStageNum = obstacleList.size() - 1;
    int sizeLastStage = obstacleList[lastStageNum].size() - 1;

    //Check if we have lost the game
    if(stickman->get_lives() <= 0){
        winLose = true;
        std::string lose = "You Lose!!";
        endItem->setPlainText(QString::fromStdString(lose));
    }
    //If the user touches the last checkpoint of the last stage
    else if(stickman->collidesWithItem(obstacleList[lastStageNum][sizeLastStage]->get_obstacle())){
        winLose = true;
        std::string win = "You Win!!";
        endItem->setPlainText(QString::fromStdString(win));
    }
}

void GameDialog::set_text(){
    //Add in the text items to the GraphicsScene
    scoreItem = new QGraphicsTextItem("Score:    ");
    scoreItem->setPos(0, 0);
    scoreItem->setZValue(150);
    livesItem = new QGraphicsTextItem("Lives:    ");
    livesItem->setPos(0, 20);
    livesItem->setZValue(150);
    QFont serifFont("Times", 20, QFont::Bold);
    endItem = new QGraphicsTextItem(" ");
    endItem->setFont(serifFont);
    endItem->setPos(0,res_height / 2 - endItem->boundingRect().height());
    endItem->setZValue(150);
    scene->addItem(scoreItem);
    scene->addItem(livesItem);
    scene->addItem(endItem);
}

//Draw the score of the stickman and the stickman lives left
void GameDialog::draw_score(){
    std::stringstream ss;
    ss << "Score: " << counter;
    scoreItem->setPlainText(QString::fromStdString(ss.str()));
    //Clear the stringstream and put the lives on it
    ss.str(std::string());
    ss << "Lives: " << stickman->get_lives();
    livesItem->setPlainText(QString::fromStdString(ss.str()));
}

//Check all the power up related things including the powerup timer, collision and power up spawning
void GameDialog::check_powerUp(){
    //Decrement timer for the powerup and reset size of stickman if the timer is done:
    if(stickman->update_power()){
        stickman->remove_from_scene(scene); //Remove the stickman from the scene to update it
        stickman->reset_size();
        this->attach_to_scene(stickman); //Reattach stickman to the scene
    }

    //If we activated a power up then change the stickman
    if(activate_powerUp){
        stickman->remove_from_scene(scene);
        stickman->use_power_up(stickman->get_xPos(), stickman->get_yPos());
        this->attach_to_scene(stickman);
        toggle_powerUp();
    }

    powerUpCollision(); //Check for collision with a power up

    if(!powerUp->get_spawn()){
        //If there is currently no power up on the board, check if we can spawn one
        powerUp->check_spawn();
    }

    powerUp->draw(scene);
}

//Toggle the use of a power up:
void GameDialog::toggle_powerUp(){
    activate_powerUp = !activate_powerUp;
}

//Toggle depending on whether the stickman moved horizontally, direction = -1 for Left, 1 for right
void GameDialog::toggle_move(int direction){
    move_direction = direction;
    stick_move = !stick_move;
}

//Set the game to pause/unpause:
void GameDialog::toggle_pause()
{
    game_running = !game_running;
}

//Make the stickman jump
void GameDialog::toggle_jump()
{
    game_jump = !game_jump;
}

//Toggle collisions on and off:
void GameDialog::toggle_collision()
{
    s_collision = !s_collision;
    stickman->set_collision(s_collision);
}
