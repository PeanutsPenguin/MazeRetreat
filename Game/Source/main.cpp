#include "CoreGame.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game::CoreGame theGame(1920, 1080, 4, 5);

	double lastTime = glfwGetTime();
	int nbFrames = 0;

	while (!glfwWindowShouldClose(theGame.getGameWindow()->screen))
	{	 
			// Measure speed
			//double currentTime = glfwGetTime();
			//nbFrames++;
			//if (currentTime - lastTime >= 1.0) 
			//{	// If last prinf() was more than 1 sec ago
			//	// printf and reset timer
			//	printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			//	nbFrames = 0;
			//	lastTime += 1.0;
			//}
			switch (theGame.getGameStatus())
			{
			case Game::E_TITLE:
				theGame.renderTitleScreen();
				break;
			case Game::E_PLAYING:
				theGame.renderGame();
				break;
			case Game::E_PAUSE:
				theGame.RenderPauseMenu();
				break;
			default:
				break;
			}
	}

	glfwTerminate();
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	theGame.getGameSound()->engine->drop();
}