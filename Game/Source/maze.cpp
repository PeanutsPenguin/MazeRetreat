#include "maze.h"

namespace Game
{
	///Maze Ccnstructor
	Level::Maze::Maze(int Rows, int Columns)
	{
		///Stock a pointer to the solution in the heap memory
		this->solution = DBG_NEW doorNkey;  

		///Associate the right numbers
		this->nbrRows = Rows;
		this->nbrColumns = Columns;

		///Reserve enough space to stck the cells
		this->CellArray.resize(nbrRows);

		///Define width and height
		float height = 6;
		float width = 6;

		///For every Cell construct a Cell
		for (int i = 0; i < this->nbrRows; i++)
		{
			for (int j = 0; j < this->nbrColumns; j++)
			{
				this->CellArray[i].emplace_back(width, height);
			}
		}
	}

	///Cell constructor
	Level::Maze::Cell::Cell(float width, float height)
	{
		this->height = height;
		this->width = width;
	}

	///Set the position for a Cell
	void Level::Maze::Cell::SetPosition(LibMath::Vec3 position)
	{
		this->_cellPos = position;
	}

	///Get the position of a Cell
	LibMath::Vec3 Level::Maze::Cell::getPosition()
	{
		return this->_cellPos;
	}

	///Get the width of a Cell
	float Level::Maze::Cell::getWidth()
	{
		return this->width;
	}
	
	///Get the height of a Cell
	float Level::Maze::Cell::getHeight()
	{
		return this->height;
	}

	///Cell destructor
	Level::Maze::Cell::~Cell()
	{
		for(int i = 0; i < this->_cellwalls.size(); ++i)
		{
			delete this->_cellwalls[i];
		}
	}

	///Level constructor
	Level::Level(int nbrMaze, Resources::ResourcesManager& manager, int size)
	{
		this->recreateLevel(nbrMaze, manager, size);
	}

	///Level DEstructor
	Level::~Level()
	{
		for(int i = 0; i < this->_MazeScene.size(); ++i)
		{
			delete this->_MazeScene[i];
		}
	}

	///Function to recreate a level
	void Level::recreateLevel(int nbrMaze, Resources::ResourcesManager& manager, int size)
	{
		///Associate the size
		this->MazeSize = size;

		///Create the Model* for the level
		Resources::Model* floor = manager.CreateRessource<Resources::Model>("Assets/Meshes/floor.obj");
		Resources::Model* walls = manager.CreateRessource<Resources::Model>("Assets/Meshes/cube.obj");

		///Create the Texture* for the level
		Resources::Texture* wallTex = manager.CreateRessource<Resources::Texture>("Assets/Textures/WallTexture.png");
		Resources::Texture* GroundTex = manager.CreateRessource<Resources::Texture>("Assets/Textures/GroundTexture.png");
		Resources::Texture* CeilTex = manager.CreateRessource<Resources::Texture>("Assets/Textures/Ceiling.png");

		///For the number of mae wanted
		for (int i = 0; i < nbrMaze; ++i)
		{
			///Create a maze 
			this->_MazeScene.push_back(DBG_NEW Maze(this->MazeSize, this->MazeSize));

			///Get his index in our Maze array
			int index = this->_MazeScene.size() - 1;

			///Set the Models pointer in our maze
			this->_MazeScene[index]->setModel(1, floor);
			this->_MazeScene[index]->setModel(0, walls);

			///Set the texture pointers in our maze
			this->_MazeScene[index]->setTexture(0, wallTex);
			this->_MazeScene[index]->setTexture(1, GroundTex);
			this->_MazeScene[index]->setTexture(3, CeilTex);

			///Call the function to create the Maze and initialize it right
			this->_MazeScene[index]->create_Maze(LibMath::Vec3(i * (this->MazeSize * 6), 0, 0), i);

			this->_MazeScene[index]->createGrapples();

			///Create the solution for the maze just created
			this->_MazeScene[index]->createKeys(i, LibMath::Vec3(i * (this->MazeSize * 6), 0, 0));

			this->_MazeScene[index]->GrappleColor();
			
			///Find the position of the key
			LibMath::Vec3 pos = this->_MazeScene[index]->CellArray[this->_MazeScene[i]->getsolution()->boxIndex.first][this->_MazeScene[i]->getsolution()->boxIndex.second].getPosition();

			///Find the index of the key
			int BoxIndex = this->_MazeScene[index]->CellArray[this->_MazeScene[i]->getsolution()->boxIndex.first][this->_MazeScene[i]->getsolution()->boxIndex.second]._cellwalls.size() - 1;

			///Find the color of the key
			LibMath::Vec3 color = this->_MazeScene[index]->CellArray[this->_MazeScene[i]->getsolution()->boxIndex.first][this->_MazeScene[i]->getsolution()->boxIndex.second]._cellwalls[BoxIndex]->color;

			///Initialize a light in the cell where the key is and set the color to the key color
			this->_MazeScene[i]->keyLight.SetValues(pos, {0.4f, 0.4f, 0.4f}, color, {0.1f, 0.1, 0.1f}, {0, 0, 0}, {0, 0, 0}, 0.0f, 0.032f);
		}
		///Initialize a light in the first cell
		this->firstLight.SetValues(this->_MazeScene[0]->CellArray[0][0].getPosition(), { 0.4f, 0.4f, 0.4f }, { 1.0f, 1.0f, 1.0f }, { 0.1f, 0.1, 0.1f }, { 0, 0, 0 }, { 0, 0, 0 }, 0.0f, 0.032f);
	}

	Visual::Light Game::Level::getfirstLight()
	{
		return this->firstLight;
	}

	///Starter for creating the maze
	void Level::Maze::create_Maze(LibMath::Vec3 offset, int seed)
	{
		///Pair of int to keep track of the index
		std::vector<std::pair<int, int>> closeOne;

		closeOne.push_back(std::make_pair(0, 1));
		closeOne.push_back(std::make_pair(1, 0));

		///Take a random index
		srand(time(0));
		int indices = std::rand() % closeOne.size();

		if (indices == closeOne.size())
			indices--;

		///Random start 
		if (closeOne[indices].first == 1)
			CellArray[0][0].Up_Wall = false;
		else
			CellArray[0][0].Right_Wall = false;

		///First Cell has been visited
		CellArray[0][0].visited = true;

		///Call the recursive function to create a maze
		create_Maze_r(closeOne[indices].first, closeOne[indices].second, 0, seed);

		///Call the function to put the walls, floor, ect
		this->DrawMAze(offset, seed);
	}

	///Recursive function to vreate the maze
	void Level::Maze::create_Maze_r(int iIndex, int jIndex, int toRemove, int seed)
	{
		///Change the random seed
		srand(time(0));
		srand(rand() * iIndex - jIndex + seed);

		///Set the boolean to draw correctly the walls at the right place
		if (toRemove == 1)
			CellArray[iIndex][jIndex].Up_Wall = false;
		else if (toRemove == 2)
			CellArray[iIndex][jIndex].Right_Wall = false;

		///Cell has been visited
		CellArray[iIndex][jIndex].visited = true;

		///Vector of int pairs for the index
		std::vector<std::pair<int, int>> closeOne;

		///If the Cell on the left is existing and didn't have been visited yet keep the index
		if (jIndex - 1 >= 0 && !CellArray[iIndex][jIndex - 1].visited)
			closeOne.push_back(std::make_pair(iIndex, jIndex - 1));

		///If the Cell on the Right is existing and didn't have been visited yet keep the index
		if (iIndex + 1 < this->nbrColumns && !CellArray[iIndex + 1][jIndex].visited)
			closeOne.push_back(std::make_pair(iIndex + 1, jIndex));

		///If the Cell in front of us is existing and didn't have been visited yet keep the index
		if (jIndex + 1 < this->nbrRows && !CellArray[iIndex][jIndex + 1].visited)
			closeOne.push_back(std::make_pair(iIndex, jIndex + 1));

		///If the Cell behinf us is existing and didn't have been visited yet keep the index
		if (iIndex - 1 >= 0 && !CellArray[iIndex - 1][jIndex].visited)
			closeOne.push_back(std::make_pair(iIndex - 1, jIndex));

		///If we still have index
		if (!closeOne.empty())
		{
			int iteration = closeOne.size();

			///For all the index we have
			for (int i = 0; i < iteration; i++)
			{
				///Take a random number
				int indices = std::rand() % closeOne.size();

				///If the radom number is too big just -1
				if (indices == closeOne.size())
					indices--;

				///If the random index we had is in front of us, our upWall is set to false and we call back the function cause we're now on another cell
				if (closeOne[indices].first == iIndex + 1 && !CellArray[iIndex + 1][jIndex].visited)
				{
					CellArray[iIndex][jIndex].Up_Wall = false;
					create_Maze_r(closeOne[indices].first, closeOne[indices].second, 0, seed);
				}

				///If the random index we had is on our right, our RightWall is set to false and we call back the function cause we're now on another cell
				else if (closeOne[indices].second == jIndex + 1 && !CellArray[iIndex][jIndex + 1].visited)
				{
					CellArray[iIndex][jIndex].Right_Wall = false;
					create_Maze_r(closeOne[indices].first, closeOne[indices].second, 0, seed);
				}

				///If the random index we had is behind us  just call back the function because we're on another cell
				else if (closeOne[indices].first == iIndex - 1 && !CellArray[iIndex - 1][jIndex].visited)
				{
					create_Maze_r(closeOne[indices].first, closeOne[indices].second, 1, seed);
				}

				///If the random index we had is on our left just call back the function because we're on another cell
				else if (closeOne[indices].second == jIndex - 1 && !CellArray[iIndex][jIndex - 1].visited)
				{
					create_Maze_r(closeOne[indices].first, closeOne[indices].second, 2, seed);
				}

				///Get the iterator of our current index
				std::vector<std::pair<int, int>>::iterator it = (closeOne.begin() + indices);
				
				///Delete the index in the vector
				closeOne.erase(it);
			}

		}

	}

	void Level::Maze::createGrapples()
	{
		for(int iIndex = 0; iIndex < this->nbrRows; ++iIndex)
		{
			for(int jIndex = 0; jIndex < this->nbrColumns; ++jIndex)
			{
				if(iIndex >= 2)
				{
					if (this->checkLocationInX(iIndex, jIndex) && this->CellArray[iIndex][jIndex].Up_Wall)
					{
						///Insert the grappler in the Scene of the Node
						CellArray[iIndex][jIndex]._cellwalls.push_back(DBG_NEW Resources::SceneNode(this->wallModel, Resources::E_UP_GRAPPLE));

						///Find the index for this key
						int index = CellArray[iIndex][jIndex]._cellwalls.size() - 1;

						///Translate and scale the cube
						CellArray[iIndex][jIndex]._cellwalls[index]->local *= LibMath::Mat4::Translate(this->CellArray[iIndex][jIndex].getPosition());
						CellArray[iIndex][jIndex]._cellwalls[index]->local *= LibMath::Mat4::Scale(LibMath::Vec3(0.25, 0.25, 0.25));
						CellArray[iIndex][jIndex]._cellwalls[index]->local *= LibMath::Mat4::Translate({ 9, 3, 0 });

						///Update his bounding box
						CellArray[iIndex][jIndex]._cellwalls[index]->UpdateboundingBox();

						///Set his color to the radom color found earlier
						CellArray[iIndex][jIndex]._cellwalls[index]->color = LibMath::Vec4(1.0f, 0.0f, 0.0f, 1.0f);

						CellArray[iIndex][jIndex]._cellwalls[index]->Position = this->CellArray[iIndex][jIndex].getPosition();
					}
				}

				if (jIndex >= 2)
				{
					if (this->checkLocationInZ(iIndex, jIndex) && this->CellArray[iIndex][jIndex].Right_Wall)
					{
						///Insert the grappler in the Scene of the Node
						CellArray[iIndex][jIndex]._cellwalls.push_back(DBG_NEW Resources::SceneNode(this->wallModel, Resources::E_RIGHT_GRAPPLE));

						///Find the index for this key
						int index = CellArray[iIndex][jIndex]._cellwalls.size() - 1;

						///Translate and scale the cube
						CellArray[iIndex][jIndex]._cellwalls[index]->local *= LibMath::Mat4::Translate(this->CellArray[iIndex][jIndex].getPosition());
						CellArray[iIndex][jIndex]._cellwalls[index]->local *= LibMath::Mat4::Scale(LibMath::Vec3(0.25, 0.25, 0.25));
						CellArray[iIndex][jIndex]._cellwalls[index]->local *= LibMath::Mat4::Translate({ 0, 3, 9 });

						///Update his bounding box
						CellArray[iIndex][jIndex]._cellwalls[index]->UpdateboundingBox();

						///Set his color to the radom color found earlier
						CellArray[iIndex][jIndex]._cellwalls[index]->color = LibMath::Vec4(1.0f, 0.0f, 0.0f, 1.0f);

						CellArray[iIndex][jIndex]._cellwalls[index]->Position = this->CellArray[iIndex][jIndex].getPosition();
					}
				}
					
			}
		}
	}

	bool  Level::Maze::checkLocationInX(int iIndex, int Jindex)
	{
		for(int i = 1; i < 3; i++)
		{
			if (this->CellArray[iIndex - i][Jindex].Up_Wall)
				return false;
		}

		return true;
	}

	bool  Level::Maze::checkLocationInZ(int iIndex, int Jindex)
	{
		for (int i = 1; i < 3; i++)
		{
			if (this->CellArray[iIndex][Jindex - i].Right_Wall)
				return false;
		}

		return true;
	}

	///Create the solution for the maze
	void Level::Maze::createKeys(int seed, LibMath::Vec3 offset)
	{
		///Change the random seed
		srand(time(0));
		srand(rand() * seed);

		///Get a ramdom Row index + a random color
		int iIndex = std::rand() % this->nbrRows;
		float colorX = std::rand() % 100;
		
		///Change the random seed
		srand(rand() * (seed + 1));

		///Get a random Column index + a random color
		int jIndex = std::rand() % this->nbrColumns;
		float colorY = std::rand() % 100;

		///Change the random seed
		srand(rand() * (seed + 2));

		///Get a random color
		float colorZ = std::rand() % 100;

		///Keep the solution index
		this->solution->boxIndex.first = iIndex;
		this->solution->boxIndex.second = jIndex;

		///Change the random seed
		srand(time(0));
		srand(seed);

		///Find a random place for the door 
		int door = std::rand() % this->nbrColumns;

		///Keep the index of the solution
		this->solution->wallIndex.first = this->nbrRows - 1;
		this->solution->wallIndex.second = door;

		///Find the index for the scene
		int Secondindex = 0;
		if (this->CellArray[this->nbrRows - 1][door].Right_Wall == true)
			Secondindex = 1;

		///Destroy the texture for the wall and set it to the color of the key
		this->CellArray[this->nbrRows - 1][door]._cellwalls[Secondindex]->color = LibMath::Vec4(colorX / 100, colorY / 100, colorZ / 100, 0.8f);
		this->CellArray[this->nbrRows - 1][door]._cellwalls[Secondindex]->TexArray.clear();

		///If we're on the thirs maze create a special cell for the key
		if(seed == 2)
		{
			int Prevdoor = -1;

			///If the key is on the first Line we check where is the door of the previous maze
			if (iIndex == 0)
			{
				srand(time(0));
				srand(seed - 1);

				Prevdoor = std::rand() % this->nbrColumns;
			}
			
			///The special key can't spawn on a door 
			while (jIndex == Prevdoor || jIndex == door)
			{
				jIndex++;

				if (jIndex >= this->getNumberColumns())
					jIndex = 0;
			}
			
			this->solution->boxIndex.second = jIndex;
			this->CreateSpecialCell(iIndex, jIndex, LibMath::Vec3(colorX / 100, colorY /100, colorZ / 100), offset);
		}
		else
		{
			///Insert the key in the Scene of the Node
			CellArray[iIndex][jIndex]._cellwalls.push_back(DBG_NEW Resources::SceneNode(this->wallModel, Resources::E_KEY));

			///Find the index for this key
			int index = CellArray[iIndex][jIndex]._cellwalls.size() - 1;

			///Translate and scale the cube
			CellArray[iIndex][jIndex]._cellwalls[index]->local *= LibMath::Mat4::Translate(this->CellArray[iIndex][jIndex].getPosition());
			CellArray[iIndex][jIndex]._cellwalls[index]->local *= LibMath::Mat4::Scale(LibMath::Vec3(0.5, 0.5, 0.5));
			CellArray[iIndex][jIndex]._cellwalls[index]->local *= LibMath::Mat4::Translate({ 0, -1, 0 });

			///Update his bounding box
			CellArray[iIndex][jIndex]._cellwalls[index]->UpdateboundingBox();

			///Set his color to the radom color found earlier
			CellArray[iIndex][jIndex]._cellwalls[index]->color = LibMath::Vec4(colorX / 100, colorY / 100, colorZ / 100, 1.0f);
		}
	}

	void Level::Maze::GrappleColor()
	{
		for(int i = 0; i < this->nbrRows; ++i)
		{
			for(int j = 0; j < this->nbrColumns; ++j)
			{
				for(int k = 0; k < this->CellArray[i][j]._cellwalls.size(); ++k)
				{
					if (this->CellArray[i][j]._cellwalls[k]->getTag() == Resources::E_RIGHT_GRAPPLE || this->CellArray[i][j]._cellwalls[k]->getTag() == Resources::E_UP_GRAPPLE)
						this->CellArray[i][j]._cellwalls[k]->color = this->CellArray[this->solution->boxIndex.first][this->solution->boxIndex.second]._cellwalls[this->CellArray[this->solution->boxIndex.first][this->solution->boxIndex.second]._cellwalls.size() - 1]->color;
				}
			}
		}
	}
	///Set the Model
	void Level::Maze::setModel(int name, Resources::Model* Model)
	{
		if(name == 0)
			this->wallModel = Model;
		else if (name == 1)
			this->floorModel = Model;
	}

	///Create the special cell for the key
	void Level::Maze::CreateSpecialCell(int Iindex, int Jindex, LibMath::Vec4 color, LibMath::Vec3 offset)
	{
		///First we erase the current cell
		this->eraseCell(Iindex, Jindex);

		///Then we create a path around this cell
		this->createNewPath(Iindex, Jindex);

		///We create Four wall with a hole in the middle
		float x = (Iindex * this->getCellHeight()) + 3;
		float y = (Jindex + 1) * this->getCellWidth();

		this->CreateWall(Iindex, Jindex, offset, LibMath::Vec3(2.5, 3, 0.20), {x - 1.75f, 0, y});
			
		this->CreateWall(Iindex, Jindex, offset, LibMath::Vec3(2.5, 3, 0.20), {x + 1.75f, 0, y});

		this->CreateWall(Iindex, Jindex, offset, LibMath::Vec3(1, 1.40, 0.20), {x, 1, y});

		this->CreateWall(Iindex, Jindex, offset, LibMath::Vec3(1, 1.40, 0.20), {x, -0.75, y });

		x = (Iindex + 1) * this->getCellHeight();
		y = (Jindex * this->getCellWidth()) + 3;

		this->CreateWall(Iindex, Jindex, offset, LibMath::Vec3(0.20, 3, 2.5), {x , 0, y + 1.75f } );

		this->CreateWall(Iindex, Jindex, offset, LibMath::Vec3(0.20, 3, 2.5), { x, 0, y - 1.75f });

		this->CreateWall(Iindex, Jindex, offset, LibMath::Vec3(0.20, 1.40, 1), {x, 1, y});

		this->CreateWall(Iindex, Jindex, offset, LibMath::Vec3(0.20, 1.40, 1), {x, -0.75, y});

		x = (Iindex * this->getCellHeight()) + 3;
		y = (Jindex) * this->getCellWidth();

		this->CreateWall(Iindex, Jindex, offset, LibMath::Vec3(2.5, 3, 0.20), { x - 1.75f, 0, y });

		this->CreateWall(Iindex, Jindex, offset, LibMath::Vec3(2.5, 3, 0.20), { x + 1.75f, 0, y });

		this->CreateWall(Iindex, Jindex, offset, LibMath::Vec3(1, 1.40, 0.20), { x, 1, y });

		this->CreateWall(Iindex, Jindex, offset, LibMath::Vec3(1, 1.40, 0.20), { x, -0.75, y });

		x = Iindex * this->getCellHeight();
		y = (Jindex * this->getCellWidth()) + 3;

		this->CreateWall(Iindex, Jindex, offset, LibMath::Vec3(0.20, 3, 2.5), { x , 0, y + 1.75f });

		this->CreateWall(Iindex, Jindex, offset, LibMath::Vec3(0.20, 3, 2.5), { x, 0, y - 1.75f });

		this->CreateWall(Iindex, Jindex, offset, LibMath::Vec3(0.20, 1.40, 1), { x, 1, y });

		this->CreateWall(Iindex, Jindex, offset, LibMath::Vec3(0.20, 1.40, 1), { x, -0.75, y });

		///Then we insert the key
		CellArray[Iindex][Jindex]._cellwalls.push_back(DBG_NEW Resources::SceneNode(this->wallModel, Resources::E_KEY));

		int index = CellArray[Iindex][Jindex]._cellwalls.size() - 1;

		///Translate and scale the cube
		CellArray[Iindex][Jindex]._cellwalls[index]->local *= LibMath::Mat4::Translate(this->CellArray[Iindex][Jindex].getPosition());
		CellArray[Iindex][Jindex]._cellwalls[index]->local *= LibMath::Mat4::Scale(LibMath::Vec3(0.5, 0.5, 0.5));

		///Create a target for the key
		this->solution->target = CellArray[Iindex][Jindex]._cellwalls[index]->local.m_transform * LibMath::Mat4::Translate({ 0, 1, 0 });

		///Translate the cube a second time so he is in the bottom
		CellArray[Iindex][Jindex]._cellwalls[index]->local *= LibMath::Mat4::Translate({ 0, -1, 0 });

		///Create the other target for the key
		this->solution->Secondtarget = CellArray[Iindex][Jindex]._cellwalls[index]->local.m_transform;

		///Update his bounding box
		CellArray[Iindex][Jindex]._cellwalls[index]->UpdateboundingBox();
		CellArray[Iindex][Jindex]._cellwalls[index]->color = color;
	}

	///Function to create a wall
	void Level::Maze::CreateWall(int i, int j, LibMath::Vec3 offset, LibMath::Vec3 Scaler, LibMath::Vec3 Position)
	{
		LibMath::Vec4 WallColor(0.8f, 0.9f, 0.6f, 1.0f);

		///Insert a wall with his texture
		CellArray[i][j]._cellwalls.push_back(DBG_NEW Resources::SceneNode(this->wallModel, this->wallTexture, Resources::E_WALL));

		///Find the index in the scene
		int index = CellArray[i][j]._cellwalls.size() - 1;

		///Translate and scale the wall at the right place
		CellArray[i][j]._cellwalls[index]->local *= LibMath::Mat4::Translate(LibMath::Vec3(Position.x + offset.x, Position.y + offset.y, Position.z + offset.z));
		CellArray[i][j]._cellwalls[index]->local *= LibMath::Mat4::Scale(Scaler);

		///Update the bouding box of the wall
		CellArray[i][j]._cellwalls[index]->UpdateboundingBox();

		///Set the color of the wall to the color define before
		CellArray[i][j]._cellwalls[index]->color = WallColor;
	}

	///Set the Texture
	void Level::Maze::setTexture(int name, Resources::Texture* texture)
	{
		switch (name)
		{
		case 0:
			this->wallTexture = texture;
			break;
		case 1:
			this->GroundTexture = texture;
			break;
		case 3:
			this->CellingTexture = texture;
			break;
		default:
			break;
		}
	}

	///Function to erase a cell
	void Level::Maze::eraseCell(int Iindex, int Jindex)
	{
		///Create an iterator of the current cell
		std::vector<Resources::SceneNode*>::iterator it = this->CellArray[Iindex][Jindex]._cellwalls.begin();

		if(Jindex < this->nbrColumns)
		{
			///If the is a right wall delete it
			if (this->CellArray[Iindex][Jindex].Right_Wall)
			{
				delete this->CellArray[Iindex][Jindex]._cellwalls[0];
				this->CellArray[Iindex][Jindex]._cellwalls.erase(it);
				this->CellArray[Iindex][Jindex].Right_Wall = false;
			}
				
		}
		
		if(Iindex < this->nbrRows)
		{
			std::vector<Resources::SceneNode*>::iterator it4 = this->CellArray[Iindex][Jindex]._cellwalls.begin();

			///If the is an Up wall delete it
			if (this->CellArray[Iindex][Jindex].Up_Wall)
			{
				delete this->CellArray[Iindex][Jindex]._cellwalls[0];
				this->CellArray[Iindex][Jindex]._cellwalls.erase(it4);
				this->CellArray[Iindex][Jindex].Up_Wall = false;
			}
				
		}

		///If anything is still in the cell, erase it
		int SizeOfCell = this->CellArray[Iindex][Jindex]._cellwalls.size();

		if (SizeOfCell > 1)
		{
			for(int i = 1; i < SizeOfCell; ++i)
			{
				std::vector<Resources::SceneNode*>::iterator it4 = this->CellArray[Iindex][Jindex]._cellwalls.begin();
				delete this->CellArray[Iindex][Jindex]._cellwalls[0];
				this->CellArray[Iindex][Jindex]._cellwalls.erase(it4);
			}
		}
		
		if (Jindex > 0)
		{
			std::vector<Resources::SceneNode*>::iterator it2 = this->CellArray[Iindex][Jindex - 1]._cellwalls.begin();

			///If the is a right wall on the left cell delete it
			if (this->CellArray[Iindex][Jindex - 1].Right_Wall && Jindex - 1 >= 0)
			{
				delete this->CellArray[Iindex][Jindex - 1]._cellwalls[0];
				this->CellArray[Iindex][Jindex - 1]._cellwalls.erase(it2);
				this->CellArray[Iindex][Jindex - 1].Right_Wall = false;
			}
		}

		if (Iindex > 0)
		{
			std::vector<Resources::SceneNode*>::iterator it3 = this->CellArray[Iindex - 1][Jindex]._cellwalls.begin();

			///If the is an Up wall on the cell behind delete it
			if (this->CellArray[Iindex - 1][Jindex].Up_Wall && this->CellArray[Iindex - 1][Jindex].Right_Wall && Iindex - 1 >= 0)
			{
				delete this->CellArray[Iindex - 1][Jindex]._cellwalls[1];
				this->CellArray[Iindex - 1][Jindex]._cellwalls.erase(++it3);
				this->CellArray[Iindex - 1][Jindex].Up_Wall = false;
			}
			else if (this->CellArray[Iindex - 1][Jindex].Up_Wall && Iindex - 1 >= 0)
			{
				delete this->CellArray[Iindex - 1][Jindex]._cellwalls[0];
				this->CellArray[Iindex - 1][Jindex]._cellwalls.erase(it3);
				this->CellArray[Iindex - 1][Jindex].Up_Wall = false;
			}
		}
	}

	///Get the model pointer
	Resources::Model* Level::Maze::getModel()
	{
		return this->wallModel;
	}

	///Function to create a new path
	void Level::Maze::createNewPath(int Iindex, int Jindex)
	{
		///Erase the upWall on the left cell if we're not at the end of the maze and not on the leftest side
		if(Jindex -  1 >= 0)
		{
			if (Iindex + 1 < this->nbrRows && this->CellArray[Iindex][Jindex - 1].Up_Wall)
			{
				std::vector<Resources::SceneNode*>::iterator it = this->CellArray[Iindex][Jindex - 1]._cellwalls.begin();

				if (this->CellArray[Iindex][Jindex - 1].Right_Wall)
				{
					it += 1;
					delete this->CellArray[Iindex][Jindex - 1]._cellwalls[1];
				}
				else 
					delete this->CellArray[Iindex][Jindex - 1]._cellwalls[0];
				
				this->CellArray[Iindex][Jindex - 1].Up_Wall = false;
				this->CellArray[Iindex][Jindex - 1]._cellwalls.erase(it);
			}
		}

		///Erase the upWall on the right cell if we're not at the end of the maze and not on the rightest side
		if (Jindex + 1 < this->nbrColumns)
		{
			if (Iindex != this->nbrRows - 1 && this->CellArray[Iindex][Jindex + 1].Up_Wall)
			{
				std::vector<Resources::SceneNode*>::iterator it = this->CellArray[Iindex][Jindex + 1]._cellwalls.begin();

				if (this->CellArray[Iindex][Jindex + 1].Right_Wall)
				{
					it += 1;
					delete this->CellArray[Iindex][Jindex + 1]._cellwalls[1];
				}
				else 
					delete this->CellArray[Iindex][Jindex + 1]._cellwalls[0];
					
				this->CellArray[Iindex][Jindex + 1].Up_Wall = false;
				this->CellArray[Iindex][Jindex + 1]._cellwalls.erase(it);
			}
		}
		else if (Jindex == this->nbrColumns - 1 && Iindex - 1 >= 0)
		{
			if (Iindex != this->nbrRows - 1 && this->CellArray[Iindex - 1][Jindex - 1].Up_Wall)
			{
				std::vector<Resources::SceneNode*>::iterator it = this->CellArray[Iindex - 1][Jindex - 1]._cellwalls.begin();

				if (this->CellArray[Iindex - 1][Jindex - 1].Right_Wall)
				{
					it += 1;	
					delete this->CellArray[Iindex - 1][Jindex - 1]._cellwalls[1];
				}
				else
					delete this->CellArray[Iindex - 1][Jindex - 1]._cellwalls[0];


				this->CellArray[Iindex - 1][Jindex - 1].Up_Wall = false;
				this->CellArray[Iindex - 1][Jindex - 1]._cellwalls.erase(it);
			}
		}

		if(Iindex - 1 >= 0)
		{
			if (Jindex < this->nbrColumns - 1 && this->CellArray[Iindex - 1][Jindex].Right_Wall)
			{
				std::vector<Resources::SceneNode*>::iterator it = this->CellArray[Iindex - 1][Jindex]._cellwalls.begin();

				this->CellArray[Iindex - 1][Jindex].Right_Wall = false;
				delete this->CellArray[Iindex - 1][Jindex]._cellwalls[0];
				this->CellArray[Iindex - 1][Jindex]._cellwalls.erase(it);
			}
		}
		
		if (Iindex + 1 < this->nbrRows)
		{
			if (Jindex < this->nbrColumns - 1 && this->CellArray[Iindex + 1][Jindex].Right_Wall)
			{
				std::vector<Resources::SceneNode*>::iterator it = this->CellArray[Iindex + 1][Jindex]._cellwalls.begin();

				this->CellArray[Iindex + 1][Jindex].Right_Wall = false;
				delete this->CellArray[Iindex + 1][Jindex]._cellwalls[0];
				this->CellArray[Iindex + 1][Jindex]._cellwalls.erase(it);
			}
		}

		if (Iindex - 1 >= 0 && Jindex - 1 >= 0)
		{
			if (this->CellArray[Iindex - 1][Jindex - 1].Right_Wall)
			{
				std::vector<Resources::SceneNode*>::iterator it = this->CellArray[Iindex - 1][Jindex - 1]._cellwalls.begin();

				this->CellArray[Iindex - 1][Jindex - 1].Right_Wall = false;
				delete this->CellArray[Iindex - 1][Jindex - 1]._cellwalls[0];
				this->CellArray[Iindex - 1][Jindex - 1]._cellwalls.erase(it);
			}
		}
		
	}

	///Place the maze's wall ect
	void Level::Maze::DrawMAze(LibMath::Vec3 offset, int seed)
	{
		///gET THE RIGHT SEED FOR THE RANDOM NUMBER
		srand(time(0));
		srand((seed - 1));

		///This will get the index of the previous door solution
		int backDoor = std::rand() % this->nbrColumns;

		///If we're on the first maze there's no previous solution
		if (seed == 0)
			backDoor = 100;

		///Define the wall color 
		

		for (int i = 0; i < this->nbrRows; i++)
		{
			for (int j = 0; j < this->nbrColumns; j++)
			{
				///If we have a right Wall
				if (CellArray[i][j].Right_Wall)
				{
					///Find the right x and z
					float x = (i * this->getCellHeight()) + 3;
					float y = (j + 1) * this->getCellWidth();

					this->CreateWall(i, j, offset, LibMath::Vec3(6, 3, 0.20), {x, 0, y});
				}

				///If we have an Up Wall
				if (CellArray[i][j].Up_Wall)
				{
					///Find the right x and z
					float x = (i + 1) * this->getCellHeight();
					float y = (j * this->getCellWidth()) + 3;

					this->CreateWall(i, j, offset, { 0.20, 3, 6 }, { x, 0, y });

				}

				///If we're on the first column
				if(j == 0)
				{
					///Find the right x and z
					float x = (i * this->getCellHeight()) + 3;
					float y = 0;

					this->CreateWall(i, j, offset, { 6, 3, 0.20 }, { x, 0, y });
				}

				///If we're on the first line
				if (i == 0 && j != backDoor)
				{
					///Find the right x and z
					float x = 0;
					float y = (j * this->getCellWidth()) + 3;

					this->CreateWall(i, j, offset, { 0.20, 3, 6 }, { x, 0, y });
				}

				///Find the position for the floor
				float groundX = (i * this->getCellWidth()) + offset.x + (this->getCellWidth() / 2);
				float groundY = (j * this->getCellHeight()) + offset.z + (this->getCellHeight() / 2);

				///Set the right position for the floor
				CellArray[i][j].SetPosition({ groundX, 0 + offset.y, groundY });

				///Insert the celling in the scene
				CellArray[i][j]._cellwalls.push_back(DBG_NEW Resources::SceneNode(this->floorModel, this->CellingTexture, Resources::E_CEILING));

				///Find the index in the scene
				int Cellingindex = CellArray[i][j]._cellwalls.size() - 1;

				///Translate and scale at the right position
				CellArray[i][j]._cellwalls[Cellingindex]->local *= LibMath::Mat4::Translate(LibMath::Vec3(groundX, offset.y + 0.5, groundY));
				CellArray[i][j]._cellwalls[Cellingindex]->local *= LibMath::Mat4::Scale(LibMath::Vec3(3, 1, 3));
				CellArray[i][j]._cellwalls[Cellingindex]->local *= LibMath::Mat4::Rotate(LibMath::Vec3(3.14, 0, 0));

				///Set the right Color
				CellArray[i][j]._cellwalls[Cellingindex]->color = { .5f, .5f, .5f, 1.0f };

				CellArray[i][j]._cellwalls[Cellingindex]->UpdateboundingBox();
			}

			CellArray[0][0]._cellwalls.push_back(DBG_NEW Resources::SceneNode(this->floorModel, this->GroundTexture, Resources::E_GROUND));
			int index = CellArray[0][0]._cellwalls.size() - 1;

			CellArray[0][0]._cellwalls[index]->local *= LibMath::Mat4::Translate({3 * this->nbrRows + offset.x, 0 + offset.y, 3 * this->nbrColumns + offset.z});

			CellArray[0][0]._cellwalls[index]->local *= LibMath::Mat4::Scale(LibMath::Vec3(3 * this->nbrRows, 1, 3 * this->nbrColumns));

			CellArray[0][0]._cellwalls[index]->color = { 0.8f, 0.9f, 0.4f, 1.0f };

			CellArray[0][0]._cellwalls[index]->UpdateboundingBox();
		}
	}
	
	///Function to move a key from a target to another
	void Level::Maze::moveKeys(const LibMath::Mat4& mvp, Rendering::Application& screen)
	{
		int Keyindex = CellArray[this->solution->boxIndex.first][this->solution->boxIndex.second]._cellwalls.size() - 1;

		///If our target is the first one
		if(this->solution->TargetFirst)
		{
			///We check the Translate number of the matrix if we're at destination we change target ele we move
			if(this->CellArray[this->solution->boxIndex.first][this->solution->boxIndex.second]._cellwalls[Keyindex]->local.m_transform[3][1] <= this->solution->Secondtarget[3][1])
			{
				this->solution->TargetFirst = false;
				this->CellArray[this->solution->boxIndex.first][this->solution->boxIndex.second]._cellwalls[Keyindex]->local *= LibMath::Mat4::Translate({ 0, (float)0.3 * screen.getDeltaTime(), 0 });
			}
			else 
				this->CellArray[this->solution->boxIndex.first][this->solution->boxIndex.second]._cellwalls[Keyindex]->local *= LibMath::Mat4::Translate({ 0, (float)-0.3 * screen.getDeltaTime(), 0 });
		}
		///same with the second target
		else if (!this->solution->TargetFirst)
		{
			if (this->CellArray[this->solution->boxIndex.first][this->solution->boxIndex.second]._cellwalls[Keyindex]->local.m_transform[3][1] >= this->solution->target[3][1])
			{
				this->solution->TargetFirst = true;
				this->CellArray[this->solution->boxIndex.first][this->solution->boxIndex.second]._cellwalls[Keyindex]->local *= LibMath::Mat4::Translate({ 0,(float)-0.3 * screen.getDeltaTime(), 0 });
			}
			else
				this->CellArray[this->solution->boxIndex.first][this->solution->boxIndex.second]._cellwalls[Keyindex]->local *= LibMath::Mat4::Translate({ 0,(float)0.3 * screen.getDeltaTime(), 0 });
		}
	}
	
	///Get the cell Width
	float Level::Maze::getCellWidth()
	{
		return this->CellArray[0][0].getWidth();
	}

	///Get the cell Height
	float Level::Maze::getCellHeight()
	{
		return this->CellArray[0][0].getHeight();
	}

	///Get the number of Rows
	int Level::Maze::getNumberRows()
	{
		return this->nbrRows;
	}
	
	///Get the number of Columns
	int Level::Maze::getNumberColumns()
	{
		return this->nbrColumns;
	}
	
	///Get the solution
	Level::Maze::doorNkey* Level::Maze::getsolution()
	{
		return this->solution;
	}

	///Destructor of maze
	Level::Maze::~Maze()
	{
		delete this->solution;
	}

}