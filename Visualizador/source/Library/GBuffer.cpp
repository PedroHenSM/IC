#include "GBuffer.h"

namespace Library
{
    GLenum GBuffer::mDrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };

    GBuffer::GBuffer(int width, int height) : Framebuffer(width, height), mFrameBufferObject(0),
        mRT0(0), mRT1(0), mRT2(0), mDepthBuffer(0)
    {}

    GBuffer::~GBuffer()
    {
        Delete();
    }

    void GBuffer::Initialize()
    {
        /// Create the RT0 Texture
        /// //////////////////////////
        glGenTextures(1, &mRT0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mRT0);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mFramebufferWidth, mFrameufferHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_2D, 0);

        /// Create the RT1 Texture
        /// //////////////////////////
        glGenTextures(1, &mRT1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, mRT1);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mFramebufferWidth, mFrameufferHeight, 0, GL_RGBA, GL_FLOAT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_2D, 0);

        /// Create the RT2 Texture
        /// //////////////////////////
        glGenTextures(1, &mRT2);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, mRT2);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, mFramebufferWidth, mFrameufferHeight, 0, GL_RG, GL_FLOAT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_2D, 0);

        /// Create the Depth
        /// //////////////////////////
        glGenTextures(1, &mDepthBuffer);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, mDepthBuffer);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, mFramebufferWidth, mFrameufferHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_2D, 0);


        /// Create the Framebuffer
        /// //////////////////////////
        glGenFramebuffers(1, &mFrameBufferObject);
        glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferObject);

        // Attach the Albedo/Metallic buffer
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mRT0, 0);

        // Attach the Normal/Roughness buffer
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, mRT1, 0);

        // Attach the AO/Specular
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, mRT2, 0);

        // Attach the  depth buffer
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mDepthBuffer, 0);

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            Delete();
            throw RendererException("GL_FRAMEBUFFER_COMPLETE error 0x" + glCheckFramebufferStatus(GL_FRAMEBUFFER));
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

    }

    void GBuffer::Resize(int width, int height)
    {
        // Delete old textures, if any
        Delete();

        // Update GBuffer size
        mFramebufferWidth = width;
        mFrameufferHeight = height;

        // Create the other GBuffer
        Initialize();
    }

    void GBuffer::Delete()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        DeleteFramebuffer(mFrameBufferObject);

        glBindTexture(GL_TEXTURE_2D, 0);
        DeleteTexture(mRT0);
        DeleteTexture(mRT1);
        DeleteTexture(mRT2);
        DeleteTexture(mDepthBuffer);
    }

    void GBuffer::UseAsTexture()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mRT0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, mRT1);

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, mRT2);

        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, mDepthBuffer);
    }

    void GBuffer::Bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferObject);
        glDrawBuffers(3, mDrawBuffers);
    }

    void GBuffer::Release() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDrawBuffer(GL_COLOR_ATTACHMENT0);
    }

    void GBuffer::Clear() const
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    GLuint GBuffer::RT0() const
    {
        return mRT0;
    }

    GLuint GBuffer::RT1() const
    {
        return mRT1;
    }

    GLuint GBuffer::RT2() const
    {
        return mRT2;
    }

    GLuint GBuffer::DepthBuffer() const
    {
        return mDepthBuffer;
    }

}
