#include "..\header_files\ScreenManager.hpp"

ScreenManager :: ScreenManager() : newScreen(nullptr)
{
}


void ScreenManager :: add_Screen(std :: unique_ptr <Screen> new_screen, bool isReplacing)
{
    this -> toAdd = true;
    this -> newScreen = std :: move(new_screen);
    this -> toReplace = isReplacing;

}

void ScreenManager :: remove_Screen()
{
    this -> toRemove = true;
}

void ScreenManager :: process_Screen_Changes()
{
    if (this -> toRemove && !screenStack.empty())
    {
        this -> screenStack.pop();
        if (!this -> screenStack.empty())
        {
            this -> screenStack.top() -> start_Screen();
        }
        this -> toRemove = false;
    }

    if (this -> toAdd)
    {
        if (this -> toReplace && !screenStack.empty())
        {
            this -> screenStack.pop();
            this -> toReplace = false;
        }

        if(!screenStack.empty())
        {
            this -> screenStack.top() -> pause_Screen();
        }

        this -> screenStack.push(std ::move(this -> newScreen));
        screenStack.top() -> init_Screen();
        screenStack.top() -> start_Screen();

        
        this -> toAdd = false;
    }
}

std :: unique_ptr <Screen>& ScreenManager :: get_Current_Screen()
{
    return this -> screenStack.top();
}

bool ScreenManager :: isEmpty() const
{
    return this -> screenStack.empty();
}

ScreenManager :: ~ScreenManager()
{

}