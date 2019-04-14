#pragma once

#include "Common.h"
#include <assimp/vector3.h>

namespace Library
{
	class VectorHelper
	{
	public:
		static const vec3 Forward;
		static const vec3 Right;
		static const vec3 Up;

		static const float RadianToDegree;
		static const float DegreeToRadian;

		static quat RotationFromTo(vec3 from, vec3 to);

		static vec3 Vec3Cast(aiVector3D& vector);


	private:
		VectorHelper();
		VectorHelper(const VectorHelper& rhs);
		VectorHelper& operator=(const VectorHelper& rhs);
	};
}
