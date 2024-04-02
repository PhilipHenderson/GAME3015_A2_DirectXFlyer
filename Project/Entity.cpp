#include "Entity.hpp"

// Constructor: Initializes an Entity with a reference to the game and default velocity.
Entity::Entity(Game* game) : SceneNode(game), mVelocity(0, 0, 0)
{
    // Intentionally left empty - initialization is done via initializer list.
}

// Sets the entity's velocity using a 3D vector.
void Entity::setVelocity(XMFLOAT3 velocity)
{
    mVelocity = velocity; // Directly updates the velocity.
}

// Overloaded setVelocity: Allows setting velocity using individual components.
void Entity::setVelocity(float vx, float vy, float vz)
{
    mVelocity.x = vx; // Set the X component of the velocity.
    mVelocity.y = vy; // Set the Y component of the velocity.
    mVelocity.z = vz; // Set the Z component of the velocity.
}

// Retrieves the current velocity of the entity.
XMFLOAT3 Entity::getVelocity() const
{
    return mVelocity; // Returns the velocity as a 3D vector.
}

// Updates the entity's position based on its velocity and the elapsed time since last frame.
void Entity::updateCurrent(const GameTimer& gt)
{
    XMFLOAT2 mV; // Temporary 2D vector for velocity.
    mV.x = mVelocity.x * gt.DeltaTime(); // Calculate horizontal displacement.
    mV.y = mVelocity.y * gt.DeltaTime(); // Calculate vertical displacement.

    move(mV.x, mV.y, 0); // Move the entity based on calculated displacement.

    // Update the renderer's world transform and mark the frame as dirty.
    renderer->World = getWorldTransform();
    renderer->NumFramesDirty++;
}
