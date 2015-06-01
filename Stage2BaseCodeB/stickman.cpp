#include "stickman.h"
#include <QDebug>

//Stickman constructor (given a string):
Stickman::Stickman(std::string size_string) :
    PositionInterface(),
    x_start(0), //Added in to fix bug on lab machines
    y_start(300),
    lives(5), // Default 5 lives
    powerType(-1),
    velocity(0),
    gravity(9.8),
    jump_velocity(10),
    jump(false),
    stick_move(false),
    collision(true)
{
    //These variables only affect the rotation of body parts, set them to constants
    left_speed = 5;
    right_speed = 5;
    set_size(size_string);
    set_start_size(size_string);
    change_state();
//    construct(false, 0);
}

//Stickman Destructor:
Stickman::~Stickman()
{
    delete head;
    delete body;
    delete right_lower_leg;
    delete left_lower_leg;
    delete right_arm;
    delete left_arm;
    delete current_state;
}

//Set the horizontal velocity of the stickman (useful for Stage 3):
void Stickman::set_movement_speed(int velocity)
{
    this->velocity = current_state->set_movement_speed(velocity);
}

//Set whether collisions are enabled or disabled for the stickman:
void Stickman::set_collision(bool setting) {
    collision = setting;
}

//Construct the stickman at position start, have the boolean if we are reconstructing (for the powerups):
void Stickman::construct(bool freeVar, int start)
{
    if(freeVar){
        delete head;
        delete body;
        delete right_lower_leg;
        delete left_lower_leg;
        delete right_arm;
        delete left_arm;
    }
    head = new QGraphicsEllipseItem(0, 0, 5*size_multiplier, 5*size_multiplier);
    ((QGraphicsEllipseItem*)head)->setBrush(Qt::black);
    head->setX(start + 1);

    body = new QGraphicsRectItem(head->boundingRect().width()/2 - (size_multiplier*0.3), 0, 0.7*size_multiplier, 4*size_multiplier);
    ((QGraphicsRectItem*)body)->setBrush(Qt::black);
    body->setX(start +(head->boundingRect().width()/2)-(3*size_multiplier));
    right_lower_leg = new QGraphicsLineItem(0, 0, 0, 7*size_multiplier);
    right_lower_leg->setX(start + head->boundingRect().width()/2);
    right_lower_leg->setRotation(-25);

    left_lower_leg = new QGraphicsLineItem(0, 0, 0, 7*size_multiplier);
    left_lower_leg->setX(start + head->boundingRect().width()/2);
    left_lower_leg->setRotation(25);


    right_arm = new QGraphicsLineItem(0, 0, 0, 5*size_multiplier);
    right_arm->setX(start + head->boundingRect().width()/2);
    right_arm->setRotation(-25);

    left_arm = new QGraphicsLineItem(0, 0, 0, 5*size_multiplier);
    left_arm->setX(start + head->boundingRect().width()/2);
    left_arm->setRotation(25);

    head->setY(this->get_start_y()-(head->boundingRect().height() + body->boundingRect().height()
                    + right_lower_leg->boundingRect().height()));
    body->setY(head->y()+head->boundingRect().height());
    right_lower_leg->setY(body->y()+body->boundingRect().height());
    left_lower_leg->setY(body->y()+body->boundingRect().height());
    left_arm->setY(body->y());
    right_arm->setY(body->y());

    this->set_y(this->get_start_y()); //added in
}

//Set the x (horizontal) position of the stickman:
void Stickman::set_x(int x)
{
    this->xpos = x;
    //Updates the stickman position
    head->setX(x);
    body->setX(x +(head->boundingRect().width()/2)-(3*size_multiplier));
    right_arm->setX(x + head->boundingRect().width()/2);
    left_arm->setX(x + head->boundingRect().width()/2);
    left_lower_leg->setX(x + head->boundingRect().width()/2);
    right_lower_leg->setX(x + head->boundingRect().width()/2);
}

//Set the y (vertical) position of the stickman:
void Stickman::set_y(int y)
{
    this->ypos = y;
    //Update the stickman position
    head->setY(y);
    body->setY(head->y()+head->boundingRect().height());
    right_lower_leg->setY(body->y()+body->boundingRect().height());
    left_lower_leg->setY(body->y()+body->boundingRect().height());
    left_arm->setY(body->y());
    right_arm->setY(body->y());
}

//Set the amount of lives the stickman has:
void Stickman::set_lives(int numLives){
    if(numLives > 0){
        lives = numLives;
    }
    else{
        qDebug() << "Invalid stickman lives, default to 5 lives";
        lives = 5; //Default 5 lives
    }
}

//Change lives value
void Stickman::add_lives(int add){
    lives += add;
}

//Set the gravity at which the stickman obeys:
void Stickman::set_gravity(float given_gravity)
{
    gravity = given_gravity;
}

//Set the vertical velocity at which the stickman obeys:
void Stickman::set_vertical_velocity(float vertical_velocity) {
    start_jump_velocity = vertical_velocity;
    jump_velocity = vertical_velocity;
}

bool Stickman::check_camera(int res_width){
    if((xpos >= (x_start + 75) && velocity > 0) || (xpos <= (x_start - 75) && velocity < 0)){
        return true;
    }
    if(this->get_left_x() <= -(res_width / 2) || this->get_right_x() >= (res_width / 2)){
        //If the stickman goes out of the screen also pan the camera
        return true;
    }
    return false;
}

//Set the size of the stickman:
void Stickman::set_size(std::string size)
{
    if(size.compare("tiny") == 0)
    {
        this->size_multiplier = 1.0;
    }
    else if(size.compare("normal") == 0)
    {
        size_multiplier = 2.0;
    }
    else if(size.compare("large") == 0)
    {
        size_multiplier = 3.0;
    }
    else if(size.compare("giant") == 0)
    {
        size_multiplier = 4.0;
    }
}

//Set the starting size of the stickman, so we can revert back to it once power up finishes it's duration
void Stickman::set_start_size(std::string size){
    if(size.compare("tiny") == 0)
    {
        start_size = 3;
    }
    else if(size.compare("normal") == 0)
    {
        start_size = -1;
    }
    else if(size.compare("large") == 0)
    {
        start_size = 2;
    }
    else if(size.compare("giant") == 0)
    {
        start_size = 1;
    }
}

//Reset the stickman to the original position, used when restarting a level
void Stickman::reset_position(){
    this->set_x(this->get_start_x());
    this->set_y(this->get_start_y());
    this->jump_velocity = 0;
}

//Set the starting x (horizontal) position:
void Stickman::set_start_x(int x)
{
    x_start = x;
    this->set_x(x);
}

//Get amount of lives left on the stickman
int Stickman::get_lives(){
    return lives;
}

//Get the size multiplier value
float Stickman::get_sizeMult(){
    return size_multiplier;
}

//Get x position of the stickman
int Stickman::get_xPos(){
    return xpos;
}

//Get y position of stickman
int Stickman::get_yPos(){
    return ypos;
}

//Get powerUp value of the stickman
int Stickman::get_power_up(){
    return powerType;
}

//Set the power up that the stickman got:
void Stickman::set_power_up(int type){
    powerType = type;
}

void Stickman::use_power_up(int x, int y){
    //Only use a power up if we have one at the moment, and don't change the state if the default size == powerup size
    if(start_size != powerType){
        //Power up here if stickman is holding a power up
        change_state();
        current_state->changeSize(x, y); //Change the size depending on the state we're in
        powerType = start_size; //Revert the powerup back so that we can't power up again
    }
}

//Reset stickman size to it's original size in config file
void Stickman::reset_size(){
    this->set_power_up(start_size);
    change_state();
    current_state->changeSize(this->get_xPos(), this->get_yPos());
}

bool Stickman::update_power(){
    current_state->update_power();
    if(current_state->get_timer() <= 0){
        return true;
    }
    return false;
}

void Stickman::change_state(){
    //Clear memory of last state
    current_state = new StickmanStateNormal(this);
    delete current_state;
    //Change state of stickman, assign new state to current_state
    if(powerType == 0){
        current_state = new StickmanStatePower(this);
    }
    else if(powerType == 1){
        current_state = new StickmanStateGiant(this);
    }
    else if(powerType == 2){
        current_state = new StickmanStateLarge(this);
    }
    else if(powerType == 3){
        current_state = new StickmanStateTiny(this);
    }
    else{
        current_state = new StickmanStateNormal(this);
    }
}

//Get speed of stickman
int Stickman::get_speed(){
    return velocity;
}

//Get gravity
float Stickman::get_gravity(){
    return gravity;
}

//Get start jump velocity
float Stickman::get_start_jump_velocity(){
    return start_jump_velocity;
}

//Returns a reference to the jump velocity
float& Stickman::get_jump_velocity(){
    return jump_velocity;
}

//Get the starting x (horizontal) position:
int Stickman::get_start_x() {
    return x_start;
}

//Set the starting y (vertical) position:
void Stickman::set_start_y(int y)
{
    y_start = y;
    this->set_y(y);
}

//Get the starting y (vertical) position:
int Stickman::get_start_y()
{
    return y_start;
}

//Set the z-value of the Stickman (where it stacks on the scene with other objects)
void Stickman::set_z(int z)
{
    head->setZValue(z);
    body->setZValue(z);
    left_lower_leg->setZValue(z);
    right_lower_leg->setZValue(z);
    left_arm->setZValue(z);
    right_arm->setZValue(z);
    z_value = z;
}

//Attach the stickman to the given scene (referenced in gamedialog):
void Stickman::attach_to_scene(QGraphicsScene* scene)
{
    scene->addItem(head);
    scene->addItem(body);
    scene->addItem(left_lower_leg);
    scene->addItem(right_lower_leg);
    scene->addItem(left_arm);
    scene->addItem(right_arm);
    set_z(99);
}

void Stickman::remove_from_scene(QGraphicsScene* scene){
    scene->removeItem(head);
    scene->removeItem(body);
    scene->removeItem(left_lower_leg);
    scene->removeItem(right_lower_leg);
    scene->removeItem(left_arm);
    scene->removeItem(right_arm);
}

void Stickman::move(){
    stick_move = true;
}

//Draw the stickman:
void Stickman::draw(QGraphicsScene* scene)
{
        //If stickman moves horizontally, update horizontal position
        if(stick_move){
            set_x(xpos + velocity);
            stick_move = false;
        }

        //If the stickman jumps, update it's vertical position and velocity:
        if(jump && this->get_y() <= this->get_start_y()) {
            this->set_y(this->get_y() - jump_velocity);
            float jump_multiplier = size_multiplier;
            if(size_multiplier == 3){
                //If the stickman is large then make it jump higher than normal
                jump_multiplier = 1.5;
            }
            jump_velocity -= gravity * jump_multiplier / 32;
        }
        else {
            jump_velocity = start_jump_velocity;
            this->set_y(this->get_start_y());
            jump = false;
        }

        //Legacy code, update the rotation of the legs and arms:
        if((int)left_lower_leg->rotation()%-35 || left_lower_leg->rotation() == 0) {
            left_lower_leg->setRotation(left_lower_leg->rotation()-left_speed);
            left_arm->setRotation(left_arm->rotation()-left_speed);
        } else {
            left_speed *= -1;
            left_lower_leg->setRotation(left_lower_leg->rotation()-left_speed);
            left_arm->setRotation(left_arm->rotation()-left_speed);
        }

        if((int)right_lower_leg->rotation()%-35 || right_lower_leg->rotation() == 0) {
            right_lower_leg->setRotation(right_lower_leg->rotation()+right_speed);
            right_arm->setRotation(right_arm->rotation()+right_speed);
        } else {
            right_speed *= -1;
            right_lower_leg->setRotation(right_lower_leg->rotation()+right_speed);
            right_arm->setRotation(right_arm->rotation()+right_speed);
        }

}

//Used to draw the stickman when the jump key is pressed:
void Stickman::draw(QGraphicsScene* scene, bool dialog_jump)
{
        jump = true;
        this->draw(scene);
        jump_velocity = start_jump_velocity;
}

//Get the y-value of the top of the stickman (head):
int Stickman::get_top_y() {
    return this->ypos;
}

//Get the y-value of the bottom of the stickman (feet):
int Stickman::get_bottom_y() {
    return this->ypos + (body->boundingRect().height() + left_arm->boundingRect().height() + head->boundingRect().height());
}

//Get the x-value of the leftmost part of the stickman:
int Stickman::get_left_x() {
    return this->xpos;
}

//Get the y-value of the rightmost part of the stickman:
int Stickman::get_right_x() {
    return this->xpos + head->boundingRect().width();
}

//Get the height of the stickman:
int Stickman::get_height() {
    return this->get_bottom_y() - this->get_top_y();
}

//Get the width of the stickman:
int Stickman::get_width() {
    return this->get_right_x() - this->get_left_x();
}

//Check for collision between the stickman and a powerUp
bool Stickman::collidesWithPowerUp(QGraphicsEllipseItem *powerUp){
    if (head->collidesWithItem(powerUp) || body->collidesWithItem(powerUp) || left_arm->collidesWithItem(powerUp)
            || right_arm->collidesWithItem(powerUp) || left_lower_leg->collidesWithItem(powerUp) || right_lower_leg->collidesWithItem(powerUp)){
        return true;
    }
    return false;
}

//Check for collision between the stickman and some QGraphicsItem object
bool Stickman::collidesWithItem(QGraphicsItem *object){
    //Check with the current state as collision in different states will haev different outcomes
    return current_state->collidesWithItem(object);
}

//Check for collsion between stickman and the checkpoint
bool Stickman::collidesWithCheckpoint(QGraphicsItem* object){
    if(collision && object->isVisible()){
        if (head->collidesWithItem(object) || body->collidesWithItem(object) || left_arm->collidesWithItem(object)
                || right_arm->collidesWithItem(object) || left_lower_leg->collidesWithItem(object) || right_lower_leg->collidesWithItem(object))
        {
            return true;
        }
    }
    return false;
}

//Check for collision with an enemy
bool Stickman::collidesWithEnemy(QGraphicsPixmapItem* enemy){
    return current_state->collidesWithEnemy(enemy);
}

//Return collision variable
bool Stickman::get_collision(){
    return collision;
}

//Get the different body parts of the stickman
QGraphicsItem* Stickman::get_head(){
    return head;
}

QGraphicsItem* Stickman::get_body(){
    return body;
}

QGraphicsItem* Stickman::get_left_leg(){
    return left_lower_leg;
}

QGraphicsItem* Stickman::get_right_leg(){
    return right_lower_leg;
}

QGraphicsItem* Stickman::get_left_arm(){
    return left_arm;
}

QGraphicsItem* Stickman::get_right_arm(){
    return right_arm;
}


