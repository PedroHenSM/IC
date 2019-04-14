#include "OrbitCamera.h"
#include "Common.h"

namespace Library
{
    RTTI_DEFINITIONS(OrbitCamera);

    OrbitCamera::OrbitCamera(Renderer& renderer)
        : Camera(renderer),
          mCenter(0.0f),
          mZoomSensibility(5.0f),
          mPanSensibility(0.1f),
          mOrbitSensibility(10.0f)
    {
    }

    OrbitCamera::OrbitCamera(Renderer& renderer, float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance)
        : Camera(renderer, fieldOfView, aspectRatio, nearPlaneDistance, farPlaneDistance),
          mCenter(0.0f),
          mZoomSensibility(5.0f),
          mPanSensibility(0.1f),
          mOrbitSensibility(10.0f)
    {

    }

    void OrbitCamera::Orbit(vec2 delta)
    {
		vec3 distance = mPosition - mCenter;

		float theta = atan2( distance.x, distance.z );
		float phi = atan2( sqrt( distance.x * distance.x + distance.z * distance.z ), distance.y );

        delta *= mOrbitSensibility;
		theta += delta.x;
		phi += delta.y;

		float EPS = 0.000001f;

		phi = max( EPS, min( pi<float>() - EPS, phi ) );

		float radius = sqrt(distance.x*distance.x + distance.y*distance.y + distance.z*distance.z);

		distance.x = radius * sin( phi ) * sin( theta );
		distance.y = radius * cos( phi );
		distance.z = radius * sin( phi ) * cos( theta );

		mPosition = mCenter + distance;

		mDirection = normalize(-distance);
		mRight = normalize(cross(mDirection, vec3(0, 1, 0)));
		mUp = cross(mRight, mDirection);



        mViewMatrixNeedUpdate = true;
    }

    void OrbitCamera::Zoom(float times)
    {
        vec3 distance = mPosition - mCenter;

        distance *= (1.0f + times * mZoomSensibility);
        mPosition = mCenter + distance;

        mViewMatrixNeedUpdate = true;
    }

    void OrbitCamera::Pan(vec2 pan)
    {
        vec3 distance = (mPosition - mCenter);
        vec3 translation = (pan.x * mRight) + (-pan.y * mUp);
        translation *= sqrt(distance.x*distance.x + distance.y*distance.y + distance.z*distance.z) * 10.0f * mPanSensibility + 0.001f;
        mPosition += translation;
        mCenter += translation;
        mViewMatrixNeedUpdate = true;
    }

    void OrbitCamera::LookAt(vec3 focus)
    {
        vec3 distance = mPosition - mCenter;
        mCenter = focus;
        mPosition = focus + distance;

        mViewMatrixNeedUpdate = true;
    }
}
