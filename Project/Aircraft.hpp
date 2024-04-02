#pragma once
#include "Entity.hpp"
#include <string>

// The Aircraft class represents a specific type of entity in the game - an aircraft.
// It inherits from Entity to leverage common entity functionalities like positioning and movement.
class Aircraft : public Entity
{
public:
    // Enum to define the possible types of aircrafts in the game.
    enum Type
    {
        Eagle, // Represents an Eagle type aircraft.
        Raptor, // Represents a Raptor type aircraft.
    };

public:
    // Constructor: Initializes an aircraft with a specific type and game context.
    Aircraft(Type type, Game* game);

    // Gets the current position of the aircraft.
    XMFLOAT3 getPosition() const { return mPosition; }

    // Abstract method to get the forward vector of the aircraft. Implementation should define how this vector is calculated.
    XMFLOAT3 getForwardVector() const;

    // Gets the pitch (rotation around the x-axis) of the aircraft.
    float getPitch() const
    {
        XMFLOAT3 rotation = getWorldRotation(); // Obtain rotation from the Entity base class.
        return rotation.x; // Return the Pitch component.
    }

    // Gets the yaw (rotation around the y-axis) of the aircraft.
    float getYaw() const
    {
        XMFLOAT3 rotation = getWorldRotation(); // Obtain rotation from the Entity base class.
        return rotation.y; // Return the Yaw component.
    }

    // Gets the roll (rotation around the z-axis) of the aircraft.
    float getRoll() const
    {
        XMFLOAT3 rotation = getWorldRotation(); // Obtain rotation from the Entity base class.
        return rotation.z; // Return the Roll component.
    }

    void moveForward(float dt);
    void moveBackward(float dt);
    void adjustYaw(float amount);
    void adjustPitch(float amount);
    void adjustRoll(float amount);
private:
    // Draws the current aircraft. To be implemented specifically in derived classes.
    virtual void drawCurrent() const;

    // Builds the graphical representation of the aircraft. Specific to derived classes.
    virtual void buildCurrent();

    // The position of the aircraft in the game world.
    XMFLOAT3 mPosition;

    // Updates the state of the aircraft with respect to the game timer.
    void updateCurrent(const GameTimer& gt);

private:
    // The type of the aircraft, determined by the Type enum.
    Type mType;

    // The sprite associated with the aircraft for rendering.
    std::string mSprite;
};
