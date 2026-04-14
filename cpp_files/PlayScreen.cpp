#include "..\header_files\PlayScreen.hpp"
#include "..\header_files\Game.hpp"
#include "..\header_files\MainMenuScreen.hpp"

#include <random>
#include <stdlib.h>
#include <time.h>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


PlayScreen::PlayScreen(Texture* textures, ScreenManager* screens, sf::RenderWindow* window)
    : textures(textures)
    , screens(screens)
    , window(window)
    , snakeDirection(38.f, 0.f)
    , elapsedTime(sf::Time::Zero)
{}

PlayScreen::~PlayScreen()
{}

void PlayScreen::init_Screen()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // FIX 5: seed random

    textures->addTexture(textureID::food,  "features/texture/food.png",  false);
    textures->addTexture(textureID::grass, "features/texture/grass1.png", false);
    textures->addTexture(textureID::snake, "features/texture/snake.png",  false);
    textures->addTexture(textureID::wall,  "features/texture/wall.png",   false);
    textures->addFont(textureID::font, "features/fonts/SairaStencil-VariableFont_wdth,wght.ttf");
    grass.setTexture(textures->getTexture(textureID::grass));
    grass.setTextureRect(window->getViewport(window->getDefaultView()));

    for (int i = 0; i < 4; ++i)
    {
        walls[i].setTexture(textures->getTexture(textureID::wall));
    }

    walls[0].setTextureRect({0, 0, (int)window->getSize().x, 16});
    walls[1].setTextureRect({0, 0, (int)window->getSize().x, 16});
    walls[1].setPosition(0, window->getSize().y - 16);

    walls[2].setTextureRect({0, 0, 16, (int)window->getSize().y});
    walls[3].setTextureRect({0, 0, 16, (int)window->getSize().y});
    walls[3].setPosition(window->getSize().x - 16, 0);

    food.setTexture(textures->getTexture(textureID::food));
    food.setPosition((int)window->getSize().x / 2, (int)window->getSize().y / 2);

    ourSnake.initSnake(textures->getTexture(textureID::snake));

    score.setFont(textures->getFont(textureID::font));
    score.setCharacterSize(30);
    score.setFont(textures->getFont(textureID::font));
    score.setFillColor(sf::Color::Black);
    score.setString("Score = " + std::to_string(scoreValue));
}


void PlayScreen::input_to_Screen()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                screens->add_Screen(std::make_unique<MainMenuScreen>(textures, screens, window));
            }
            else 
            {
                sf::Vector2f newDirection = snakeDirection;

                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    newDirection = {0.f, -38.f};
                    break;
                case sf::Keyboard::Down:
                    newDirection = {0.f, 38.f};
                    break;
                case sf::Keyboard::Left:
                    newDirection = {-38.f, 0.f};
                    break;
                case sf::Keyboard::Right:
                    newDirection = {38.f, 0.f};
                    break;
                default:
                    break;
                }

                if (std::abs(snakeDirection.x) != std::abs(newDirection.x) ||
                    std::abs(snakeDirection.y) != std::abs(newDirection.y))
                {
                    snakeDirection = newDirection;
                }
            }
        }
    }
}


void PlayScreen::update_Screen(sf::Time update_time)
{
    elapsedTime += update_time;

    if (elapsedTime.asSeconds() > 0.2f)
    {
        for (auto& wall : walls)
        {
            if (ourSnake.isOn(wall))
            {
              screens->add_Screen(std::make_unique<MainMenuScreen>(textures, screens, window), true);
                break;
            }
        }

        if (ourSnake.isOn(food))
        {
            ourSnake.growSnake(snakeDirection);
            scoreValue += 10;
            score.setString("Score = " + std::to_string(scoreValue));

            float maxX = window->getSize().x - food.getGlobalBounds().width;
            float maxY = window->getSize().y - food.getGlobalBounds().height;
            float randomX = static_cast<float>(std::rand() % static_cast<int>(maxX));
            float randomY = static_cast<float>(std::rand() % static_cast<int>(maxY));
            food.setPosition(randomX, randomY);
        }
        else
        {
            ourSnake.move(snakeDirection);
        }

        elapsedTime = sf::Time::Zero;
    }
}


void PlayScreen::display_on_Screen()
{
    window->clear();
    window->draw(grass);

    for (int i = 0; i < 4; ++i)
    {
        window->draw(walls[i]);
    }

    window->draw(food);
    window->draw(ourSnake); 
    window->draw(score);

    window->display();
}
