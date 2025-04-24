#pragma once

#include "Player.h"
#include "Core/sound.h"
#include "hud.h"
#include "pch.h"

namespace Game
{
	enum GAME_STATUS
	{
		E_TITLE,
		E_PLAYING,
		E_PAUSE
	};

	class CoreGame
	{
	public:		
	
		CoreGame() = default;		///Default constructor for the CoreGame

		CoreGame(int windowX, int windowY, int nbrLevel, int levelSize);		///Constructor with a window size and a number of level and their size

		void recreateGame(int nbrLevel, int levelSize);		///Function to recreate the entire game

		void renderGame();			///Function to render the game

		void RenderCullingBox(std::vector<Resources::SceneNode*> toRender, Resources::Shader& shader, const LibMath::Mat4& pvm, Rendering::Application& screen, Resources::SceneNode& player, Sound::SoundEngine& engine);		///Function to render what's inside the culling box

		void RenderPauseMenu();		///Function to render the pause menu

		void renderTitleScreen();		///Function to render the title screen

		void updateGame();		///Function to update the entire game

		void deleteGame();		///Function to delete the game

		Rendering::Application* getGameWindow();		///Get the window

		Resources::ResourcesManager* getGameManager();		///Get the the Manager

		Game::Player* getGamePlayer();		///Get the player

		Game::Level* getGameLevel();		///Get the Level
			
		Sound::SoundEngine* getGameSound();		///Get the sound engine

		Resources::Shader* getgameShader();		///Get the shader progran

		GAME_STATUS getGameStatus();		///Get the current status

		~CoreGame();		///Destructor of coreGame
	
	private :
		Rendering::Application* window = nullptr;		///Window pointer
		Resources::ResourcesManager* manager = nullptr;		///Manager pointer
		Game::Player* player = nullptr;		///Player pointer
		Game::Level* level = nullptr;		///Level pointer
		Sound::SoundEngine* sound = nullptr;		///Sound engine pointer
		Resources::Shader* shader = nullptr;		///Shader pointer

		GLFWcursorposfun previousFunc;		///Keep the default mouse imput function

		GAME_STATUS currentStatus = E_TITLE;		///Status of the game

		float MenuCoolDown = 0;		///CoolDown for the menu

		bool isMenuOpen = false;		///Boolean to check if the menu os open
	};

	void RenderFrame();		///Render a frame with ImGui
}