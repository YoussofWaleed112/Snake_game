#include "..\header_files\Texture.hpp"
#include <iostream>


Texture :: Texture()
{
}

Texture :: ~Texture()
{
}

void Texture::addTexture(int id, const std::string& filename, bool repeat) {
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(filename))
        std::cerr << "Error loading texture: " << filename << std::endl;
    texture->setRepeated(repeat);
    textures[id] = std::move(texture);
}

void Texture::addFont(int id, const std::string& filename) {
    auto font = std::make_unique<sf::Font>();
    if (!font->loadFromFile(filename))
        std::cerr << "Error loading font: " << filename << std::endl;
    fonts[id] = std::move(font);
}

const sf::Texture& Texture::getTexture(int id) const {
    auto it = textures.find(id);
    if (it == textures.end()) throw std::runtime_error("Texture not found");
    return *(it->second);
}

const sf::Font& Texture::getFont(int id) const {
    auto it = fonts.find(id);
    if (it == fonts.end()) throw std::runtime_error("Font not found");
    return *(it->second);
}