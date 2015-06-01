#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

class Config
{
public:
    static Config* get_instance();
    void set_path(std::string filename);
    void load();
    void save();
    void change_file(std::string filename);
    void set_value(std::string key, std::string value);
    void destroy();
    std::string get_value(std::string key);
    std::string get_path();

private:
    Config();
    ~Config();
    void open();
    void close();
    std::string filename;
    std::fstream config_file;
    std::map<std::string, std::string> config_map;
    std::vector<std::string> keys;
    static Config* instance;
};

#endif // CONFIG_H
