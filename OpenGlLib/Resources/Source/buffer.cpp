#include "Resources/Model.h"

namespace Resources
{
	Model::Buffer::Buffer(std::vector<Model::Vertex>& VertexBuffer)
	{	
		///Initialize a VBO
		glGenBuffers(1, &this->m_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
		glBufferData(GL_ARRAY_BUFFER, VertexBuffer.size() * sizeof(VertexBuffer[0]), &VertexBuffer[0], GL_STATIC_DRAW);
	}

	Model::Buffer::Buffer(std::vector<GLuint>& IndiceBuffer)
	{
		///Initialize a EBO
		glGenBuffers(1, &this->m_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndiceBuffer.size() * sizeof(IndiceBuffer[0]), &IndiceBuffer[0], GL_STATIC_DRAW);
	}

	Model::VertexAttributes::VertexAttributes()
	{	
		///Initialize a VAO
		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(VAO);
	}

	void Model::VertexAttributes::SetAttribute(int location, int nbrOfElements, int gapSize, int toFirstSize)
	{
		///Set the right attributes to the Vertex Array Object
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(location, nbrOfElements, GL_FLOAT, GL_FALSE, gapSize, (void*)toFirstSize);
	}
}