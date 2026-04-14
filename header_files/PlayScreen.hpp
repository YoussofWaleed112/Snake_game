#pragma once

#include <array>
#include <memory>


#include "Screen.hpp"
#include "Texture.hpp"
#include "ScreenManager.hpp"
#include "Snake.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class PlayScreen : public Screen
{
    public:
        PlayScreen(Texture* textures, ScreenManager* screens, sf::RenderWindow* window);
        ~PlayScreen();

        void init_Screen() override;
        void input_to_Screen() override;
        void update_Screen(sf :: Time update_time) override;
        void display_on_Screen() override;

    private:
        Texture* textures;
        ScreenManager* screens;
        sf::RenderWindow* window;
        Snake ourSnake;
        sf :: Sprite food;
        sf :: Sprite grass;

        sf :: Text score;
        int scoreValue{0};
        std :: array<sf :: Sprite, 4> walls;

        sf:: Vector2f snakeDirection;
        sf:: Time elapsedTime;


};