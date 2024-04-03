#include "Player.hpp"
#include "Aircraft.hpp"
#include <Windows.h> // For GetAsyncKeyState
#include <map>

struct AircraftMover
{
    DirectX::XMFLOAT2 velocity;

    AircraftMover(float vx, float vy)
        : velocity(vx, vy)
    {
    }

    void operator()(Aircraft& aircraft, float dt) const
    {
        aircraft.moveForward(dt);
    }
};

Player::Player()
{
    // Set initial key bindings
    mKeyBinding[VK_LEFT] = MoveLeft;
    mKeyBinding[VK_RIGHT] = MoveRight;
    mKeyBinding[VK_UP] = MoveUp;
    mKeyBinding[VK_DOWN] = MoveDown;

    // Set initial action bindings
    initializeActions();

    // Assign all categories to player's aircraft
    for (auto& pair : mActionBinding)
        pair.second.category = Category::PlayerAircraft;
}

void Player::handleEvent(CommandQueue& commands) 
{
    mInputHandler.handleEvent(commands);
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
    for (auto pair : mKeyBinding)
    {
        if (GetAsyncKeyState(pair.first) & 0x8000)
        {
            commands.push(mActionBinding[pair.second]);
        }
    }
}

void Player::assignKey(Action action, int key)
{
    mKeyBinding[key] = action;
}

int Player::getAssignedKey(Action action) const
{
    for (auto pair : mKeyBinding)
    {
        if (pair.second == action)
            return pair.first;
    }

    return -1; // or some other invalid key code
}

void Player::initializeActions()
{
    const float playerSpeed = 200.f;

   //mActionBinding[MoveLeft] = Command(AircraftMover(-playerSpeed, 0.f), Category::PlayerAircraft);
   //mActionBinding[MoveRight] = Command(AircraftMover(playerSpeed, 0.f), Category::PlayerAircraft);
   //mActionBinding[MoveUp] = Command(AircraftMover(0.f, -playerSpeed), Category::PlayerAircraft);
   //mActionBinding[MoveDown] = Command(AircraftMover(0.f, playerSpeed), Category::PlayerAircraft);
}

bool Player::isRealtimeAction(Action action)
{
    switch (action)
    {
    case MoveLeft:
    case MoveRight:
    case MoveDown:
    case MoveUp:
        return true;

    default:
        return false;
    }
}
