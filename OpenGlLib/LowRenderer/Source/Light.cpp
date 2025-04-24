#include "LowRenderer/light.h"

void Visual::Light::SetValues(const LibMath::Vec3 position, const LibMath::Vec3 diffuse, const LibMath::Vec3 ambient, const LibMath::Vec3 specular, const LibMath::Vec3 dir, const LibMath::Vec3 view, double cutOff, float quadratic)
{
	this->position = position;
	this->diffuseColor = diffuse;
	this->ambientColor = ambient;
	this->specularColor = specular;
	this->lightDir = dir;
	this->viewPos = view;
	this->cutOff = cutOff;
	this->quadratic = quadratic;
}

void Visual::Light::renderPoint(Resources::Shader& myShader, int index)
{
    std::string uniformName = "pointlight[" + std::to_string(index) + "].";

	this->setUniformsPoint(myShader.SahderProg, uniformName);
}

void Visual::Light::renderSpot(Resources::Shader& myShader, bool isSpolightOn)
{
	this->setUniformsSpot(myShader.SahderProg, isSpolightOn);
}

void Visual::Light::setUniformsSpot(GLuint program, bool isSpolightOn)
{
	glUniform3fv(glGetUniformLocation(program, "viewPos"), 1, (float*)&this->viewPos);
	glUniform3fv(glGetUniformLocation(program, "lightPos"), 1, (float*)&this->position);
	glUniform3fv(glGetUniformLocation(program, "lightAmbient"), 1, (float*)&this->ambientColor);
	glUniform3fv(glGetUniformLocation(program, "lightDiffuse"), 1, (float*)&this->diffuseColor);
	glUniform3fv(glGetUniformLocation(program, "lightSpecular"), 1, (float*)&this->specularColor);
	glUniform3fv(glGetUniformLocation(program, "lightDir"), 1, (float*)&this->lightDir);
	glUniform1f(glGetUniformLocation(program, "cutOff"), cutOff);
	glUniform1f(glGetUniformLocation(program, "quadratic"), quadratic);
	glUniform1i(glGetUniformLocation(program, "isSpotLightOn"), isSpolightOn);
}

void Visual::Light::setUniformsPoint(GLuint program, const std::string& name)
{
	glUniform3fv(glGetUniformLocation(program, (name + "position").c_str()), 1, (float*)&this->position);
	glUniform3fv(glGetUniformLocation(program, (name + "Ambient").c_str()), 1, (float*)&this->ambientColor);
	glUniform3fv(glGetUniformLocation(program, (name + "Diffuse").c_str()), 1, (float*)&this->diffuseColor);
	glUniform3fv(glGetUniformLocation(program, (name + "Specular").c_str()), 1, (float*)&this->specularColor);
	glUniform1f(glGetUniformLocation(program, (name + "quadratic").c_str()), quadratic);
}

void Visual::Light::UpdateSpotLight(LibMath::Vec3 pos, LibMath::Vec3 front)
{
	this->position = pos;
	this->lightDir = front;
}

void Visual::Light::UpdateColor(LibMath::Vec3 color)
{
	this->ambientColor = color;
}

   