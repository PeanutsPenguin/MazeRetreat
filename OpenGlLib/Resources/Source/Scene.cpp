#include "Resources/Scene.h"

namespace Resources
{
	///Set The right Model for the Node
	SceneNode::SceneNode(Resources::Model* model)
	{
		this->_model = model;
		this->BoudingBox = DBG_NEW Collision::Box;
	}

	///Set The right Model and if is a collectible or not for the Node
	SceneNode::SceneNode(Resources::Model* model, OBJECT_TAG tag)
	{
		this->_model = model;
		this->tag = tag;

		this->BoudingBox = DBG_NEW Collision::Box;
	}

	///Set The right Model, if is a collectible or not and a texture for the Node
	SceneNode::SceneNode(Resources::Model* model, Resources::Texture* tex, OBJECT_TAG tag)
	{
		this->_model = model;
		this->TexArray.push_back(tex);
		this->tag = tag;
		this->BoudingBox = DBG_NEW Collision::Box;
	}

	///Set the right head and a local matrix
	SceneNode::SceneNode(SceneNode* head, const Physics::Transform& transform)
	{
		this->local = transform;
		this->BoudingBox = DBG_NEW Collision::Box;
	}

	///Add a texture to the Node
	void SceneNode::addTexture(Resources::Texture* manager)
	{
		this->TexArray.push_back(manager);
	}

	///Update the Bouding box of the Node
	void SceneNode::UpdateboundingBox()
	{
		///Multiply the global matrix by the local matrix of the object
		LibMath::Mat4 finalMatrix = this->local.m_transform;

		std::vector<LibMath::Vec3> NewPosition;
		for (int i = 0; i < this->_model->vertexBuffer.size(); ++i)
		{
			///For all the Vertices take their position and multiply it by their transform matrix
			LibMath::Vec4 result = LibMath::Vec4(this->_model->vertexBuffer[i].position) * finalMatrix;

			NewPosition.push_back({ result.x, result.y, result.z });
		}

		this->BoudingBox->MaxPos = Collision::getVectorMax(NewPosition);
		this->BoudingBox->MinPos = Collision::getVectorMin(NewPosition);
	}

	///Input handler for the Node
	void SceneNode::NodeInputHandler(Rendering::Application& screen, SceneNode& player, Sound::SoundEngine& engine)
	{
		///If we press left click and the object is reachable 
		if (glfwGetMouseButton(screen.screen, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && this->reachable && this->coolDownm > 2 && this->tag == E_KEY)
		{
			engine.engine->play2D(engine.keysound);

			LibMath::Vec4 tempColor = player.color;

			///We set the color to the phone
			player.color = this->color;
			this->color = tempColor;

			this->coolDownm = 0;
		}

		if (glfwGetMouseButton(screen.screen, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && this->reachable && this->coolDownm > 2 && this->tag == E_UP_GRAPPLE && player.color == this->color)
		{
			engine.engine->play2D(engine.grappleSound);

			player.grounded = false;
			LibMath::Vec3 tempPos = this->Position;
			//tempPos.x -= 3;
			player.Position = tempPos;
		}

		if (glfwGetMouseButton(screen.screen, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && this->reachable && this->coolDownm > 2 && this->tag == E_RIGHT_GRAPPLE && player.color == this->color)
		{
			engine.engine->play2D(engine.grappleSound);

			player.grounded = false;
			LibMath::Vec3 tempPos = this->Position;
			//tempPos.z -= 3;
			player.Position = tempPos;
		}
			
	}

	///Function to render the node
	void SceneNode::RenderNode(Resources::Shader& shader, const LibMath::Mat4& pvm, Rendering::Application& screen, SceneNode& player, Sound::SoundEngine& engine)
	{
		///Check if there is any input pressed
		this->NodeInputHandler(screen, player, engine);

		if (this->tag == E_KEY || this->tag == E_RIGHT_GRAPPLE || this->tag == E_UP_GRAPPLE)
		{
			this->coolDownm += screen.getDeltaTime();
		}
			
		///Multiply the global matrix by the local matrix of the object
		LibMath::Mat4 finalMatrix = this->local.m_transform;

		if (this->active)
		{
			///Bind the element buffer
			glBindBuffer(GL_ARRAY_BUFFER, this->getModel()->ElementBuffer.m_buffer);

			///For all the texture the current object has, bind them and send them in the fragment shader
			for (int i = 0; i < this->TexArray.size(); ++i)
			{
					glActiveTexture(this->TexArray[i]->index);
					glBindTexture(GL_TEXTURE_3D, this->TexArray[i]->id);

					std::string name = "textures[" + std::to_string(i) + "]";
					glUniform1i(glGetUniformLocation(shader.SahderProg, name.c_str()), i);
			}

			///Find the pvm matrix and apply it to every vertex
			glUniformMatrix4fv(glGetUniformLocation(shader.SahderProg, "PVM"), 1, GL_FALSE, &(pvm * this->local.m_transform)[0][0]);
			glUniformMatrix4fv(glGetUniformLocation(shader.SahderProg, "model"), 1, GL_FALSE, &finalMatrix[0][0]);
			glUniform1i(glGetUniformLocation(shader.SahderProg, "nbtextures"), this->TexArray.size());
			glUniform4fv(glGetUniformLocation(shader.SahderProg, "color"),1, (float*)&this->color);

			///Bind the Vertex Array Object
			glBindVertexArray(this->_model->VertexObject.VAO);

			///Draw everything
			glDrawElements(GL_TRIANGLES, this->_model->indices.size(), GL_UNSIGNED_INT, 0);

			///Unbind 
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			///Unbind the textures
			for (int i = 0; i < this->TexArray.size(); ++i)
			{
				glActiveTexture(this->TexArray[i]->index);
				glBindTexture(GL_TEXTURE_3D, 0);
			}

			///Reset the boolean reachable because we update it every frame
			this->reachable = false;
		}
	}

	float SceneNode::GetGravity()
	{
		return this->gravity;
	}

	OBJECT_TAG& SceneNode::getTag()
	{
		return this->tag;
	}

	Collision::Box* SceneNode::GetBoundingBox()
	{
		return this->BoudingBox;
	}

	Resources::Model* SceneNode::getModel()
	{
		return this->_model;
	}

	void SceneNode::setBoundingBox(Collision::Box* box)
	{
		this->BoudingBox = box;
	}

	void SceneNode::SetModel(Resources::Model* model)
	{
		this->_model = model;
	}

	SceneNode::~SceneNode()
	{
		if(this->BoudingBox != nullptr)
			delete this->BoudingBox;
	}

	///Render the object
	void Scene::RenderScene(Resources::Shader& shader, const LibMath::Mat4& pvm, Rendering::Application& screen, SceneNode& Player, Sound::SoundEngine& engine)
	{
		for(int i = 0; i < this->nodes.size(); ++i)
		{
			this->nodes[i]->RenderNode(shader, pvm, screen, Player, engine);
		}
	}

	Scene::~Scene(void)
	{
		for(int i = 0; i < this->nodes.size(); ++i)
		{
			delete this->nodes[i];
		}
	}

}

