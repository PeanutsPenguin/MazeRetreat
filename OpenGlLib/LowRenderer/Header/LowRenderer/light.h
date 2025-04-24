#pragma once
#include "Resources/ResourceManager.h"
#include "Resources/Scene.h"

namespace Visual
{
	class Light : public Resources::SceneNode
	{
	public:
		LibMath::Vec3 position, ambientColor, lightDir;

		Light() = default;

		Light(const Light&) = default;

		Light& operator=(const Light&) = default;

		Light(const LibMath::Vec3 position, const LibMath::Vec3 diffuse, const LibMath::Vec3 ambient, const LibMath::Vec3 specular, const LibMath::Vec3 dir, const LibMath::Vec3 view, double cutOff, float quadratic)
			: position(position), diffuseColor(diffuse), ambientColor(ambient), specularColor(specular), lightDir(dir), viewPos(view), cutOff(cutOff), quadratic(quadratic) {}

		void SetValues(const LibMath::Vec3 position, const LibMath::Vec3 diffuse, const LibMath::Vec3 ambient, const LibMath::Vec3 specular, const LibMath::Vec3 dir, const LibMath::Vec3 view, double cutOff, float quadratic);
	
		void renderPoint(Resources::Shader& myShader, int index);

		void renderSpot(Resources::Shader& myShader, bool isSpotLightOn);

		void setUniformsSpot(GLuint program, bool isSpolightOn);

		void setUniformsPoint(GLuint program, const std::string& name);

		void UpdateSpotLight(LibMath::Vec3 pos, LibMath::Vec3 front);

		void UpdateColor(LibMath::Vec3 color);

		~Light() = default;
	private:
		LibMath::Vec3 diffuseColor, specularColor, viewPos;

		float quadratic = 0;
		float cutOff = 0;
	};
}
