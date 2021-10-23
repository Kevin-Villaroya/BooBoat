#include "TextureTool.h"
#include <algorithm>
#include <iostream>

TextureTool::TextureTool() : sf::Texture() {}

TextureTool::TextureTool(std::string locationFolder) : sf::Texture(){
  this->loadFromFile(locationFolder);
}