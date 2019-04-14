#pragma once

#include <cstdarg>

#include "Renderer.h"
#include "Texture.h"
#include "Shader.h"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Library
{
    struct Character {
        GLuint     TextureID;  // ID handle of the glyph texture
        glm::ivec2 Size;       // Size of glyph
        glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
        GLuint     Advance;    // Offset to advance to next glyph
    };

    class Text2D
    {
    public:
        static void Initialize(Renderer* renderer, int size = 32);
        /*static void Print(std::string text, int x, int y, int size, float spacing = 0.8f);
        static void Print(int x, int y, int size, float spacing, char* text, ...);*/
        static void Print(std::string text, int x, int y, float scale, vec3 color = vec3(1.0f));
        static void Print(int x, int y, float size, vec3 color, char* format, ...);
        static void Exit();
    private:
        static Texture *mTexture;
        static Shader *mShader;

        static GLuint mVertexArray;
        static GLuint mVertexBuffer;
        static GLuint mUVBuffer;

        static GLuint mTextureSamplerUniform;

        static Renderer* mRenderer;

        static FT_Library mFreeTypeLibrary;
        static FT_Face mFace;

        static int mSize;

        static std::map<GLchar, Character> mCharacters;
    };
}
