#include "Text2D.h"
#include <cstdio>
#include <cstring>

#include "RendererException.h"
#include "Utility.h"

namespace Library
{
    Texture *Text2D::mTexture = nullptr;
    Shader *Text2D::mShader = nullptr;
    int Text2D::mSize = 32;
    GLuint Text2D::mTextureSamplerUniform = 0;
    GLuint Text2D::mVertexArray = 0;
    GLuint Text2D::mVertexBuffer = 0;
    GLuint Text2D::mUVBuffer = 0;
    Renderer *Text2D::mRenderer = nullptr;
    FT_Library Text2D::mFreeTypeLibrary;
    FT_Face Text2D::mFace;
    std::map<GLchar, Character> Text2D::mCharacters;


    void Text2D::Initialize(Renderer *renderer, int size)
    {
        // Set renderer reference
        mRenderer = renderer;

        // Set De default size
        mSize = size;

        // Initialize VBO
        glGenVertexArrays(1, &mVertexArray);
        glGenBuffers(1, &mVertexBuffer);
        glGenBuffers(1, &mUVBuffer);

        // Initialize Shader
        #ifdef ALLAN
            mShader = new Shader("../../content/textVert.glsl", "../../content/textFrag.glsl");
        #else
            mShader = new Shader("../../content/textVertLili.glsl", "../../content/textFragLili.glsl");
        #endif // ALLAN

        // Initialize uniforms' IDs
        mTextureSamplerUniform = mShader->GetUniform("text");

        if (FT_Init_FreeType(&mFreeTypeLibrary))
            throw RendererException("Could not init FreeType Library");

        if (FT_New_Face(mFreeTypeLibrary, Utility::GetPath("../../content/FreeSans.ttf").c_str(), 0, &mFace))
            throw RendererException("Failed to load font");

        FT_Set_Pixel_Sizes(mFace, 0, mSize);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

        for (GLubyte c = 0; c < 128; c++)
        {
            // Load character glyph
            if (FT_Load_Char(mFace, c, FT_LOAD_RENDER))
            {
                throw RendererException("Failed to load Glyph");
                continue;
            }
            // Generate texture
            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                mFace->glyph->bitmap.width,
                mFace->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                mFace->glyph->bitmap.buffer
            );
            // Set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // Now store character for later use
            Character character = {
                texture,
                glm::ivec2(mFace->glyph->bitmap.width, mFace->glyph->bitmap.rows),
                glm::ivec2(mFace->glyph->bitmap_left, mFace->glyph->bitmap_top),
                mFace->glyph->advance.x
            };
            mCharacters.insert(std::pair<GLchar, Character>(c, character));
        }
        FT_Done_Face(mFace);
        FT_Done_FreeType(mFreeTypeLibrary);


        // Allocate buffer size
        glBindVertexArray(mVertexArray);

        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    /*void Text2D::Print(int x, int y, int size, float spacing, char* format, ...)
    {
        size_t bufferSize = strlen(format)+256;
        char buffer[bufferSize];

        va_list argptr;
        va_start(argptr, format);
        std::vsnprintf (buffer, bufferSize, format, argptr);
        va_end(argptr);

        std::string fText(buffer);
        Print(fText, x, y, size, spacing);
    }

    void Text2D::Print(std::string text, int x, int y, int size, float spacing)
    {
        unsigned int length = text.length();

        int width = mRenderer->ScreenWidth() / 2.0f;
        int height = mRenderer->ScreenHeight() / 2.0f;
        glm::vec2 screen(width, height);

        // Fill buffers
        std::vector<glm::vec2> vertices;
        std::vector<glm::vec2> UVs;
        for ( unsigned int i=0 ; i<length ; i++ ){

            glm::vec2 vertex_up_left    = (glm::vec2( x+i*size*spacing      , y+size ) - screen) / screen;
            glm::vec2 vertex_up_right   = (glm::vec2( x+i*size*spacing+size , y+size ) - screen) / screen;
            glm::vec2 vertex_down_right = (glm::vec2( x+i*size*spacing+size , y      ) - screen) / screen;
            glm::vec2 vertex_down_left  = (glm::vec2( x+i*size*spacing      , y      ) - screen) / screen;

            vertices.push_back(vertex_up_left   );
            vertices.push_back(vertex_down_left );
            vertices.push_back(vertex_up_right  );

            vertices.push_back(vertex_down_right);
            vertices.push_back(vertex_up_right);
            vertices.push_back(vertex_down_left);

            char character = text[i];
            float uv_x = (character%16)/16.0f;
            float uv_y = (character/16)/16.0f;

            glm::vec2 uv_up_left    = glm::vec2( uv_x           , uv_y );
            glm::vec2 uv_up_right   = glm::vec2( uv_x+1.0f/16.0f, uv_y );
            glm::vec2 uv_down_right = glm::vec2( uv_x+1.0f/16.0f, (uv_y + 1.0f/16.0f) );
            glm::vec2 uv_down_left  = glm::vec2( uv_x           , (uv_y + 1.0f/16.0f) );
            UVs.push_back(uv_up_left   );
            UVs.push_back(uv_down_left );
            UVs.push_back(uv_up_right  );

            UVs.push_back(uv_down_right);
            UVs.push_back(uv_up_right);
            UVs.push_back(uv_down_left);
        }
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, mUVBuffer);
        glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);

        // Bind shader
        mShader->Use();

        // Bind texture
        glActiveTexture(GL_TEXTURE0);
        mTexture->Use();
        // Set our "myTextureSampler" sampler to user Texture Unit 0
        glUniform1i(mTextureSamplerUniform, 0);

        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

        // 2nd attribute buffer : UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, mUVBuffer);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GEQUAL, 0.3);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Draw call
        glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

        glDisable(GL_ALPHA_TEST);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }*/

    void Text2D::Print(int x, int y, float size, vec3 color, char* format, ...)
    {
        size_t bufferSize = strlen(format)+256;
        char buffer[bufferSize];

        va_list argptr;
        va_start(argptr, format);
        std::vsnprintf (buffer, bufferSize, format, argptr);
        va_end(argptr);

        std::string fText(buffer);
        Print(fText, x, y, size, color);
    }

    void Text2D::Print(std::string text, int x, int y, float size, vec3 color)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        float scale = size / mSize;

        // Activate corresponding render state
        mShader->Use();

        glUniform3fv(mShader->GetUniform("textColor"), 1, &color[0]);
        glUniform1i(mTextureSamplerUniform, 0);

        int width = mRenderer->ScreenWidth() / 2.0f;
        int height = mRenderer->ScreenHeight() / 2.0f;

        glActiveTexture(GL_TEXTURE0);


        glBindVertexArray(mVertexArray);

        // Iterate through all characters
        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++)
        {
            Character ch = mCharacters[*c];

            GLfloat xpos = x + ch.Bearing.x * scale;
            GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

            GLfloat w = ch.Size.x * scale;
            GLfloat h = ch.Size.y * scale;
            // Update VBO for each character
            GLfloat vertices[6][4] = {
                { (xpos-width) / width,      (ypos + h - height) / height,   0.0, 0.0 },
                { (xpos-width) / width,      (ypos - height) / height,       0.0, 1.0 },
                { (xpos + w -width) / width, (ypos - height) / height,       1.0, 1.0 },

                { (xpos-width) / width,      (ypos + h - height) / height,   0.0, 0.0 },
                { (xpos + w -width) / width, (ypos - height) / height,       1.0, 1.0 },
                { (xpos + w -width) / width, (ypos + h - height) / height,   1.0, 0.0 }
            };
            // Render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            // Update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // Render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glDisable(GL_BLEND);
    }

    void Text2D::Exit()
    {
        // Delete buffers
        glDeleteVertexArrays(1, &mVertexArray);
        glDeleteBuffers(1, &mVertexBuffer);
        glDeleteBuffers(1, &mUVBuffer);

        // Delete texture
        for(std::pair<const char, Character> ch : mCharacters)
        {
            glDeleteTextures(1, &ch.second.TextureID);
        }

        // Delete shader
        delete mShader;
    }
}
