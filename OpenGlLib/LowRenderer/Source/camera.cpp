#include "LowRenderer/camera.h"
#include <iostream>

void Visual::Camera::LookAt(LibMath::Vec3& eye, LibMath::Vec3& center, LibMath::Vec3& UpVector)
{
	///Create a matrice identity
	LibMath::Mat4 LookAt = LibMath::Mat4::Identity();

	///This a vector pointing at the direction in the Z Axis
	LibMath::Vec3 f = LibMath::Vec3::Normalize(center - eye);

	///This a vector pointing at the direction in the X Axis
	LibMath::Vec3 s = LibMath::Vec3::Normalize(LibMath::Vec3::Cross(f, UpVector));

	///This a vector pointing at the direction in the Y Axis
	LibMath::Vec3 u = LibMath::Vec3::Normalize(LibMath::Vec3::Cross(s, f));

	///Set our X direction in our matrix
	LookAt[0][0] = s.x;
	LookAt[1][0] = s.y;
	LookAt[2][0] = s.z;

	///Set our Y direction in our matrix
	LookAt[0][1] = u.x;
	LookAt[1][1] = u.y;
	LookAt[2][1] = u.z;

	///Set our  Z direction in our matrix
	LookAt[0][2] = -f.x;
	LookAt[1][2] = -f.y;
	LookAt[2][2] = -f.z;
	
	///Look at the right direction
	LookAt[3][0] = -LibMath::Vec3::Dot(s, eye);
	LookAt[3][1] = -LibMath::Vec3::Dot(u, eye);
	LookAt[3][2] = LibMath::Vec3::Dot(f, eye);

	this->view = LookAt;
}

void Visual::Camera::CameraUpdate()
{
	///Vector Forward so we can move freely in space
	LibMath::Vec3 forwrard = this->Front + this->Position;

	this->LookAt(this->Position, forwrard, this->toTheSky);
}

void Visual::Camera::CameraInputHandler(double positionX, double positionY)
{
	///Calculate the offset in x and y
	float xoffset = positionX - this->lastx;
	float yoffset = this->lasty - positionY;

	///Set the last x and y for the next mouse move
	this->lastx = positionX;
	this->lasty = positionY;

	///Multiplicate our movement by our sensitivity
	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	///our angle is equal to our offset on the screen
	yaw += LibMath::Degree(xoffset);
	pitch += LibMath::Degree(yoffset);

	///Fix the rotation between 0 and 90
	if (pitch > LibMath::Degree(89.0f))
		pitch = LibMath::Degree(89.0f);
	if (pitch < LibMath::Degree(-89.0f))
		pitch = LibMath::Degree (-89.0f);

	///Move our Front vector based on our calculations before
	this->Front.x = LibMath::cos(yaw) * LibMath::cos(pitch);
	this->Front.y = LibMath::sin(pitch);
	this->Front.z = LibMath::sin(yaw) * LibMath::cos(pitch);

	///Keep the vector Front between 0 and 1
	this->Front = LibMath::Vec3::Normalize(this->Front);
}


