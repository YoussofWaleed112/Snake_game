#pragma once

#include <SFML/System/Time.hpp>

/* Our Game consists of multiple screens, 
at which we want to be able to intialize and switch between them.*/

class Screen
{
// Initlize the screen, handle input from the user, update the screen and display the screen.
    public:
        Screen();
        virtual ~Screen();

        virtual void init_Screen() = 0;
        virtual void input_to_Screen() = 0;
        virtual void update_Screen(sf :: Time update_time) = 0;
        virtual void display_on_Screen() = 0;

        virtual void pause_Screen(){};
        virtual void start_Screen(){};
};

inline Screen::Screen() {}
inline Screen::~Screen() {}


