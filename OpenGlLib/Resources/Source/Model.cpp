#include "Resources/Model.h"
#include <fstream>
#include <sstream>
#include <unordered_map>


Resources::Model::Model(std::string& fileName)
{
	///Open the file
	std::ifstream fstream = std::ifstream(fileName);

	///Create a map of Vec3 with a string key
	std::unordered_map<std::string, std::vector<LibMath::Vec3>> vecmap;

	///Create a map of size_t with a vertex key (to keep the index)
	std::unordered_map<Model::Vertex, size_t, Model::Vertex::Hash> vertices;

	///String that'll contaain our line
	std::string line;
	while (std::getline(fstream, line))
	{
		std::istringstream stream(line);

		///Get the first charachter of the line
		std::string ID;
		stream >> ID;

		if (ID != "f")
		{
			///If it's not f we create a vector 3 with the numbers following the first character
			LibMath::Vec3 vec;
			stream >> vec;

			///Push back our Vector in the map and set the id to the first character founds
			vecmap[ID].push_back(std::move(vec));
		}
		else if (ID == "f")
		{
			///Doing a for 'cause there is three Vertices
			for (size_t n = 0; n < 3; ++n)
			{
				///Create a vertex
				Model::Vertex vertex;

				///Stock the line in a string and add '/' at the end of it
				std::string str;
				stream >> str;
				str += '/';


				std::string token;
				size_t pos = 0;
				int index = 0;

				///While the next character isn't '/'
				while ((pos = str.find("/")) != std::string::npos)
				{
					///Add one to the index
					++index;

					///Split the string and erase it
					token = str.substr(0, pos);
					str.erase(0, pos + 1);

					///If the string is empty skip the rest
					if (token.empty()) continue;

					switch (index)
					{
					default:
					///If the index is equal to 1 it means we're on vertex Coordinates
					case 1:
					{
						///Convert the string into int
						int component = std::stoi(token);
						///If the int is negative substract the size with the given index
						if (component < 0) component += vecmap["v"].size();
						///else -1 because index starts at one
						else component -= 1;

						///set the right position to our vertex
						vertex.position = vecmap["v"][component];
					}
					break;
					case 2:
					{
						///Convert the string into int
						int component = std::stoi(token);
						///If the int is negative substract the size with the given index
						if (component < 0) component += vecmap["vt"].size();
						///else -1 because index starts at one
						else component -= 1;

						///set the right Texture position to our vertex
						vertex.TexturePosition = vecmap["vt"][component];
					}
					break;
					case 3:
					{
						///set the right position to our vertex
						int component = std::stoi(token);
						///If the int is negative substract the size with the given index
						if (component < 0) component += vecmap["vn"].size();
						///else -1 because index starts at one
						else component -= 1;

						///set the right Normale to our vertex
						vertex.Normale = vecmap["vn"][component];
					}
					break;
					}
				}

				///If our Vertex doesn't exist
				if (!vertices.contains(vertex))
				{
					///Stock it in our map
					vertices[vertex] = vertices.size();
					this->vertexBuffer.push_back(vertex);
				}
				this->indices.push_back(vertices[vertex]);
			}
		}
	}

	///Create the Vertex Buffer Object
	Model::Buffer tempVBO(this->vertexBuffer);

	this->VertexBufferObject = tempVBO;

	///Create the Vertex Array Object
	Model::VertexAttributes tempVAO;

	///Set all the attributes we have in our Vertices
	tempVAO.SetAttribute(0, 3, 9 * sizeof(float), 0);
	tempVAO.SetAttribute(1, 3, 9 * sizeof(float), 3 * sizeof(float));
	tempVAO.SetAttribute(2, 3, 9 * sizeof(float), 6 * sizeof(float));

	this->VertexObject = tempVAO;

	///Create the Ellement Buffer
	Resources::Model::Buffer tempEBO(this->indices);

	this->ElementBuffer = tempEBO;
}
