#pragma once

#include "Common.h"
#include "Framebuffer.h"

namespace Library
{
    class GBuffer : public Framebuffer
    {
    public:
        GBuffer(int width, int height);
        ~GBuffer();

        void Initialize();
        void Resize(int width, int height);
        void Delete();

        void UseAsTexture();

        void Bind() const;
        void Release() const;
        void Clear() const;

        GLuint RT0() const;
        GLuint RT1() const;
        GLuint RT2() const;
        GLuint DepthBuffer() const;



    private:
        /** Framebuffer Object
         *
         */
        GLuint mFrameBufferObject;

        /** RT0 Deferred Shading Texture
         *  RGB: Diffuse Albedo A: AO
         */
        GLuint mRT0;

        /** RT1 Deferred Shading Texture
         *  RGA: NormalXYZ A: Roughness
         */
        GLuint mRT1;

        /** RT2 Deferred Shading Texture
         *  R: Metallic G: Specular
         */
        GLuint mRT2;

        /** Depth & Stencil Buffer
         *  24b Depth 8b Stencil
         */
         GLuint mDepthBuffer;

        static GLenum mDrawBuffers[3];


        // Prevent copy
        GBuffer(const GBuffer &rhs);
        GBuffer& operator=(const GBuffer &rhs);



    };

}


