#include "config.h"
#include <QDebug>

Config* Config::instance = nullptr;

Config::Config()
{

}

Config::~Config()
{

}

//Return a new instance of config:
Config* Config::get_instance()
{
    if(instance == nullptr)
        instance = new Config();
    return instance;
}

//Set path of config:
void Config::set_path(std::string filename)
{
    this->filename = filename;
}

//Get path of config:
std::string Config::get_path()
{
    return filename;
}

//Change config file to a new one:
void Config::change_file(std::string filename)
{
    close();
    config_map.clear();
    keys.clear();
    this->filename = filename;
    open();
}

//Load config:
void Config::load()
{
    std::string line;
    std::string property;
    std::string value;
    open();
    if(config_file.is_open())
    {
        while(std::getline(config_file, line))
        {
            std::size_t position = line.find("=");
            if(position > 0)
            {
                property = line.substr(0, position);
                value = line.substr(position+1, line.length()-1);
                keys.push_back(property);
                config_map[property] = value;
            }
        }
    }
    close();
}

//Save config:
void Config::save()
{
    open();
    if(config_file.is_open())
    {
        for(unsigned i = 0; i < keys.size(); i++)
        {
            config_file << keys[i] << "=" << config_map[keys[i]];
        }
    }
    close();
}

//Given a property, grap a value:
std::string Config::get_value(std::string property)
{
    return config_map[property];
}

//Set a value for a given key:
void Config::set_value(std::string key, std::string value)
{
    config_map[key] = value;
}

//Open a file:
void Config::open()
{
    if(!config_file.is_open())
        config_file.open(filename.c_str(), std::fstream::in | std::fstream::out);
}

//Close a file:
void Config::close()
{
    if(config_file.is_open())
        config_file.close();
}

//Destroy the config + delete memory:
void Config::destroy()
{
    close();
    delete instance;
}

