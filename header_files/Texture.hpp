#pragma once

#include <string>
#include <map>
#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>


class Texture
{
    private:
        std::map<int, std::unique_ptr<sf::Texture>> textures;
        std::map<int, std::unique_ptr<sf::Font>>    fonts;
                
    public:
        Texture();
        ~Texture();

        void addTexture(int TextureID, const std::string& filename, bool repeatTexture);
        void addFont(int TextureID, const std::string& filename);

        const sf::Texture &getTexture(int id) const;
        const sf::Font &getFont(int id) const;



};