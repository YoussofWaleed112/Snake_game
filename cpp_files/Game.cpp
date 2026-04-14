#include "..\header_files\Game.hpp"
#include "..\header_files\MainMenuScreen.hpp"


Game :: Game()
{
    textures = std ::make_shared<Texture>();
    screens =  std :: make_shared<ScreenManager>();
    window = std :: make_shared<sf ::RenderWindow>();
    window->create(sf::VideoMode(800, 500), "Snake Game", sf::Style::Close);
    
    screens->add_Screen(std :: make_unique<MainMenuScreen>(textures.get(), screens.get(), window.get()));
}

Game:: ~Game(){} 

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    while (window->isOpen())
    {
        timeSinceLastFrame += clock.restart();

        while (timeSinceLastFrame >= FramePerSecond)
        {
            timeSinceLastFrame -= FramePerSecond;

            screens->process_Screen_Changes();

            if (screens->isEmpty()) break; // safety guard

            screens->get_Current_Screen()->input_to_Screen();

            screens->process_Screen_Changes(); // handle any screen change triggered by input

            if (screens->isEmpty()) break;

            screens->get_Current_Screen()->update_Screen(FramePerSecond);

            screens->process_Screen_Changes(); // handle any screen change triggered by update

            if (screens->isEmpty()) break;

            screens->get_Current_Screen()->display_on_Screen();
        }
    }
}
