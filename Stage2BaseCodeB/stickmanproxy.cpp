#include "stickmanproxy.h"
#include "stickman.h"
#include <QDebug>

//StickmanProxy Constructor:
StickmanProxy::StickmanProxy(std::string size_string)
    : m_stickman(size_string)
{}

//StickmanProxy Destructor:
StickmanProxy::~StickmanProxy() {
}

//Horizontal starting position (make sure it's in the allowable area!):
void StickmanProxy::set_start_x(int x){
    if (x < -(this->get_resolution_width()/2) || x > this->get_resolution_width()/2) {
        qDebug() << "Starting x position is outside the allowable area, setting to default value (0)";
        m_stickman.set_start_x(0);
    }
    else {
        m_stickman.set_start_x(x);
    }
}

int StickmanProxy::get_start_x() {
    return m_stickman.get_start_x();
}

int StickmanProxy::get_lives(){
    return m_stickman.get_lives();
}

int StickmanProxy::get_xPos(){
    return m_stickman.get_xPos();
}

int StickmanProxy::get_yPos(){
    return m_stickman.get_yPos();
}

//Vertical starting position (make sure it's in the allowable area!):
void StickmanProxy::set_start_y(int y) {
    if (y < 0 || y > this->get_resolution_height()) {
        qDebug() << "Starting y position is outside the allowable area, setting to default value (resolution_height)";
        m_stickman.set_start_y(this->get_resolution_height() - this->get_height());
    }
    else {
        m_stickman.set_start_y(y);
    }
}
int StickmanProxy::get_start_y() {
    return m_stickman.get_start_y();
}
//Positional information:
int StickmanProxy::get_top_y() {
    return m_stickman.get_top_y();
}
int StickmanProxy::get_bottom_y() {
    return m_stickman.get_bottom_y();
}
int StickmanProxy::get_left_x() {
    return m_stickman.get_left_x();
}
int StickmanProxy::get_right_x() {
    return m_stickman.get_right_x();
}
int StickmanProxy::get_height() {
    return m_stickman.get_height();
}
int StickmanProxy::get_width() {
    return m_stickman.get_width();
}
int StickmanProxy::get_speed(){
    return m_stickman.get_speed();
}

//Properties of stickman:
void StickmanProxy::set_size(std::string size) {
    m_stickman.set_size(size);
}
void StickmanProxy::set_start_size(std::string size){
    m_stickman.set_start_size(size);
}
void StickmanProxy::set_z(int z) {
    m_stickman.set_z(z);
}
void StickmanProxy::set_movement_speed(int speed) {
    m_stickman.set_movement_speed(speed);
}
void StickmanProxy::set_lives(int lives){
    if(lives <= 0){
        qDebug() << "Tried to set value of lives <= 0, default lives of 3";
        m_stickman.set_lives(3);
    }
    else{
        m_stickman.set_lives(lives);
    }
}

//Add lives to the stickman
void StickmanProxy::add_lives(int add){
    m_stickman.add_lives(add);
}

//Get the size multiplier value
float StickmanProxy::get_sizeMult(){
    return m_stickman.get_sizeMult();
}

void StickmanProxy::construct(bool freeVar, int start) {
    m_stickman.construct(freeVar, start);
}

//Power up stuff:
bool StickmanProxy::update_power(){
    return m_stickman.update_power();
}

int StickmanProxy::get_power_up(){
    return m_stickman.get_power_up();
}

void StickmanProxy::set_power_up(int type){
    m_stickman.set_power_up(type);
}

void StickmanProxy::use_power_up(int x, int y){
    m_stickman.use_power_up(x, y);
}

void StickmanProxy::reset_size(){
    m_stickman.reset_size();
}

bool StickmanProxy::check_camera(int res_width){
    return m_stickman.check_camera(res_width);
}

//Drawing functions of stickman:
void StickmanProxy::attach_to_scene(QGraphicsScene* scene) {
    m_stickman.attach_to_scene(scene);
}
void StickmanProxy::remove_from_scene(QGraphicsScene* scene){
    m_stickman.remove_from_scene(scene);
}
void StickmanProxy::draw(QGraphicsScene *scene) {
    m_stickman.draw(scene);
}
void StickmanProxy::draw(QGraphicsScene *scene, bool game_jump) {
    m_stickman.draw(scene,game_jump);
}

//Set movement properties of stickman:
void StickmanProxy::reset_position(){
    m_stickman.reset_position();
}

void StickmanProxy::set_x(int x) {
    m_stickman.set_x(x);
}
void StickmanProxy::set_y(int y){
    if (y > this->get_start_y()) {
        qDebug() << "Tried to set value below ground";
        m_stickman.set_y(this->get_start_y());
    } else {
        m_stickman.set_y(y);
    }
}
void StickmanProxy::set_collision(bool setting) {
    m_stickman.set_collision(setting);
}
void StickmanProxy::set_gravity(float given_gravity) {
    if (given_gravity <= 0) {
        qDebug() << "Tried to set gravity to <= 0, setting to default value (9.8)";
        m_stickman.set_gravity(9.8);
    }
    else {
        m_stickman.set_gravity(given_gravity);
    }
}
void StickmanProxy::set_vertical_velocity(float vertical_velocity) {
    if (vertical_velocity <= 0) {
        qDebug() << "Tried to set vertical velocity (jump speed) to <= 0, setting to default value (10)";
        m_stickman.set_vertical_velocity(10);
    }
    else {
        m_stickman.set_vertical_velocity(vertical_velocity);
    }
}

//Check if stickman collides:
bool StickmanProxy::collidesWithItem(QGraphicsItem* object) {
    return m_stickman.collidesWithItem(object);
}

//Check if stickman collides with the checkpoint
bool StickmanProxy::collidesWithCheckpoint(QGraphicsItem* object){
    return m_stickman.collidesWithCheckpoint(object);
}

//Check if stickman collides with a power up:
bool StickmanProxy::collidesWithPowerUp(QGraphicsEllipseItem *powerUp){
    return m_stickman.collidesWithPowerUp(powerUp);
}

bool StickmanProxy::collidesWithEnemy(QGraphicsPixmapItem* enemy){
    return m_stickman.collidesWithEnemy(enemy);
}


//Move stickman horizontally:
void StickmanProxy::move(){
    m_stickman.move();
}

//Resolution setters:
void StickmanProxy::set_resolution_width(int width) {
    resolution_width = width;
}
void StickmanProxy::set_resolution_height(int height) {
    resolution_height = height;
}

//Resolution getters:
int StickmanProxy::get_resolution_width() {
    return resolution_width;
}
int StickmanProxy::get_resolution_height() {
    return resolution_height;
}

