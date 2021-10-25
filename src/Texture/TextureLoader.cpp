#include "TextureLoader.h"

TextureTool TextureLoader::WATER_TEXTURE(TextureTool("assets/water.png"));
TextureTool TextureLoader::LAND_TEXTURE(TextureTool("assets/forest.png"));
TextureTool TextureLoader::MARKET_TEXTURE(TextureTool("assets/market.png"));
TextureTool TextureLoader::WIND_TEXTURE(TextureTool("assets/wind.png"));
TextureTool TextureLoader::BOAT_TEXTURE(TextureTool("assets/boat.png"));

sf::Texture* TextureLoader::getWaterTexture(){
    return &TextureLoader::WATER_TEXTURE;
}

sf::Texture* TextureLoader::getLandTexture(){
    return &TextureLoader::LAND_TEXTURE;
}

sf::Texture* TextureLoader::getMarketTexture(){
    return &TextureLoader::MARKET_TEXTURE;
}

sf::Texture* TextureLoader::getWindTexture(){
    return &TextureLoader::WIND_TEXTURE;
}

sf::Texture* TextureLoader::getBoatTexture(){
    return &TextureLoader::BOAT_TEXTURE;
}