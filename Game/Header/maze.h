#pragma once

///project include
#include "Resources/ResourceManager.h"
#include "Resources/Scene.h"
#include "Physics/Collision.h"
#include "LowRenderer/light.h"


///Standart include
#include <random>
#include <vector>

namespace Game
{
	class Level
	{
	public:

		class Maze
		{
		public:

			class Cell
			{
			public:

				Cell() = default;								///default Constructor

				Cell(float width, float height);				///Constructor with a specific height and width

				void SetPosition(LibMath::Vec3 position);		///Function to set the position of the cell

				LibMath::Vec3 getPosition();					///Function to get the position of the cell

				float getWidth();								///Function to get the width of the cell

				float getHeight();								///Function to get the height of the cell

				~Cell();										///Default destructor

				bool Up_Wall{ true };							///Is there an Up Wall or not
				bool Right_Wall{ true };						///Is there an Right Wall or not
				bool visited{ false };							///Is the cell has been visited already or not

				std::vector<Resources::SceneNode*> _cellwalls;					///Scene that contains the wall, ground ect of the cell
			private:
				
				LibMath::Vec3 _cellPos;							///Position of the Cell
				float width{ 0 };								///Width of the Cell
				float height{ 0 };								///Height of the Cell
			};

			class doorNkey
			{
			public:

				doorNkey() = default;		///Default constructor for the class

				~doorNkey() = default;		///Default destructor for the class

				std::pair<int, int> boxIndex;		///Pair to keep the index on where is the key
				std::pair<int, int> wallIndex;		///Pait to keep the index of where is the door
				LibMath::Mat4 target;				///Mat4 target if we want to move the keys
				LibMath::Mat4 Secondtarget;			///Another mat4 to move the key with two points
				
				bool TargetFirst = true;			///Boolean to choose on witch target the kill will go for
			};

			Maze() = default;		///Default constructor

			Maze(int Rows, int Columns);		///Constructor with specific rows and columns

			void create_Maze(LibMath::Vec3 offset, int seed);		///Initialize the creatin of the maze

			void create_Maze_r(int iIndex, int jIndex, int toRemove, int seed);		///Recursive function to create an random maze

			void createGrapples();		///Function to create the grappler

			bool checkLocationInX(int iIndex, int Jindex);		///Check if there is a Up Wall in the 3 last cells

			bool checkLocationInZ(int iIndex, int Jindex);		///Check if there is a right Wall in the 3 last cells

			void createKeys(int seed, LibMath::Vec3 offset);		///Function to create the keys and the door for the maze

			void CreateSpecialCell(int Iindex, int Jindex, LibMath::Vec4 color, LibMath::Vec3 offset);		///Function to create the specific cell where the moving key is

			void GrappleColor();		///Set the right color for the grapple

			void eraseCell(int Iindex, int Jindex);		///Function ot erase a cell except the ground

			void createNewPath(int Iindex, int Jindex);		///Function to create a path around the special key

			void setModel(int name, Resources::Model* Model);		///Set the right model

			void setTexture(int name, Resources::Texture* texture);		///Set the right Texture

			Resources::Model* getModel();		///Get the Model*

			void CreateWall(int i, int j, LibMath::Vec3 offset, LibMath::Vec3 Scaler, LibMath::Vec3 Position);		///Function to create a Wall

			void DrawMAze(LibMath::Vec3 offset, int seed);		///Draw the Maze

			void moveKeys(const LibMath::Mat4& mvp, Rendering::Application& screen);		///Function to move the key

			float getCellWidth();		///Get the cell Width

			float getCellHeight();		///Get the Cell Height

			int getNumberRows();		///Get the number of Rows

			int getNumberColumns();		///Get the number of columns

			doorNkey* getsolution();		///Get the solution

			~Maze();			///Default destructor

			std::vector<std::vector<Cell>> CellArray;		///Vector that contains all the Cells
			Visual::Light keyLight;

		private:	
			int nbrRows;		///Number of Rows
			int nbrColumns;		///Number of Colums

			doorNkey* solution;		///Pointer to the Solution

			Resources::Model* wallModel{ nullptr };		///Model for the walls
			Resources::Model* floorModel{ nullptr };		///Model for the keys

			Resources::Texture* wallTexture{ nullptr };		///Texture for the walls
			Resources::Texture* CellingTexture{ nullptr };		///Texture for the ceiling
			Resources::Texture* GroundTexture{ nullptr };		///Texture for the ground
		};

		Level() = default;		///Default constructor

		Level(int nbrMaze, Resources::ResourcesManager& manager, int size);		///Constructor with specific number of maze, the manger to initialize textures and models and the size of the mazes

		void recreateLevel(int nbrMaze, Resources::ResourcesManager& manager, int size);		///Function to recreate an entire level 

		Visual::Light getfirstLight();			///Ge the light of the level

		~Level();		///Default destructor

		std::vector<Maze*> _MazeScene;		///Vector that contains the mazes

		int MazeSize;		///Number of mazes
	private:
		Visual::Light firstLight;		///Light for the first Room
	};

}