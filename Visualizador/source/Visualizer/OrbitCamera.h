#pragma once

#include "Common.h"
#include "Camera.h"

namespace Library
{
    class OrbitCamera : public Camera
    {
        RTTI_DECLARATIONS(Camera, RendererComponent);

    public:
        OrbitCamera(Renderer& renderer);
        OrbitCamera(Renderer& renderer, float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);

        void Orbit(vec2 delta);
        void Zoom(float times);

        void Pan(vec2 pan);
        void LookAt(vec3 focus);

    private:
        vec3 mCenter;
        float mZoomSensibility;
        float mPanSensibility;
        float mOrbitSensibility;

        float mTheta;
        float mPhi;

    };
}
