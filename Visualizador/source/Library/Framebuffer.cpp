#include "Framebuffer.h"

namespace Library
{
    Framebuffer::Framebuffer(int width, int height) : mFramebufferObject(0), mFramebufferWidth(width), mFrameufferHeight(height)
    {}

    Framebuffer::~Framebuffer()
    {}
}
