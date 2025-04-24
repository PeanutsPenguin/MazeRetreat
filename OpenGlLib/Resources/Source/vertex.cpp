#include "Resources/Model.h"

namespace Resources
{
	bool Model::Vertex::operator==(const Vertex& toCompare) const
	{
		if (this->position == toCompare.position && this->Normale == toCompare.Normale && this->TexturePosition == toCompare.TexturePosition)
			return true;
		else
			return false;
	}
	bool Model::Vertex::operator!=(const Vertex& toCompare) const
	{
		return this->position != toCompare.position || this->Normale != toCompare.Normale || this->TexturePosition != toCompare.TexturePosition;
	}
}