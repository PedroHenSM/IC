#include "RendererException.h"

namespace Library
{
    RendererException::RendererException(std::string message) : mMessage(message)
    {}

    const char* RendererException::what()
    {
        return mMessage.c_str();
    }
}
