#include "World.hpp"

// Constructor for the World class, initializes key components of the game world.
World::World(Game* game)
    : mSceneGraph(new SceneNode(game)) // Initialize the scene graph with a new SceneNode.
    , mGame(game)                      // Store the game context.
    , mPlayerAircraft(nullptr)         // Initialize the player's aircraft pointer to nullptr.
    , mBackground(nullptr)             // Initialize the background pointer to nullptr.
    , mWorldBounds(-1.5f, 1.5f, 200.0f, 0.0f) // Set the world bounds (Left, Right, Down, Up).
    , mSpawnPosition(0.f, 0.f)         // Set the initial spawn position for the player.
    , mScrollSpeed(1.0f)               // Set the background scroll speed.
    , mInputHandler(nullptr)
{
    buildScene();
}

// Update the world state based on game timer.
void World::update(const GameTimer& gt)
{
    if (mInputHandler)
    {
        mInputHandler->handleRealtimeInput(mCommandQueue);
    }

    while (!mCommandQueue.isEmpty())
    {
        Command command = mCommandQueue.pop();
        handleCommand(command);  // This will now call your handleCommand method
    }

    mSceneGraph->update(gt); // Update the entire scene graph based on the elapsed time.
}


// Draw the world.
void World::draw()
{
    mSceneGraph->draw(); // Delegate drawing to the scene graph.
}

// Builds the initial scene with player, enemies, and background.
void World::buildScene()
{
    // Create the player aircraft, set its properties, and add it to the scene graph.
    std::unique_ptr<Aircraft> player(new Aircraft(Aircraft::Eagle, mGame));
    mPlayerAircraft = player.get();
    mPlayerAircraft->setPosition(0, 0.1, 0.0);
    mPlayerAircraft->setScale(0.5, 0.5, 0.5);
    mPlayerAircraft->setWorldRotation(0, 7.85, 0);
    mSceneGraph->attachChild(std::move(player));

    // Create the first enemy aircraft, set its properties, and add it to the scene graph.
    std::unique_ptr<Aircraft> enemy1(new Aircraft(Aircraft::Raptor, mGame));
    auto raptor = enemy1.get();
    raptor->setPosition(3, 5, -1);
    raptor->setScale(1.0, 1.0, 1.0);
    raptor->setWorldRotation(0, 1.57, 0);
    mSceneGraph->attachChild(std::move(enemy1));

    // Create a second enemy aircraft, set its properties, and add it to the scene graph.
    std::unique_ptr<Aircraft> enemy2(new Aircraft(Aircraft::Raptor, mGame));
    auto raptor2 = enemy2.get();
    raptor2->setPosition(0.5, 5, -1);
    raptor2->setScale(1.0, 1.0, 1.0);
    raptor2->setWorldRotation(0, 0, 0);
    mSceneGraph->attachChild(std::move(enemy2));

    // Create the background sprite, set its properties, and add it to the scene graph.
    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame));
    mBackground = backgroundSprite.get();
    mBackground->setPosition(mWorldBounds.x, mWorldBounds.y, 0.0f);
    mBackground->setPosition(0, 0, 0.0);
    mBackground->setScale(1.0, 1.0, 1.0);
    mSceneGraph->attachChild(std::move(backgroundSprite));

    // Finalize the scene graph construction.
    mSceneGraph->build();
}

CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
}

void World::handleCommand(const Command& command)
{
    if (mSceneGraph) {
        mSceneGraph->onCommand(command);
    }
}

void World::setInputHandler(InputHandler* inputHandler)
{
    mInputHandler = inputHandler;
}
