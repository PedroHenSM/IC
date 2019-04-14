#include "VectorHelper.h"

#include <assimp/vector3.h>

namespace Library
{
	const vec3 VectorHelper::Forward = vec3(0.0f, 0.0f, -1.0f);
	const vec3 VectorHelper::Right = vec3(1.0f, 0.0f, 0.0f);
	const vec3 VectorHelper::Up = vec3(0.0f, 1.0f, 0.0f);

	const float VectorHelper::RadianToDegree = 57.2957795130f;
	const float VectorHelper::DegreeToRadian = 0.0174532925f;

	quat VectorHelper::RotationFromTo(vec3 from, vec3 to)
	{
		vec3 a(normalize(from));
		vec3 b(normalize(to));

		float dotProduct = dot(a, b);

		if (dotProduct < 1.0f - 1e-6f && dotProduct > 1e-6f - 1.0f)
		{
			float sin = glm::sqrt((1.0f - dotProduct) / 2.0f);
			float cos = glm::sqrt((1.0f + dotProduct) / 2.0f);
			vec3 axis = cross(a, b) * sin;

			return normalize(quat(cos, axis.x, axis.y, axis.z));
		}
		else
		{
			if (a != Up)
			{
				vec3 axis(cross(a, Up));
				float angle = glm::pi<float>();
				return quat(angle, axis);
			}
			else
			{
				vec3 axis(cross(a, Forward));
				float angle = glm::pi<float>();
				return quat(angle, axis);
			}
		}
	}

	vec3 VectorHelper::Vec3Cast(aiVector3D& vector)
	{
		return vec3(vector.x, vector.y, vector.z);
	}
}
