#include "../include/json.h"
#include <string>
#include <iostream>

// For convinience we make a shortcut to the json type
using json = nlohmann::json;

void JsonDemo()
{
    // Make a string from a literal
    std::string JsonStr = "{\"happy\":true,\"pi\":3.141}";

    // Parsing the string to the json type
    json j = json::parse(JsonStr);

    // Now we can subscribe single elements from the json
    std::cout << j["pi"] << std::endl;
}
