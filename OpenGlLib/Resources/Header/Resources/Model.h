#pragma once

#include "Iresources.h"
#include "pch.h"

///LibMath Include
#include "LibMath/Vector/Vec2.h"
#include "LibMath/Vector/Vec3.h"

///Standar Include
#include <vector>
#include <string>

///ModernOpenGl Include
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Resources
{
	class Model : public IResources
	{
		class Vertex
		{
		public:
			LibMath::Vec3 position;
			LibMath::Vec3 Normale;
			LibMath::Vec3 TexturePosition;

			struct Hash
			{
				size_t operator()(const Vertex& vec) const
				{
					return	std::hash<float>()(vec.position.x) ^ std::hash<float>()(vec.position.y) ^ std::hash<float>()(vec.position.z) ^
						std::hash<float>()(vec.Normale.x) ^ std::hash<float>()(vec.Normale.y) ^ std::hash<float>()(vec.Normale.z) ^
						std::hash<float>()(vec.TexturePosition.x) ^ std::hash<float>()(vec.TexturePosition.y);
				}
			};

			Vertex(void) = default;

			Vertex(const Vertex&) = default;

			Vertex& operator=(const Vertex&) = default;

			Vertex(Vertex&&) = default;

			Vertex& operator=(Vertex&&) = default;

			bool operator==(const Vertex& toCompare) const;

			bool operator!=(const Vertex& toCompare) const;

			~Vertex() = default;
		};

		class Buffer
		{
		public:
			Buffer() = default;

			Buffer(std::vector<Model::Vertex>& VertexBuffer);

			Buffer(std::vector<unsigned int>& IndiceBuffer);

			Buffer& operator=(const Buffer&) = default;

			~Buffer() = default;

			unsigned int m_buffer;
		};

		class VertexAttributes
		{
		public:	
			VertexAttributes();

			VertexAttributes& operator=(const VertexAttributes&) = default;

			void SetAttribute(int location, int nbrOfElements, int gapSize, int toFirstSize);

			~VertexAttributes() = default;

			unsigned int VAO;
		};

	public:

		Model(void) = default;

		Model(std::string& fileName);

		~Model(void) = default;

		std::vector<Vertex> vertexBuffer;
		std::vector<unsigned int> indices;

		Resources::Model::Buffer VertexBufferObject;
		Resources::Model::VertexAttributes VertexObject;
		Resources::Model::Buffer ElementBuffer;

	};
} 