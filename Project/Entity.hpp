#pragma once
#include "SceneNode.hpp"

// The Entity class represents any object in the game that has a position, velocity, and can be updated.
// It inherits from SceneNode, meaning it can be part of the scene graph.
class Entity :
    public SceneNode
{
public:
    // Constructor: Initializes the entity within the game world.
    Entity(Game* game);

    // Sets the entity's velocity to a specific vector.
    void setVelocity(XMFLOAT3 velocity);

    // Overloaded setVelocity: Allows setting the velocity using individual x, y, z components.
    void setVelocity(float vx, float vy, float vz);

    // Returns the current velocity of the entity as a 3D vector.
    XMFLOAT3 getVelocity() const;

    // Updates the entity's state. This method is called once per frame and is meant to be overridden by derived classes.
    // The GameTimer object provides timing information such as delta time.
    virtual void updateCurrent(const GameTimer& gt);

public:
    XMFLOAT3 mVelocity; // Holds the current velocity of the entity in 3D space.
};
