#pragma once

#include "Core/Application.h"
#include "Resources/Scene.h"
#include "Resources/ResourceManager.h"


namespace Game
{
	class Crosshair
	{
	public:

		Crosshair() = default;	

		Crosshair(Rendering::Application& screen);

		void drawSquare();

		void drawCrosshair();

		~Crosshair() = default;

		bool isOverSquare{ false };

	private:
		ImVec2 squareCenter;
		float squareSize = 5.0f;
	};

	class Phone : public Resources::SceneNode
	{
	public:
		Phone() = default;

		Phone(float posX, float posY, float posZ, Resources::ResourcesManager& manager);

		~Phone() = default;
	};
}