#pragma once
#include "CommandQueue.hpp"
#include "Command.hpp"
#include <map>
#include <Windows.h>  // Needed for key codes

class InputHandler {
public:
    enum Action {
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown,
        Fire
    };

    InputHandler();

    void handleEvent(CommandQueue& commands);
    void handleRealtimeInput(CommandQueue& commands);

private:
    void initializeActions();
    static bool isRealtimeAction(Action action);

    std::map<Action, Command> mActionBinding;
    std::map<int, Action> mKeyBinding;  // Map from virtual key code to action
};

