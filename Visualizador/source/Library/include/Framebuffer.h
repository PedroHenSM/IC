#pragma once

#include "Common.h"

namespace Library
{
    class Framebuffer
    {
    public:
        Framebuffer(int width, int height);
        ~Framebuffer();

        virtual void Initialize() {}
        virtual void Resize(int width, int height){}
        virtual void Delete(){}

        virtual void UseAsTexture(){}

        virtual void Bind() const {}
        virtual inline void Release() const {}
        virtual inline void Clear() const {}

    protected:
        /** Framebuffer Object
         *
         */
        GLuint mFramebufferObject;

        /** Width of the Framebuffer Textures
         *
         */
        int mFramebufferWidth;

        /** Height of the Framebuffer Textures
         *
         */
        int mFrameufferHeight;

    private:
        Framebuffer& operator=(const Framebuffer& rhs);
        Framebuffer(const Framebuffer& rhs);

    };
}
