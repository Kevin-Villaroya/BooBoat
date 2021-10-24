#include "TextureLoader.h"

TextureTool TextureLoader::WATER_TEXTURE(TextureTool("assets/water.png"));
TextureTool TextureLoader::LAND_TEXTURE(TextureTool("assets/forest.png"));
TextureTool TextureLoader::MARKET_TEXTURE(TextureTool("assets/market.png"));

sf::Texture* TextureLoader::getWaterTexture(){
    return &TextureLoader::WATER_TEXTURE;
}

sf::Texture* TextureLoader::getLandTexture(){
    return &TextureLoader::LAND_TEXTURE;
}

sf::Texture* TextureLoader::getMarketTexture(){
    return &TextureLoader::MARKET_TEXTURE;
}