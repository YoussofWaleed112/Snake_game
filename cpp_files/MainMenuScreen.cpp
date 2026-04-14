#include "..\header_files\MainMenuScreen.hpp"
#include "..\header_files\Game.hpp"
#include "..\header_files\Screen.hpp"
#include "..\header_files\Texture.hpp"
#include "..\header_files\PlayScreen.hpp"

#include <SFML/Window/Event.hpp>


MainMenuScreen :: MainMenuScreen(Texture* textures, ScreenManager* screens, sf::RenderWindow* window)
    : textures(textures)
    , screens(screens)
    , window(window)
{
}

void MainMenuScreen :: init_Screen()
{
    textures->addFont(textureID :: font, "features/fonts/SairaStencil-VariableFont_wdth,wght.ttf");

    titleText.setFont(textures -> getFont(textureID :: font));
    titleText.setString("Abo EL Joe Snake Game");
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf :: Color :: Cyan);
    titleText.setPosition(100.f, 50.f);

    playText.setFont(textures -> getFont(textureID :: font));
    playText.setString("Play Game");
    playText.setCharacterSize(32);
    playText.setFillColor(sf :: Color :: White);
    playText.setOrigin(playText.getLocalBounds().width / 2, playText.getLocalBounds().height / 2);
    playText.setPosition(100.f, 150.f);

    exitText.setFont(textures -> getFont(textureID :: font));
    exitText.setString("Exit Game");
    exitText.setCharacterSize(32);
    exitText.setFillColor(sf :: Color :: White);
    exitText.setOrigin(exitText.getLocalBounds().width / 2, exitText.getLocalBounds().height / 2);
    exitText.setPosition(100.f, 250.f);
}

void MainMenuScreen :: input_to_Screen()
{
    sf::Event event;
    while (window->pollEvent(event))
        {  
            if (event.type == sf::Event::Closed){
                window->close(); }

            if(event.type == sf::Event::MouseMoved)
            {
                sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
                isPlaySelected = playText.getGlobalBounds().contains(mousePos);
                isExitSelected = exitText.getGlobalBounds().contains(mousePos);

                playText.setFillColor(isPlaySelected ? sf :: Color :: Yellow : sf :: Color :: White);
                exitText.setFillColor(isExitSelected ? sf :: Color :: Yellow : sf :: Color :: White);
            }
            
            if(event.type == sf::Event::MouseButtonPressed)
            {
                if(isPlaySelected && event.mouseButton.button == sf::Mouse::Left)
                {
                    isPlayPressed = true;
                   
                }
                else if(isExitSelected && event.mouseButton.button == sf::Mouse::Left)
                {
                    isExitPressed = true;
    
                   
                }
            }
        }


}

void MainMenuScreen :: update_Screen(sf :: Time update_time)
{
    // Update menu animations or states

    if(playText.getFillColor() == sf :: Color :: Yellow && isPlayPressed)
    {
        // Transition to the game screen
        screens->add_Screen(std::make_unique<PlayScreen>(textures, screens, window), true); // true = replace
    }

    else if(exitText.getFillColor() == sf :: Color :: Yellow && isExitPressed)
    {
        window->close();
    }
}

void MainMenuScreen :: display_on_Screen()
{
    window -> clear(sf::Color::Black);
    window -> draw(titleText);
    window -> draw(playText);
    window -> draw(exitText);
    window -> display();
}
 
MainMenuScreen :: ~MainMenuScreen()
{
}
