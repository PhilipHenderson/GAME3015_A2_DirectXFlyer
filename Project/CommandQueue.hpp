#pragma once

#include <queue>
#include "Command.hpp"

enum CommandCategory {
    MoveForwardCategory,
    MoveBackwardCategory,
    AdjustYawCategory,
    AdjustPitchCategory,
    // Add other categories as needed
};

class CommandQueue {
public:
    void push(const Command& command) {
        mQueue.push(command);
    }

    Command pop() {
        if (mQueue.empty()) 
            return Command();

        Command cmd = mQueue.front();
        mQueue.pop();
        return cmd;
    }

    bool isEmpty() const {
        return mQueue.empty();
    }

private:
    std::queue<Command> mQueue;
};
