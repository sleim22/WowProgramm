/**
 * @file
 * @brief A demo file for the config module
 *
 * @author Lukas Deutscher
 * @date 30.07.2018
 */

#include "../include/config.h"
#include <string>

void ConfigDemo()
{

    // To use the config we have to initialize it first
    LoadConfig("../demo/path/config.cfg", ":", "#");

    // After that we can get config values with the keys in the file
    std::string Foo = ReadConfigString("Bar");

    // There are different functions for different var types
    // The module casts the strings if possible to the requested type
    // If it isn't possible there will be an error
}
