#pragma once

#include <stack>
#include <memory>
#include "Screen.hpp"

class ScreenManager
{
    private:
        std :: stack<std ::unique_ptr <Screen>> screenStack;
        std :: unique_ptr <Screen> newScreen;

        bool toAdd {false};
        bool toRemove {false};
        bool toReplace {false};

    public:
        ScreenManager();
        ~ScreenManager();

        void add_Screen(std :: unique_ptr <Screen> new_screen, bool isReplacing = true);
        void remove_Screen();
        void process_Screen_Changes();
        bool isEmpty() const;

        std :: unique_ptr <Screen> &get_Current_Screen();


};