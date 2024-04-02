#pragma once

#include <functional>

class SceneNode;

class Command {
public:
    // Default constructor
    Command() : category(0) {}

    // Constructor that takes an action and a category
    Command(std::function<void(SceneNode&)> act, unsigned int cat)
        : action(act), category(cat) {}

    std::function<void(SceneNode&)> action;
    unsigned int category;  // Ensure this type matches your category type
};


