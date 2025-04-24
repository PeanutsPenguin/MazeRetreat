#include "CoreGame.h"

namespace Game
{
	///Constructor with a window size and a number of level and their size
	CoreGame::CoreGame(int windowX, int windowY, int nbrLevel, int levelSize)
	{
		///Create all the pointer and the object
		this->window = DBG_NEW Rendering::Application(windowX, windowY);		
		this->manager = DBG_NEW Resources::ResourcesManager;
		this->player = DBG_NEW Game::Player;
		this->level = DBG_NEW Game::Level(nbrLevel, *this->manager, levelSize);
		this->sound = DBG_NEW Sound::SoundEngine;
		this->shader = DBG_NEW Resources::Shader;

		///Set the crosshair, the phone and the canera at the right place
		this->player->SetPlayerCrosshair(DBG_NEW Game::Crosshair(*this->window));
		this->player->SetPlayerPhone(DBG_NEW Game::Phone(0.60, -0.60, 0, *this->manager));
		this->window->MainCamera = this->player->getPlayerCam();

		///Create the shader program
		unsigned int vertexShader = this->shader->SetShader("Shaders/vertexShaderSrc.glsl", GL_VERTEX_SHADER);
		unsigned int fragmentShader = this->shader->SetShader("Shaders/fragmentShaderSrc.glsl", GL_FRAGMENT_SHADER);
		this->shader->SahderProg = this->shader->Link({ vertexShader, fragmentShader });

		///Enable the depth and the blend 
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}		

	///Function to recreate the entire game
	void CoreGame::recreateGame(int nbrLevel, int levelSize)
	{
		///Recreate the game and recreate the phone
		this->level->recreateLevel(nbrLevel, *this->manager, levelSize + 1);
		this->player->SetPhoneModel(this->manager->CreateRessource<Resources::Model>("Assets/Meshes/sphere.obj"));
	}

	///Function to render the game
	void CoreGame::renderGame()
	{
		///Process Events
		glfwPollEvents();

		///New Imgui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		///Set the right numbers of light
		glUniform1i(glGetUniformLocation(this->shader->SahderProg, "nbLight"), this->getGameLevel()->_MazeScene.size() + 1);

		///Play the ambient music
		if (!this->sound->engine->isCurrentlyPlaying(this->sound->ambientMusic))
			this->sound->engine->play2D(this->sound->ambientMusic);

		///Clear the Screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		///Use our shader Program
		glUseProgram(this->shader->SahderProg);

		///Check the Keyboard Input
		this->window->processInput(this->window->screen);

		///Update the Game
		this->updateGame();

		///Calculate the Projection View Model Matrix
		LibMath::Mat4 pvm = this->player->getPlayerCam()->projection * this->player->getPlayerCam()->view * this->player->getPlayerCam()->transformation;

		///Set the draw mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		///Render the object that are in the Culling Box and the Phone
		if(!this->getGamePlayer()->isChangingLevel)
		{
			this->RenderCullingBox(this->getGamePlayer()->inCullingBox, *this->shader, pvm, *this->window, *this->player, *this->sound);
			this->player->getPlayerPhone()->RenderNode(*this->shader, this->player->getPlayerPhone()->local.m_transform, *this->window, *this->player, *this->sound);
		}
	

		///Render the ImGui frame
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		///Swap Buffers
		glfwSwapBuffers(this->window->screen);
	}

	///Function to render what's inside the culling box
	void CoreGame::RenderCullingBox(std::vector<Resources::SceneNode*> toRender, Resources::Shader& shader, const LibMath::Mat4& pvm, Rendering::Application& screen, Resources::SceneNode& player, Sound::SoundEngine& engine)
	{
		///Move the key that has to be move and render the lights in the maze
		for(int i = 0; i < this->getGameLevel()->_MazeScene.size() + 1; ++i)
		{
			if (i == this->getGameLevel()->_MazeScene.size())
			{
				this->getGameLevel()->getfirstLight().renderPoint(shader, i);
			}
			else if (i < this->getGameLevel()->_MazeScene.size())
			{
				if (i == 2)
					this->getGameLevel()->_MazeScene[i]->moveKeys(pvm, screen);

				int BoxIndex = this->getGameLevel()->_MazeScene[i]->CellArray[this->getGameLevel()->_MazeScene[i]->getsolution()->boxIndex.first][this->getGameLevel()->_MazeScene[i]->getsolution()->boxIndex.second]._cellwalls.size() - 1;

				LibMath::Vec3 color = this->getGameLevel()->_MazeScene[i]->CellArray[this->getGameLevel()->_MazeScene[i]->getsolution()->boxIndex.first][this->getGameLevel()->_MazeScene[i]->getsolution()->boxIndex.second]._cellwalls[BoxIndex]->color;

				this->getGameLevel()->_MazeScene[i]->keyLight.UpdateColor(color);
				this->getGameLevel()->_MazeScene[i]->keyLight.renderPoint(shader, i);
			}
		}

		///Render nodes that are in the culling
		for(int i = 0; i < toRender.size(); ++i)
		{
			toRender[i]->RenderNode(shader, pvm, screen, player, engine);
		}
	}

	///Function to render the pause menu
	void CoreGame::RenderPauseMenu()
	{
		///Update the delataTime for the coolDown
		this->window->updateDeltaTime();
		this->MenuCoolDown += this->window->getDeltaTime();

		///Process Events
		glfwPollEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		///Clear the Screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		///size of GLFW window
		int windowWidth = 1920,
			windowHeight = 1080;

		///Set the right moe function Call back
		glfwSetCursorPosCallback(this->window->screen, this->previousFunc);

		///Calculate the center position
		ImVec2 windowPos = ImVec2(windowWidth / 2 - windowWidth / 8, windowHeight / 2 - windowHeight / 8);

		///Set the center position
		ImGui::SetNextWindowPos(windowPos, ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(windowWidth / 4, windowHeight / 4));
		glfwSetInputMode(this->window->screen, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		
		///Create the ImGui window
		ImGui::Begin("Pause Menu", &this->isMenuOpen, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration); //ImGui window

		///Button to restart the game
		if (ImGui::Button("Restart", ImVec2(465, 83)))
		{
			this->deleteGame();		///Delete the Game first
			this->recreateGame(4, 5);		///Recreate it
			this->player->setPlayerPos({ 1.f , 0.f, 1.f });		///Reset the player pos
			this->player->setPlayerVelocity({ 0, 0, 0 });		///Reset the player velocity
			this->player->color = { 0, 0, 0, 1.0f };		///Reset the player color
			this->player->grounded = true;		///Set is grounded
			this->isMenuOpen = false;		/// Close pause menu
			glfwSetInputMode(this->window->screen, GLFW_CURSOR, GLFW_CURSOR_DISABLED);		///Reset the mouse inputFunction
			glfwSetCursorPosCallback(this->window->screen, this->window->mouse_callback);
			this->currentStatus = E_PLAYING;		///Set the right status for the game
		}

		///Button to return to the title screen
		if (ImGui::Button("Return title screen", ImVec2(465, 83)))
		{
			///Stop everysound
			if (this->sound->engine->isCurrentlyPlaying(this->sound->ambientMusic))
				this->sound->engine->stopAllSounds();
		
			this->deleteGame();		///delete the game
			this->recreateGame(4, 5);		///recreate it
			this->player->setPlayerPos({ 1.f , 0.f, 1.f });		///Reset the player pos
			this->player->setPlayerVelocity({ 0, 0, 0 });		///Reset the player velocity
			this->player->grounded = true;		///Set is grounded
			this->currentStatus = E_TITLE;		///Set the right status for the game
		    this->isMenuOpen = false;		/// Close pause menu
		}

		///Button quit
		if (ImGui::Button("Quit", ImVec2(465, 83))) {
			glfwSetWindowShouldClose(this->window->screen, GLFW_TRUE);		///Close the window
		}

		///If we press E again close the pause the game
		if (glfwGetKey(this->window->screen, GLFW_KEY_E) == GLFW_PRESS && this->MenuCoolDown > 1)
		{
			this->isMenuOpen = false; // Close pause menu
			glfwSetInputMode(this->window->screen, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetCursorPosCallback(this->window->screen, this->window->mouse_callback);
			this->MenuCoolDown = 0;
			this->currentStatus = E_PLAYING;
		}

		ImGui::End();

		ImGui::Render();
		RenderFrame();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		///Swap Buffers
		glfwSwapBuffers(this->window->screen);
	}

	///Function to render the title screen
	void CoreGame::renderTitleScreen()
	{
		///Process Events
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		///Clear the Screen
		glClear(GL_COLOR_BUFFER_BIT);

		if (!this->sound->engine->isCurrentlyPlaying(this->sound->themeSound))
			this->sound->engine->play2D(this->sound->themeSound); 

		//size of GLFW window
		int windowWidth = 1920,
			windowHeight = 1080;

		///Calculate the center position
		ImVec2 windowPos = ImVec2(windowWidth / 2 - windowWidth / 8, windowHeight / 2 - windowHeight / 8);

		///Set the center position
		ImGui::SetNextWindowPos(windowPos, ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(windowWidth/ 4, windowHeight/4));
		ImGui::Begin("The Backrooms Retreat", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration);

		///Play button
		if (ImGui::Button("Play", ImVec2(465, 125)))
		{
			this->sound->engine->play2D(this->sound->DoorKnocking);
			glfwSetInputMode(this->window->screen, GLFW_CURSOR, GLFW_CURSOR_DISABLED);		///Set the right Mouse function call back
			this->previousFunc = glfwSetCursorPosCallback(this->window->screen, this->window->mouse_callback);
			this->currentStatus = E_PLAYING;		///Change the status of the game
		}
	
		///Quit button
		if (ImGui::Button("Quit", ImVec2(465, 125)))
		{
			glfwSetWindowShouldClose(this->window->screen, GLFW_TRUE);		///Close the window
		}

		ImGui::End();

		ImGui::Render();
		RenderFrame();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		///Swap Buffers
		glfwSwapBuffers(this->window->screen);
	}

	///Function to update the entire game
	void CoreGame::updateGame()
	{
		///Update the deltaTime
		this->window->updateDeltaTime();

		///Update the player
		this->player->PlayerUpdate(*this->window, *this->level, *this->sound, *this->getgameShader());

		///Increase the menu cooldown
		this->MenuCoolDown += this->window->getDeltaTime();

		///If we press E open the pause menu
		if (glfwGetKey(this->window->screen, GLFW_KEY_E) == GLFW_PRESS && this->MenuCoolDown > 1)
		{	
			this->MenuCoolDown = 0;
			this->currentStatus = E_PAUSE;
		}
		
		///If the player has fall down, recreate the game
		if(this->player->getPostion().y < -10)
		{
			this->deleteGame();
			this->recreateGame(4, this->level->MazeSize);
			this->player->setPlayerPos({ 1.f , 0.f, 1.f });
			this->player->setPlayerVelocity({ 0, 0, 0 });
			this->player->grounded = true;
		}
	}

	///Delete the Game
	void CoreGame::deleteGame()
	{

		for (int mazesIndex = 0; mazesIndex < this->level->_MazeScene.size(); ++mazesIndex)
		{
			for (int cellRowIndex = 0; cellRowIndex < this->level->_MazeScene[mazesIndex]->getNumberRows(); ++cellRowIndex)
			{
				for (int cellColumnIndex = 0; cellColumnIndex < this->level->_MazeScene[mazesIndex]->getNumberColumns(); ++cellColumnIndex)
				{
					this->level->_MazeScene[mazesIndex]->CellArray[cellRowIndex][cellColumnIndex].~Cell();
				}
			}

			delete this->level->_MazeScene[mazesIndex];
		}
		
		this->level->_MazeScene.clear();

		this->manager->deleteArray();
	}
	
	///Get the window
	Rendering::Application* CoreGame::getGameWindow()
	{
		return this->window;
	}

	///Get the the Manager
	Resources::ResourcesManager* CoreGame::getGameManager()
	{
		return this->manager;
	}

	///Get the player
	Game::Player* CoreGame::getGamePlayer()
	{
		return this->player;
	}
	
	///Get the Level
	Game::Level* CoreGame::getGameLevel()
	{
		return this->level;
	}

	///Get the sound engine
	Sound::SoundEngine* CoreGame::getGameSound()
	{
		return this->sound;
	}
	
	///Get the shader progran
	Resources::Shader* CoreGame::getgameShader()
	{
		return this->shader;
	}

	///Get the current status
	GAME_STATUS CoreGame::getGameStatus()
	{
		return this->currentStatus;
	}

	///Destructor of coreGame
	CoreGame::~CoreGame()
	{
		delete this->shader;
		delete this->sound;
		delete this->level;
		delete this->player;
		delete this->manager;
		delete this->window;
	}

	///Render a frame with ImGui
	void RenderFrame()
	{
		ImGui::Render();
		ImDrawData* draw_data = ImGui::GetDrawData();
		if (draw_data != nullptr) {
			ImGui_ImplOpenGL3_RenderDrawData(draw_data);
		}
	}
}


