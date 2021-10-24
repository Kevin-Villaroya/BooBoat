#ifndef __Texture_Loader_H__
#define __Texture_Loader_H__

#include "TextureTool.h"
#include <SFML/Graphics/Texture.hpp>

class TextureLoader{
private:
    static TextureTool WATER_TEXTURE;
    static TextureTool LAND_TEXTURE;
    static TextureTool MARKET_TEXTURE;

public:

    static sf::Texture* getWaterTexture();
    static sf::Texture* getLandTexture();
    static sf::Texture* getMarketTexture();
};

#endif