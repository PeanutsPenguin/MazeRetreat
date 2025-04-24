#pragma once

///LibMath include
#include "LibMath/Matrix/Mat4x4.h"
#include "LibMath/Angle/Degree.h"
using namespace LibMath::Literal;
#include "pch.h"


namespace Visual
{
	///Class for the camera 
	class Camera
	{
	public:
		LibMath::Mat4 view = LibMath::Mat4::Identity();
		LibMath::Mat4 transformation = LibMath::Mat4::Identity();
		LibMath::Mat4 projection = LibMath::Mat4::Perspective(70.f, 1920.f / 1080.f, 0.1f, 50.f);

		LibMath::Vec3 Position = { 0.0f, 0.0f, 0.5f };
		LibMath::Vec3 toTheSky = { 0.0f, 1.0f, 0.0f };
		LibMath::Vec3 Front = {0.0f, 0.0f, 1.0f};

		LibMath::Degree yaw;
		LibMath::Degree pitch;

		float movementSpeed = 1.f;
		float lastx = 400;
		float lasty = 300;

		void LookAt(LibMath::Vec3& eye, LibMath::Vec3& center, LibMath::Vec3& UpVector);

		void CameraUpdate();

		void CameraInputHandler(double pox, double posy);

		Camera() = default;

		~Camera() = default;
	};
}
