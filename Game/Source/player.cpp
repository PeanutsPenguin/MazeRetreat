#include "Player.h"


namespace Game
{
	///Function to update evrything in the player
	void Player::PlayerUpdate(Rendering::Application& screen, Game::Level& mazes, Sound::SoundEngine& engine, Resources::Shader& myShader)
	{
		///Increase our CoolDown every frame
		this->coolDownm += screen.getDeltaTime();

		///Reset the boolean is Over Sqaure of our crosshair
		this->Crosshair->isOverSquare = false;

		///Check the inputs
		this->PlayerInputHandler(screen.screen, screen, engine);

		this->UpdatePlayerCulling(this->Position, mazes);

		this->inCullingBox = this->CullingBoxSelect(mazes);

		///Check the collisions
		this->CollisionPlayer(screen);

		///Update our movements
		this->updateMovement(screen, mazes);

		///Render and update our Torch Light
		this->torchlight.UpdateSpotLight(this->Position, this->_playerView->Front);
		this->torchlight.renderSpot(myShader, this->isSpotLightOn);

		///Find wich object is closer to us
		this->compare(this->inFieldOfView());	

		///Associate the player color and the phone color
		this->Phone->color = this->color;

		///Render the crosshair
		this->Crosshair->drawCrosshair();

		///Check if our color is equal to the current door and if so, make the door transperent
		for (int i = 0; i < mazes._MazeScene.size(); ++i)
		{
			int index = 0;

			if (mazes._MazeScene[i]->CellArray[mazes._MazeScene[i]->getsolution()->wallIndex.first][mazes._MazeScene[i]->getsolution()->wallIndex.second].Right_Wall)
				index += 1;

			LibMath::Vec3 tempWallcolor = mazes._MazeScene[i]->CellArray[mazes._MazeScene[i]->getsolution()->wallIndex.first][mazes._MazeScene[i]->getsolution()->wallIndex.second]._cellwalls[index]->color;
			LibMath::Vec3 tempPlqyerColor = this->color;

			if (tempWallcolor == tempPlqyerColor)
				mazes._MazeScene[i]->CellArray[mazes._MazeScene[i]->getsolution()->wallIndex.first][mazes._MazeScene[i]->getsolution()->wallIndex.second]._cellwalls[index]->color.a = 0.1f;
			else
				mazes._MazeScene[i]->CellArray[mazes._MazeScene[i]->getsolution()->wallIndex.first][mazes._MazeScene[i]->getsolution()->wallIndex.second]._cellwalls[index]->color.a = 0.8f;
		}
	}

	///Function to update the player movement
	void Player::updateMovement(Rendering::Application& screen, Game::Level& mazes)
	{
		///If we jump to high, let us fall
		if (this->Position.y >= 2)
		{
			this->grounded = false;
			this->Velocity.y = 0;
		}

		///If we're at the end of the level, fall down
		if(this->Position.x < mazes.MazeSize * mazes._MazeScene[0]->getCellHeight() * mazes._MazeScene.size())
		{
			this->isChangingLevel = false;

			if (this->Position.y <= 0)
			{
				this->Position.y = 0;
				this->grounded = true;
			}
		}
		else
		{
			this->isChangingLevel = true;
			this->grounded = false;
			this->Velocity -= this->GetGravity();
			this->Velocity.x += 0.1;
		}
		
		///Update the camera position
		this->_playerView->Position = this->Position;

		///Update the camera
		this->_playerView->CameraUpdate();
	}

	///Function to handle the keybords input of the player
	void Player::PlayerInputHandler(GLFWwindow* window, Rendering::Application& screen, Sound::SoundEngine& engine)
	{
		///If we're grounded check those inputs
		if(this->grounded)
		{
			///Reset the velocity
			this->Velocity.z = 0;
			this->Velocity.x = 0;

			bool isMoving = false;

			///Input WASD to go in every direction
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			{
				///Playing walkSound if we move
				if (!engine.engine->isCurrentlyPlaying(engine.walkSound))
					engine.engine->play2D(engine.walkSound);

				isMoving = true;
				///Move the velocity depending on the input
				this->Velocity.z += (this->forward.z * _playerView->movementSpeed) * 1;
				this->Velocity.x += (this->forward.x * _playerView->movementSpeed) * 1;
			}
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			{
				if (!engine.engine->isCurrentlyPlaying(engine.walkSound))
					engine.engine->play2D(engine.walkSound);

				isMoving = true;
				this->Velocity.z += (this->forward.z * _playerView->movementSpeed) * -1;
				this->Velocity.x += (this->forward.x * _playerView->movementSpeed) * -1;
			}
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			{
				if (!engine.engine->isCurrentlyPlaying(engine.walkSound))
					engine.engine->play2D(engine.walkSound);

				isMoving = true;

				LibMath::Vec3 move = LibMath::Vec3::Normalize(LibMath::Vec3::Cross(this->forward, LibMath::Vec3::Up()));

				this->Velocity.z += move.z * _playerView->movementSpeed * -1;
				this->Velocity.x += move.x * _playerView->movementSpeed * -1;
			}
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			{
				if (!engine.engine->isCurrentlyPlaying(engine.walkSound))
					engine.engine->play2D(engine.walkSound);
				
				isMoving = true;

				LibMath::Vec3 move = LibMath::Vec3::Normalize(LibMath::Vec3::Cross(this->forward, LibMath::Vec3::Up()));

				this->Velocity.z += move.z * _playerView->movementSpeed * 1;
				this->Velocity.x += move.x * _playerView->movementSpeed * 1;
			}

			///If we press shift we speed up
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
				this->_playerView->movementSpeed = 8.f;
			else
				this->_playerView->movementSpeed = 5.f;

			///If we press B turn on the Torch Light
			if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && this->coolDownm > 0.5f)
			{
				engine.engine->play2D(engine.torchLight);
				this->isSpotLightOn = !this->isSpotLightOn;
				this->coolDownm = 0; 
			}

			///If we press space then jump
			if ((glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) && this->grounded)
			{
				this->Velocity.y = 4;
				this->grounded = false;

				if (engine.engine->isCurrentlyPlaying(engine.walkSound))
					engine.engine->stopAllSoundsOfSoundSource(engine.walkSound);
			}

			///If we're not moving stop the walking sound
			if(!isMoving)
			{
				if(engine.engine->isCurrentlyPlaying(engine.walkSound))
					engine.engine->stopAllSoundsOfSoundSource(engine.walkSound);
			}
		}

		///If we're not grounded apply gravity
		else if (!this->grounded)
		{
			this->Velocity.y -= this->GetGravity();
		}

		///Change the forward vector depending on the camera input
		this->forward.x = LibMath::cos(this->_playerView->yaw);
		this->forward.y = 0;
		this->forward.z = LibMath::sin(this->_playerView->yaw);

		this->forward = LibMath::Vec3::Normalize(this->forward);
	}

	///Function to get what is in our field of view
	std::vector<Resources::SceneNode*> Player::inFieldOfView()
	{
		std::vector<Resources::SceneNode*> result;

		for(int index = 0; index < this->inCullingBox.size(); ++index)
		{
			for (int nbrVertex = 0; nbrVertex < this->inCullingBox[index]->getModel()->vertexBuffer.size(); ++nbrVertex)
			{
				///For every vertex in the level check if it is in an angle of 60 degres in front of us and at a distance of 0 to 12 from us, if so push back the object in the vector
				LibMath::Vec4 converted = (LibMath::Vec4(this->inCullingBox[index]->getModel()->vertexBuffer[nbrVertex].position) * this->inCullingBox[index]->local.m_transform);
				LibMath::Degree angle = LibMath::Vec3::Angle(this->Position - converted, this->_playerView->Front);

				if (angle > 120_deg)
				{
					result.push_back(this->inCullingBox[index]);
					break;
				}	
			}
		}

		return result;
	}

	///Function to compare wich object is closer
	Resources::SceneNode* Player::compare(std::vector<Resources::SceneNode*> object)
	{
		std::pair<float, Resources::SceneNode*> result;
		result.first = std::numeric_limits<float>::infinity();
		result.second = nullptr;

		///For every object in the vector, check if there is a collision and check the distance of it
		for (int i = 0; i < object.size(); ++i)
		{
			float distance = Collision::RaytoAAB(object[i], this->getPlayerCam());

			if (distance == -1)
				continue;

			if (result.first > distance)
			{
				result.first = distance;
				result.second = object[i];
			}
		}

		///For the nearest object, set his boolean reachable to true
		if (result.second != nullptr)
		{
			if ((result.second->getTag() == Resources::E_KEY) || (result.second->getTag() == Resources::E_RIGHT_GRAPPLE) || (result.second->getTag() == Resources::E_UP_GRAPPLE))
			{
				result.second->reachable = true;
				this->Crosshair->isOverSquare = true;
			}
			return result.second;
		}
		else
			return nullptr;
	}

	///Get the camera
	Visual::Camera* Player::getPlayerCam()
	{
		return this->_playerView;
	}

	///Set our player Crosshair
	void Player::SetPlayerCrosshair(Game::Crosshair* Crosshair)
	{
		this->Crosshair = Crosshair;
	}

	///Set our Phone
	void Player::SetPlayerPhone(Game::Phone* phone)
	{
		this->Phone = phone;
	}

	///Function to check the collision with the level
	void Player::CollisionPlayer(Rendering::Application& screen)
	{
		LibMath::Vec3 futurPos = this->Position + this->Velocity * screen.getDeltaTime();
		LibMath::Vec3 tempPlayerColor = this->color;

		bool hasCollided = false;

		this->UpdatePlayerBox(futurPos);

		for(int index = 0; index < this->inCullingBox.size(); ++index)
		{
			LibMath::Vec3 tempWallcolor = this->inCullingBox[index]->color;

			///If the wall has the color of the phone don't check the collision
			if (tempWallcolor == tempPlayerColor)
				continue;

			///If there is a collision
			if (Collision::AABBtoAABB(*this->GetBoundingBox(), *this->inCullingBox[index]->GetBoundingBox()))
			{
				hasCollided = true;

				LibMath::Vec3 PrevPos = this->Position;
				LibMath::Vec3 result;

				///Update our boundin box like we moved in x
				this->UpdatePlayerBox(LibMath::Vec3(futurPos.x, PrevPos.y, PrevPos.z));

				///If there is a collision don't move else you can move
				if (Collision::AABBtoAABB(*this->GetBoundingBox(), *this->inCullingBox[index]->GetBoundingBox()))
				{
					result.x = PrevPos.x;
				}
				else
				{
					result.x = futurPos.x;
				}

				///same in z
				this->UpdatePlayerBox(LibMath::Vec3(PrevPos.x, PrevPos.y, futurPos.z));

				if (Collision::AABBtoAABB(*this->GetBoundingBox(), *this->inCullingBox[index]->GetBoundingBox()))
				{
					result.z = PrevPos.z;
				}
				else
				{
					result.z = futurPos.z;
				}

				result.y = futurPos.y;
				this->Position = result;
			}
		}


		///If we don't have collision with anything just move normally
		if (!hasCollided)
			this->Position = futurPos;
	}

	///Function to check what we have to render
	std::vector<Resources::SceneNode*> Player::CullingBoxSelect(Level& level)
	{
		std::vector<Resources::SceneNode*> result;
		
		///Check the collision with every object int the maze and our culling box
		for (int mazesIndex = 0; mazesIndex < level._MazeScene.size(); ++mazesIndex)
		{
			for (int cellRowIndex = 0; cellRowIndex < level._MazeScene[mazesIndex]->getNumberRows(); ++cellRowIndex)
			{
				for (int cellColumnIndex = 0; cellColumnIndex < level._MazeScene[mazesIndex]->getNumberColumns(); ++cellColumnIndex)
				{
					for (int nbrMesh = 0; nbrMesh < level._MazeScene[mazesIndex]->CellArray[cellRowIndex][cellColumnIndex]._cellwalls.size(); ++nbrMesh)
					{
						int wallIndex = 0;

						if (level._MazeScene[mazesIndex]->CellArray[level._MazeScene[mazesIndex]->getsolution()->wallIndex.first][level._MazeScene[mazesIndex]->getsolution()->wallIndex.second].Right_Wall)
							wallIndex += 1;

						if (cellRowIndex == level._MazeScene[mazesIndex]->getsolution()->wallIndex.first && cellColumnIndex == level._MazeScene[mazesIndex]->getsolution()->wallIndex.second && nbrMesh == wallIndex)
							continue;

						///Push back in our vector the object if there is a collision
						if (Collision::AABBtoAABB(*this->CubeCulling, *level._MazeScene[mazesIndex]->CellArray[cellRowIndex][cellColumnIndex]._cellwalls[nbrMesh]->GetBoundingBox()))
						{
							result.push_back(level._MazeScene[mazesIndex]->CellArray[cellRowIndex][cellColumnIndex]._cellwalls[nbrMesh]);
						}
					}
				}
			}
		}
		
		///Add the transparent door in the vector
		for (int i = level._MazeScene.size() - 1; i >= 0; --i)
		{
			int index = 0;

			if (level._MazeScene[i]->CellArray[level._MazeScene[i]->getsolution()->wallIndex.first][level._MazeScene[i]->getsolution()->wallIndex.second].Right_Wall)
				index += 1;

			result.push_back(level._MazeScene[i]->CellArray[level._MazeScene[i]->getsolution()->wallIndex.first][level._MazeScene[i]->getsolution()->wallIndex.second]._cellwalls[index]);
		}

		return result;
	}

	///Function to update our BoundingBox
	void Player::UpdatePlayerBox(LibMath::Vec3 position)
	{
		std::vector<LibMath::Vec3> NewPosition;

		///Create a bounding box with our position and a 0.25 square
		NewPosition.push_back(position + LibMath::Vec3(-0.25f, 0, -0.25f));
		NewPosition.push_back(position + LibMath::Vec3(0.25f, 0, -0.25f));
		NewPosition.push_back(position + LibMath::Vec3(-0.25f, 0, 0.25f));
		NewPosition.push_back(position + LibMath::Vec3(0.25f, 0, 0.25f));
		NewPosition.push_back(position + LibMath::Vec3(-0.25f, 0.5f, -0.25f));
		NewPosition.push_back(position + LibMath::Vec3(0.25f, 0.5f, -0.25f));
		NewPosition.push_back(position + LibMath::Vec3(-0.25f, 0.5f, 0.25f));
		NewPosition.push_back(position + LibMath::Vec3(0.25f, 0.5f, 0.25f));

		this->GetBoundingBox()->MaxPos = Collision::getVectorMax(NewPosition);
		this->GetBoundingBox()->MinPos = Collision::getVectorMin(NewPosition);
	}
	
	///Function ot update our Culling Box
	void Player::UpdatePlayerCulling(LibMath::Vec3 position, Level& mazes)
	{
		std::vector<LibMath::Vec3> NewPosition;

		///Create a bounding box with our position and a size of a maze square
		NewPosition.push_back(position + LibMath::Vec3(-mazes._MazeScene[0]->getCellWidth() * mazes.MazeSize, -2, -mazes._MazeScene[0]->getCellHeight() * mazes.MazeSize));
		NewPosition.push_back(position + LibMath::Vec3(mazes._MazeScene[0]->getCellWidth() * mazes.MazeSize, -2, -mazes._MazeScene[0]->getCellHeight() * mazes.MazeSize));
		NewPosition.push_back(position + LibMath::Vec3(-mazes._MazeScene[0]->getCellWidth() * mazes.MazeSize, -2, mazes._MazeScene[0]->getCellHeight() * mazes.MazeSize));
		NewPosition.push_back(position + LibMath::Vec3(mazes._MazeScene[0]->getCellWidth() * mazes.MazeSize, -2, mazes._MazeScene[0]->getCellHeight() * mazes.MazeSize));
		NewPosition.push_back(position + LibMath::Vec3(-mazes._MazeScene[0]->getCellWidth() * mazes.MazeSize, 3.f, -mazes._MazeScene[0]->getCellHeight() * mazes.MazeSize));
		NewPosition.push_back(position + LibMath::Vec3(mazes._MazeScene[0]->getCellWidth() * mazes.MazeSize, 3.f, -mazes._MazeScene[0]->getCellHeight() * mazes.MazeSize));
		NewPosition.push_back(position + LibMath::Vec3(-mazes._MazeScene[0]->getCellWidth() * mazes.MazeSize, 3.f, mazes._MazeScene[0]->getCellHeight() * mazes.MazeSize));
		NewPosition.push_back(position + LibMath::Vec3(mazes._MazeScene[0]->getCellWidth() * mazes.MazeSize, 3.f, mazes._MazeScene[0]->getCellHeight() * mazes.MazeSize));

		this->CubeCulling->MaxPos = Collision::getVectorMax(NewPosition);
		this->CubeCulling->MinPos = Collision::getVectorMin(NewPosition);
	}

	///Get our Phone
	Game::Phone* Player::getPlayerPhone()
	{
		return this->Phone;
	}

	///Get our crosshair
	Game::Crosshair* Player::getPlayerCrosshair()
	{
		return this->Crosshair;
	}

	///Set our Phone
	void Player::SetPhoneModel(Resources::Model* model)
	{
		this->Phone->SetModel(model);
	}

	///Player destructor
	Player::~Player()
	{
		delete this->_playerView;
		delete this->Crosshair;
		delete this->Phone;
		delete this->CubeCulling;
	}

	///Get the position of the player
	LibMath::Vec3 Player::getPostion()
	{
		return this->Position;
	}

	///Get the velocity of the player
	LibMath::Vec3 Player::getVelocity()
	{
		return this->Velocity;
	}

	///Set the player to a specific position
	void Player::setPlayerPos(LibMath::Vec3 position)
	{
		this->Position = position;
	}

	///Set the velocity to a specific one
	void Player::setPlayerVelocity(LibMath::Vec3 vel)
	{
		this->Velocity = vel;
	}

	///Get the Forward vector
	LibMath::Vec3 Player::getForward()
	{
		return this->forward;
	}
}