#include "InputHandler.hpp"

InputHandler::InputHandler() {
    initializeActions();
    // Map virtual keys to actions
    mKeyBinding[VK_LEFT] = MoveLeft;
    mKeyBinding[VK_RIGHT] = MoveRight;
    mKeyBinding[VK_UP] = MoveUp;
    mKeyBinding[VK_DOWN] = MoveDown;
    mKeyBinding[VK_SPACE] = Fire;
}

void InputHandler::handleEvent(CommandQueue& commands) {
    // Event handling logic here
}

void InputHandler::handleRealtimeInput(CommandQueue& commands) {
    // Real-time input handling logic here
}

void InputHandler::initializeActions() {
    //  command actions here
}

bool InputHandler::isRealtimeAction(Action action) {
    // real-time action
    return true;
}
