#pragma once 

///Project Include
#include "Core/Application.h"
#include "maze.h"
#include "hud.h"

#include "pch.h"

namespace Game
{
	class Player : public Resources::SceneNode
	{
	public:
		///Default constructor for the player
		Player()
		{
			this->setBoundingBox(DBG_NEW Collision::Box);
			this->_playerView = DBG_NEW Visual::Camera();
			this->torchlight.SetValues(this->Position, { 0.9f, 0.9f, 0.9f }, { 0, 0, 0 }, { 0.7f, 0.7f, 0.7f }, this->getPlayerCam()->Front, this->Position, cos(0.25), 0.032f);
			this->CubeCulling = DBG_NEW Collision::Box;
		}

		///Function to update evrything in the player
		void PlayerUpdate(Rendering::Application& screen, Game::Level& mazes, Sound::SoundEngine& engine, Resources::Shader& myShader);

		///Function to update the player movement
		void updateMovement(Rendering::Application& screen, Game::Level& mazes);

		///Function to handle the keybords input of the player
		void PlayerInputHandler(GLFWwindow* window, Rendering::Application& screen, Sound::SoundEngine& engine);

		///Function to get what is in our field of view
		std::vector<Resources::SceneNode*> inFieldOfView();

		///Get the camera of the player
		Visual::Camera* getPlayerCam();

		///Get the Forward vector
		LibMath::Vec3 getForward();

		///Function to compare wich object is closer
		Resources::SceneNode* compare(std::vector<Resources::SceneNode*> object);

		///Get the position of the player
		LibMath::Vec3 getPostion();

		///Get the velocity of the player
		LibMath::Vec3 getVelocity();

		///Set the player to a specific position
		void setPlayerPos(LibMath::Vec3 position);

		///Set the velocity to a specific one
		void setPlayerVelocity(LibMath::Vec3 vel);

		///Set our player Crosshair
		void SetPlayerCrosshair(Game::Crosshair* Crosshair);

		///Set our Phone
		void SetPlayerPhone(Game::Phone* phone);

		///Set our Phone Model
		void SetPhoneModel(Resources::Model* model);

		///Function to check the collision with the level
		void CollisionPlayer(Rendering::Application& screen);

		///Function to check what we have to render
		std::vector<Resources::SceneNode*> CullingBoxSelect(Level& level);

		///Function to update our BoundingBox
		void UpdatePlayerBox(LibMath::Vec3 postion);

		///Function ot update our Culling Box
		void UpdatePlayerCulling(LibMath::Vec3 postion, Level& mazes);

		///Get our Phone
		Game::Phone* getPlayerPhone();

		///Get our crosshair
		Game::Crosshair* getPlayerCrosshair();

		///Player destructor
		~Player();

		bool isSpotLightOn = false;		///Boolean to check our torchlight
		bool isChangingLevel = false;		///Boolean to check if the player is in transition
		Visual::Light torchlight;		///The torchLight
		std::vector<Resources::SceneNode*> inCullingBox;

	private:
		LibMath::Vec3 forward;			///Forward Vector
		LibMath::Vec3 Velocity;			///Velocity vector

		Visual::Camera* _playerView = nullptr;		///player camera
		Game::Crosshair* Crosshair = nullptr;		///player crosshair
		Game::Phone* Phone = nullptr;		///player phone
		Collision::Box* CubeCulling = nullptr;		///player Culling Box

		

	};
}
