#include <string>

#include "Tests.h"

Tests::Tests()
    : m_testFailCounter(0)
{

}

bool Tests::runTests()
{
    Tests tests;
    if (!tests.checkStickmanSize())
    {
        std::cout << "Failed stickman size test" << std::endl;
        tests.updateFailCounter();
    }
    if (!tests.checkAddStickmanLives())
    {
        std::cout << "Failed stickman add lives test" << std::endl;
        tests.updateFailCounter();
    }
    if (!tests.checkDefaultStickmanLives())
    {
        std::cout << "Failed default stickman lives test" << std::endl;
        tests.updateFailCounter();
    }
    if (!tests.checkStickmanXStart())
    {
        std::cout << "Failed stickman x_start test" << std::endl;
        tests.updateFailCounter();
    }
    if (!tests.checkStickmanSpeed())
    {
        std::cout << "Failed stickman speed test" << std::endl;
        tests.updateFailCounter();
    }
    if (!tests.checkObstacleCollision())
    {
        std::cout << "Failed obstacle collision test" << std::endl;
        tests.updateFailCounter();
    }
    if (!tests.checkPowerUpSize())
    {
        std::cout << "Failed power up check test" << std::endl;
        tests.updateFailCounter();
    }
    if (!tests.failedTests())
    {
        std::cout << "Passed all tests! NICE!!" << std::endl;
        return true;
    }
    return false;
}

bool Tests::checkStickmanSize() const{
    StickmanProxy* man = new StickmanProxy("Normal");
    return true;
}

bool Tests::checkAddStickmanLives() const{
    StickmanProxy* man = new StickmanProxy("Normal");
    int passed = 0;
    man->set_lives(100);
    man->add_lives(10);
    if(man->get_lives() == 110){
        passed++;
    }
    man->add_lives(-10);
    if(man->get_lives() == 100){
        passed++;
    }
    return (passed == 2);
}

bool Tests::checkDefaultStickmanLives() const{
    int passed = 0;
    StickmanProxy* man = new StickmanProxy("Normal");
    man->set_lives(-12);
    if(man->get_lives() == 3){
        passed++; //Test default lives
    }
    man->set_lives(5);
    if(man->get_lives() == 5){
        passed++; //Test set lives
    }
    return (passed == 2);
}

bool Tests::checkStickmanXStart() const{
    int passed = 0;
    StickmanProxy* man = new StickmanProxy("Normal");
    man->construct(false, 0);
    man->set_resolution_height(600);
    man->set_resolution_width(500);
    man->set_start_x(-1110);
    if(man->get_start_x() == 0){
        passed++; //Test default value first
    }
    man->set_start_x(-10);
    if(man->get_start_x() == -10){
        passed++;
    }
    return (passed == 2);
}

bool Tests::checkStickmanSpeed() const{
    StickmanProxy* man = new StickmanProxy("Normal");
    man->set_movement_speed(10);
    return (man->get_speed() == 10);
}

bool Tests::checkObstacleCollision() const{
    int passed = 0;
    QColor o_color = QColor(255, 255, 255, 255);
    int resWidth = 600;
    int resHeight = 700;
    Obstacle* obstacle = new Obstacle(200, 10, 0, 200, resWidth, 10, o_color);
    StickmanProxy* man = new StickmanProxy("normal");
    man->set_start_size("normal");
    man->construct(false, 0);
    man->set_resolution_height(resWidth);
    man->set_resolution_width(resHeight);
    man->set_start_x(0);
    man->set_y(200);
    man->set_movement_speed(10);
    //First case is where stickman and obstacle have same x position but the obstacle is a little below the top
    //of the stickman -> this should lead to a collision!
    if(man->collidesWithItem(obstacle->get_obstacle())){
        passed++;
    }

    //Now change it so that the man is to the left of the obstacle -> should be no collision
    man->set_x(-100);
    if(!man->collidesWithItem(obstacle->get_obstacle())){
        passed++;
    }

    //Move the man into the obstacle from the left, he should be half inside the obstacle as the obstacle's x
    //position is at 0 -> should be collision
    man->set_x(-5);
    if(man->collidesWithItem(obstacle->get_obstacle())){
        passed++;
    }

    //Reset the stickmans x position to the same as the obstacle to test vertical collision:
    man->set_x(0);

    //Now change the obstacle so that it is completely below the stickman -> should be no collision
    obstacle->set_y(300);
    if(!man->collidesWithItem(obstacle->get_obstacle())){
        passed++;
    }

    int manHeight = (man->get_bottom_y() - man->get_top_y());

    //Now make the stickman stand right on top of the obstacle -> should be no collision
    //Subtract the height of the man as set_y sets the HEAD of the man at the position given
    man->set_y(300 - manHeight);
    if(!man->collidesWithItem(obstacle->get_obstacle())){
        passed++;
    }

    //Change so that the stickman is 10 units inside the obstacle from above -> should be collision
    man->set_y(300 - manHeight + 10);
    if(man->collidesWithItem(obstacle->get_obstacle())){
        passed++;
    }
    return (passed == 6);
}

bool Tests::checkPowerUpSize() const{
    int passed = 0;
    int resWidth = 600;
    int resHeight = 700;
    StickmanProxy* man = new StickmanProxy("normal");
    man->set_start_size("normal");
    man->construct(false, 0);
    man->set_resolution_height(resWidth);
    man->set_resolution_width(resHeight);
    man->set_start_x(0);
    man->set_y(200);
    man->set_movement_speed(10);
    //Give the stickman different power ups and make sure the size change is working correctly
    //Power stickman, this is giant size
    man->set_power_up(0);
    man->use_power_up(0, 0);
    if(man->get_sizeMult() == 4){
        passed++;
    }
    //Giant
    man->set_power_up(1);
    man->use_power_up(0, 0);
    if(man->get_sizeMult() == 4){
        passed++;
    }
    //Large
    man->set_power_up(2);
    man->use_power_up(0, 0);
    if(man->get_sizeMult() == 3){
        passed++;
    }
    //Tiny
    man->set_power_up(3);
    man->use_power_up(0, 0);
    if(man->get_sizeMult() == 1){
        passed++;
    }

    //Make sure the power up only lasts for 100 counts, use giant size for this test:
    man->set_power_up(0);
    man->use_power_up(0, 0);
    for(int i = 0; i < 100; i++){
        //Update the powerup timer
        man->update_power();
    }
    //The update power method will return true or false when the counter reaches 0
    if(man->update_power()){
        passed++;
    }

    return (passed == 5);
}


void Tests::updateFailCounter()
{
    ++m_testFailCounter;
}

bool Tests::failedTests() const
{
    return 0 != m_testFailCounter;
}
