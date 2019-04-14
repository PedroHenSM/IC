#include "Shader.h"
#include "Utility.h"

#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Library
{
	char* Shader::mAttributesName[ShaderAttributesSize] =
	{
		(char*)"Position",
		(char*)"TexCoord",
		(char*)"Normal",
		(char*)"Tangent",
		(char*)"Bitangent",
		(char*)"Color"
	};

	Shader::Shader(std::string vertexShader, std::string fragmentShader)
	{
		GLchar* vertexShaderSource = ReadFile(vertexShader);
		GLchar* fragmentShaderSource = ReadFile(fragmentShader);

		mVertexShaderID = CreateShader(vertexShaderSource, GL_VERTEX_SHADER);
		mFragmentShaderID = CreateShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

		mID = glCreateProgram();

		glAttachShader(mID, mVertexShaderID);
		glAttachShader(mID, mFragmentShaderID);

		glLinkProgram(mID);

		GLint linked;
		glGetProgramiv(mID, GL_LINK_STATUS, &linked);

		if (!linked)
		{
			GLsizei len;
			glGetProgramiv(mID, GL_INFO_LOG_LENGTH, &len);

			GLchar* log(new GLchar[len + 1]);
			glGetProgramInfoLog(mID, len, &len, log);

			std::cerr << "Program linking error: " << log << std::endl;

			delete[] log;

			glDeleteShader(mVertexShaderID);
			glDeleteShader(mFragmentShaderID);

			glDeleteProgram(mID);
			mID = 0;
		}

		for (int i = 0; i < ShaderAttributesSize; i++)
		{
			mAttributes[i] = glGetAttribLocation(mID, mAttributesName[i]);
		}
		GetUniforms();
	}

	Shader::~Shader()
	{
		glDetachShader(mID, mVertexShaderID);
		glDetachShader(mID, mFragmentShaderID);
		glDeleteShader(mVertexShaderID);
		glDeleteShader(mFragmentShaderID);
		glDeleteProgram(mID);
	}

	void Shader::Use()
	{
		glUseProgram(mID);
	}

	GLuint Shader::ID() const
	{
		return mID;
	}

	GLint Shader::GetUniform(std::string uniformName) const
	{
		return glGetUniformLocation(mID, uniformName.c_str());
	}

	GLint Shader::GetAttribute(ShaderAttributes attribute) const
	{
		return mAttributes[attribute];
	}

	const std::map<std::string, GLuint>& Library::Shader::Uniforms() const
	{
		return mUniforms;
	}

	GLchar* Shader::ReadFile(std::string filePath)
	{
		std::string path = Utility::GetPath(filePath);
		//std::cout << "Path: " << path << std::endl;

		std::ifstream in(path.c_str(), std::ios::in | std::ios::binary);

		if (in.bad())
		{
			std::cerr << "Could not open shader file: " << filePath << std::endl;
			return NULL;
		}

		std::ostringstream content;
		content << in.rdbuf();

		in.close();

		std::string fileContent = content.str();

		char* source = new char[fileContent.length() + 1];
		strcpy(source, fileContent.c_str());
		source[fileContent.length()] = '\0';

		return source;
	}

	GLuint Shader::CreateShader(GLchar* sourceCode, int shaderType)
	{
		const GLchar* sourcePointer = sourceCode;

		GLuint subShaderID = glCreateShader(shaderType);
		glShaderSource(subShaderID, 1, &sourcePointer, NULL);
		glCompileShader(subShaderID);

		GLint compiled;
		glGetShaderiv(subShaderID, GL_COMPILE_STATUS, &compiled);

		if (!compiled)
		{
			GLsizei len;
			glGetShaderiv(subShaderID, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetShaderInfoLog(subShaderID, len, &len, log);

			switch (shaderType)
			{
			case GL_VERTEX_SHADER:
				std::cerr << "Vertex ";
				break;
			case GL_FRAGMENT_SHADER:
				std::cerr << "Fragment ";
				break;
			case GL_TESS_CONTROL_SHADER:
				std::cerr << "Tesselation Control ";
				break;
			case GL_TESS_EVALUATION_SHADER:
				std::cerr << "Tesselation Evaluation ";
				break;
			}

			std::cerr << "Shader compile error: " << log << std::endl;
			delete[] log;

			return 0;
		}

		delete[] sourceCode;
		sourceCode = nullptr;

		return subShaderID;
	}

	void Shader::GetUniforms()
	{
		GLint numUniforms = 0;
		glGetProgramiv(mID, GL_ACTIVE_UNIFORMS, &numUniforms);

		for (GLint i = 0; i < numUniforms; i++)
		{
			char uniformName[256];
			int length = 0;

			glGetProgramResourceName(mID, GL_UNIFORM, i, 256, &length, uniformName);
			mUniforms.insert(std::pair<std::string, GLint>(uniformName, i));
		}
	}

}
