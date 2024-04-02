#pragma once
#include "CommandQueue.hpp"
#include "SceneNode.hpp"
#include "Aircraft.hpp"
#include "SpriteNode.h"
#include "InputHandler.hpp"

class World 
{
public:
	explicit							World(Game* window);
	void								update(const GameTimer& gt);
	void								draw();

	//void								loadTextures();
	void								buildScene();

	// Getter for the player's aircraft
	Aircraft* getPlayerAircraft() const { return mPlayerAircraft; }

	CommandQueue& getCommandQueue();
	void handleCommand(const Command& command);

	void setInputHandler(InputHandler* inputHandler);


private:
	enum Layer
	{
		Background,
		Air,
		LayerCount
	};


private:
	Game*								mGame;

	SceneNode*							mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;
	CommandQueue mCommandQueue;

	XMFLOAT4							mWorldBounds;
	XMFLOAT2		    				mSpawnPosition;
	float								mScrollSpeed;
	Aircraft*							mPlayerAircraft;
	SpriteNode*							mBackground;
	Aircraft*							mEnemy;

	InputHandler* mInputHandler;
};
