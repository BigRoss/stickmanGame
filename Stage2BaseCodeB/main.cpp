#include <QApplication>
#include <QThread>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <string>
#include "tests.h"
#include "gamedialog.h"
#include "config.h"
#include "stickman.h"
#include "obstacle.h"
#include "background.h"
#include "powerup.h"
#include "enemy.h"
#include "drawablefactory.h"
#include "stickmanproxy.h"

bool config_is_ok(Config* config)
{
    std::string value = config->get_value("StickmanSize");
    bool playable = true;
    long val;
    try
    {
        val = std::strtol(config->get_value("StickmanStartX").c_str(), NULL, 0);
        val = std::strtol(config->get_value("StickmanStartY").c_str(), NULL, 0);
        val = std::strtol(config->get_value("StickmanVelocity").c_str(), NULL, 0);
        val = std::strtol(config->get_value("BackgroundSpeed").c_str(), NULL, 0);
        val = std::strtol(config->get_value("ResolutionWidth").c_str(), NULL, 0);
        val = std::strtol(config->get_value("ResolutionHeight").c_str(), NULL, 0);
        val = std::strtol(config->get_value("StickmanLives").c_str(), NULL, 0);
    }
    catch(std::exception const & e)
    {
        playable = false;
    }

    //Check valid stickman sizes:
    if(!(value.compare("tiny") == 0) &&
        !(value.compare("normal") == 0) &&
        !(value.compare("large") == 0) &&
        !(value.compare("giant") == 0))
    {
        playable = false;
    }
    //Check valid background colours:
    value = config->get_value("BackgroundColor");
    if(!(value.compare("#000000") == 0)) {
        QColor color(value.c_str());
        if(color.green() == 0 && color.blue() == 0 && color.red() == 0)
        {
            playable = false;
        }
    }
    //Check valid resolution sizes:
    //value = config->get_value("ResolutionWidth");
    //if(value)

    return playable;
}

int main(int argc, char *argv[])
{
    //Uncomment thsi to run the tests
//    return Tests::runTests();
    QApplication application(argc, argv);
    GameDialog dialog;
    DrawableFactory factory; //Create the factory where we can create clouds, hills and obstacles
    Config* config = Config::get_instance(); //Create an instance of the config
    Background* background = nullptr;
    StickmanProxy* man = nullptr;
    int background_speed = 0;

    //Obstacle data:
    int number_of_obstacles = 0;
    std::string o_start = "Obstacle";
    std::string o_name;
    char o_number[10];
    int o_width(0);
    int o_height(0);
    int o_yposition(0);
    int o_space_till_next(0);
    QColor o_color;
    Obstacle* obstacle;
    bool stage2 = false;
    bool stage3 = false; //Have a boolean to check if it's stage 3
    //Set path and load config, proceed if it's valid:
    config->set_path("./Game.config");
    config->load();

    if(config_is_ok(config))
    {

        //Check if stage 2 and 3 are enabled, set the bools in the dialog appropriately
        if(atoi(config->get_value("Stage2On").c_str()) == 1){
            qDebug() << "Stage 2 On";
            stage2 = true;
            dialog.set_stage2();
        }

        if(atoi(config->get_value("Stage3On").c_str()) == 1){
            qDebug() << "Stage 3 On";
            stage3 = true;
            dialog.set_stage3();
        }

        int resHeight = atoi(config->get_value("ResolutionHeight").c_str());
        int resWidth = atoi(config->get_value("ResolutionWidth").c_str());

        //Stickman:
        man = new StickmanProxy(config->get_value("StickmanSize"));
        man->set_start_size(config->get_value("StickmanSize"));
        man->construct(false, 0);
        man->set_resolution_height(resHeight);
        man->set_resolution_width(resWidth);
        man->set_start_x(std::strtol(config->get_value("StickmanStartX").c_str(), NULL, 0));
        man->set_movement_speed(std::atoi(config->get_value("StickmanVelocity").c_str()));
        man->set_lives(atoi(config->get_value("StickmanLives").c_str()));
        man->set_start_y(std::strtol(config->get_value("StickmanStartY").c_str(), NULL, 0));
        man->set_gravity(std::strtol(config->get_value("StickmanGravity").c_str(), NULL, 0));
        man->set_vertical_velocity(std::strtol(config->get_value("StickmanVerticalVelocity").c_str(), NULL, 0));

        //Create the power up:
        PowerUp* powerUp = new PowerUp(resWidth, resHeight);

        //Background:
        QColor color(config->get_value("BackgroundColor").c_str());
        background_speed = std::strtol(config->get_value("BackgroundSpeed").c_str(), NULL, 0);

        background = factory.make_background();
        background->set_background_color(color);
        //I've modified the properties so that the clouds and hills move at the same speed as the obstacles (background_speed), doesn't make sense that they're different:
        background->add_background_item(factory.make_background_asset(CLOUD, 20, 30, 100, 90, 10, resWidth, background_speed));
        background->add_background_item(factory.make_background_asset(CLOUD, 30, 20, 90, 20, 10, resWidth, background_speed));
        background->add_background_item(factory.make_background_asset(CLOUD, 40, 40, 120, 90, 20, resWidth, background_speed));
        background->add_background_item(factory.make_background_asset(CLOUD, 35, 30, 105, 190, 13, resWidth, background_speed));
        background->add_background_item(factory.make_background_asset(CLOUD, 30, 20, 40, 300, 90, resWidth, background_speed));
        background->add_background_item(factory.make_background_asset(CLOUD, 40, 30, 80, 80, 180, resWidth, background_speed));
        background->add_background_item(factory.make_background_asset(HILLS, 40, 30, 600, 400, 300, resWidth, background_speed));

        //Only have obstacles if we are in stage2 or stage3 mode, stage1 has no obstacles
        if(stage2 || stage3){
            //Grab number of stages from config (default = 0):
            int number_of_stages = std::strtol(config->get_value("NumberOfStages").c_str(), NULL, 0);
            if(!stage3){
                //If it's not stage 3 then there is only 1 stage
                number_of_stages = 1;
            }
            std::string stageNum = "";
            //Loop through and get all the obstacles for the current stage
            for(int j = 0; j < number_of_stages; j++){
                std::vector<Obstacle*> stage;
                if(j > 0){
                    std::stringstream ss;
                    ss << j;
                    stageNum = ss.str();
                }
                //Grab number of obstacles from config (default = 0):
                number_of_obstacles = std::strtol(config->get_value("NumberOfObstacles"+stageNum).c_str(), NULL, 0);
                o_space_till_next = resWidth / 2;

                // Have a variable which will hold the x position of the obstacle with the last x position in each stage:
                int max_o_space_till_next = o_space_till_next;

                //Add in obstacles for the stage:
                for (int i = 0; i < number_of_obstacles; i++) {
                    //Properties:
                    o_name = o_start + itoa(i, o_number, 10);
                    o_width = std::strtol(config->get_value(o_name+"Width"+stageNum).c_str(), NULL, 0);
                    o_height = std::strtol(config->get_value(o_name+"Height"+stageNum).c_str(), NULL, 0);
                    o_yposition = std::strtol(config->get_value(o_name+"YPosition"+stageNum).c_str(), NULL, 0);
                    o_color = config->get_value(o_name + "Color"+stageNum).c_str();

                    //Make the obstacle and add it to the background items:
                    obstacle = factory.make_obstacle_asset(OBSTACLE, o_width, o_height, 0, o_space_till_next, o_yposition, resWidth, 1.0*background_speed, o_color);
                    background->add_background_item(obstacle);

                    //Setup the x-coordinate for the next obstacle:
                    o_space_till_next += std::strtol(config->get_value(o_name+"SpaceTillNext"+stageNum).c_str(), NULL, 0) + o_width;
                    if(o_space_till_next > max_o_space_till_next){
                        max_o_space_till_next = o_space_till_next;
                    }

                    if(j > 0){
                        //Set the obstacles not in the first stage to be invisible
                        (obstacle->get_obstacle())->setVisible(false);
                    }
                    stage.push_back(obstacle);
                }
                if(stage3){
                    //Put the checkpoint 50 units after the last obstacle and make it black
                    max_o_space_till_next += 50;
                    o_color = QColor(0, 0, 0, 255);
                     //Add a checkpoint obstacle at the end of the last stage
                    obstacle = factory.make_obstacle_asset(OBSTACLE, 500, resHeight, 0, max_o_space_till_next, 0, resWidth, 1.0*background_speed, o_color);
                    background->add_background_item(obstacle);
                    //obstacle should be invisible if not in first stage
                    if(j > 0){
                        (obstacle->get_obstacle())->setVisible(false);
                    }
                    stage.push_back(obstacle);
                }
                //Add the stage to the list of stages in dialog (so we can use it's properties later):
                dialog.add_stage(stage);
            }
        }

        //Set the resolution:
        dialog.set_resolution(resWidth, resHeight);

        //Setup the background and scene:
        dialog.set_scene_background(background->get_background_color());
        dialog.set_speed(std::atoi(config->get_value("StickmanVelocity").c_str()));
        dialog.attach_to_scene(man);
        dialog.attach_to_scene(background);
        dialog.add_drawable(man);
        dialog.add_stickman(man);
        dialog.add_drawable(background);
        if(stage3){
            //Create enemy and powerup only in stage 3
            int enemy_y = man->get_yPos();
            if(std::atoi(config->get_value("setEnemies").c_str()) != 1){
                //Put the enemy off screen if the enemy flag is off
                enemy_y += 1000;
            }
            Enemy* enemy = new Enemy(enemy_y, resWidth, resHeight);
            enemy->set_movement_speed(5); // Default move speed for enemy
            dialog.add_enemy(enemy);
            dialog.attach_to_scene(enemy);

            dialog.set_text();
            dialog.add_power_up(powerUp);
            dialog.attach_to_scene(powerUp);
        }
        dialog.toggle_pause();
        dialog.show();

        application.exec();
        delete background;
        delete man;
    }
    config->destroy();
    return 0;
}
