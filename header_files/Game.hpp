#pragma once
#include <memory>
#include "Texture.hpp"
#include "ScreenManager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>


enum textureID{
    font = 0,
    grass = 1,
    food = 2,
    wall = 3,
    snake = 4 
};

class Game{        

    public: 
        Game();
        ~Game();

        void run();

    private : 
        std :: shared_ptr<Texture> textures;
        std :: shared_ptr<ScreenManager> screens;
        std :: shared_ptr<sf ::RenderWindow> window;
        sf :: Time FramePerSecond = sf :: seconds(1.f / 60.f);


};
