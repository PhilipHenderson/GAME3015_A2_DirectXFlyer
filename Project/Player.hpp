#pragma once
#include "Command.hpp"
#include "InputHandler.hpp"
#include <map>
#include <windows.h> // For VK_* virtual key codes

class Player
{
public:
    Player();
    void handleEvent(CommandQueue& commands); // Simplified for DirectX input handling
    void handleRealtimeInput(CommandQueue& commands);

    enum Action
    {
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown,
        ActionCount
    };

    enum Category
    {
        PlayerAircraft,
        EnemyAircraft,
        Background,
        CategoryCount
    };

    void assignKey(Action action, int key); // Use int or specific key code type instead of sf::Keyboard::Key
    int getAssignedKey(Action action) const; // Return type changed from sf::Keyboard::Key

private:
    InputHandler mInputHandler;
    void initializeActions();
    static bool isRealtimeAction(Action action);

private:
    std::map<int, Action> mKeyBinding; // Key type changed to int or specific key code type
    std::map<Action, Command> mActionBinding;
};
