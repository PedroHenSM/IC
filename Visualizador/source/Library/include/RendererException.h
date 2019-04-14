#pragma once

#include "Common.h"

namespace Library
{
    class RendererException : public std::exception
    {
    public:
        RendererException(std::string message);
        const char* what();

    private:
        std::string mMessage;
    };

}
