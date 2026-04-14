#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

#include "Screen.hpp"
#include "Texture.hpp"

class ScreenManager;

class MainMenuScreen : public Screen
{
    public:
        MainMenuScreen(Texture* textures, ScreenManager* screens, sf::RenderWindow* window);
        ~MainMenuScreen();

        void init_Screen() override;
        void input_to_Screen() override;
        void update_Screen(sf :: Time update_time) override;
        void display_on_Screen() override;

    private:
        Texture* textures;
        ScreenManager* screens;
        sf::RenderWindow* window;

        sf :: Text titleText;
        sf :: Text playText;
        sf :: Text exitText;

        bool isPlaySelected = false;
        bool isExitSelected = false;

        bool isPlayPressed = false;
        bool isExitPressed = false;






};