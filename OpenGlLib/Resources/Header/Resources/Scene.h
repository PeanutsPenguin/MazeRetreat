#pragma once

#include "Core/Application.h"
#include "Core/sound.h"
#include "Physics/transform.h"
#include "Physics/boudingBox.h"
#include "DataStructure/Graph.h"
#include "Resources/Shader.h"
#include "Resources/texture.h"
#include "pch.h"

#include <vector>

namespace Resources
{
	enum OBJECT_TAG
	{
		E_WALL,
		E_GROUND,
		E_CEILING,
		E_KEY,
		E_UP_GRAPPLE,
		E_RIGHT_GRAPPLE
	};


	class SceneNode
	{
	public:
		SceneNode(void) = default;

		SceneNode(const SceneNode& node) = default;

		SceneNode(SceneNode&& node) = default;

		SceneNode(Resources::Model* model);

		SceneNode(Resources::Model* model, OBJECT_TAG tag);

		SceneNode(Resources::Model* model, Resources::Texture* tex, OBJECT_TAG tag);

		SceneNode(SceneNode* head, const Physics::Transform& transform);

		bool operator==(const SceneNode& toCheck) const = default;

		bool operator!=(const SceneNode& toCheck) const = default;

		void addTexture(Resources::Texture* manager);

		void UpdateboundingBox();

		void NodeInputHandler(Rendering::Application& screen, SceneNode& player, Sound::SoundEngine& engine);

		void RenderNode(Resources::Shader& shader, const LibMath::Mat4& pvm, Rendering::Application& screen, SceneNode& player, Sound::SoundEngine& engine);

		float GetGravity();

		OBJECT_TAG& getTag();

		Collision::Box* GetBoundingBox();

		Resources::Model* getModel();

		void setBoundingBox(Collision::Box* box);

		void SetModel(Resources::Model* model);

		~SceneNode();

		Physics::Transform local = LibMath::Mat4::Identity();

		LibMath::Vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
		LibMath::Vec3 Position = LibMath::Vec3(1.0f, 0, 1.0f);

		std::vector<Resources::Texture*> TexArray;

		float coolDownm = 0;

		bool active{ true };
		bool reachable{ false };
		bool grounded{ true };

	private :
		Resources::Model* _model = nullptr;
		Collision::Box* BoudingBox = nullptr;
		float gravity = 0.1;
		OBJECT_TAG tag = E_WALL;
	};

	class Scene : public DataStructure::Graph<SceneNode>
	{
	public:
		Scene(void) = default;

		template<typename _Type>
		Scene& insert(const _Type& toInsert);

		void RenderScene(Resources::Shader& shader, const LibMath::Mat4& pvm, Rendering::Application& screen, SceneNode& PLayer, Sound::SoundEngine& engine);

		~Scene(void);
	};
}

#include "Resources/Scene.hpp"