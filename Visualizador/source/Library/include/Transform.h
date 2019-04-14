#pragma once

#include "Common.h"

namespace Library
{
	class Camera;

	class Transform
	{
	public:
		Transform();
		Transform(vec3 position);
		Transform(vec3 position, vec3 eulerAngles);
		Transform(vec3 position, quat rotation);
		Transform(vec3 position, vec3 eulerAngles, vec3 scale);
		Transform(vec3 position, quat rotation, vec3 scale);
		~Transform();

		void Translate(vec3 translation);
		void SetPosition(vec3 position);
		vec3 GetPosition() const;

		void Scale(vec3 scale);
		void Scale(float scale);

		void Rotate(const vec3& eulerAngles);
		void Rotate(const quat& rotation);
		void SetRotation(const vec3& eulerAngles);
		void SetRotation(const quat& rotation);
		quat GetRotation() const;
		vec3 GetEulerAngles() const;

		void LookAt(vec3 center);
		void RotateAround(vec3 center, vec3 axis, float angle);

		const mat4& LocalToWorldMatrix();
		const mat4& LocalToViewMatrix();
		const mat4& LocalToScreenMatrix();

		void UpdateCameraMatrix(Camera& camera);

	private:
		vec3 mPosition;
		vec3 mScale;
		quat mRotation;

		vec3 mForward;
		vec3 mRight;
		vec3 mUp;

		bool mMatrixNeedUpdate;
		mat4 mLocalToWorldMatrix;
		mat4 mLocalToViewMatrix;
		mat4 mLocalToScreenMatrix;

		void UpdateMatrix();
	};
}
