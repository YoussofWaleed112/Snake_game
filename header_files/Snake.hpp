#pragma once
#include <list>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Drawable.hpp>



class Snake : public sf::Drawable
{
    public:

        Snake();
        ~Snake();

        void initSnake(const sf :: Texture& texture);
        void move(sf :: Vector2f direction);
        void growSnake(sf :: Vector2f direction);
        bool isOn(sf :: Sprite& sprite) const;
        void draw(sf :: RenderTarget& target, sf :: RenderStates states) const override;
    
    private:
        std :: list<sf :: Sprite> snakeBody;
        std :: list<sf :: Sprite> :: iterator headSegment;
        std :: list<sf :: Sprite> :: iterator tailSegment;

};