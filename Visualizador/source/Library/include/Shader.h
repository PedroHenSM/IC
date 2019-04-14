#pragma once

#include "Common.h"

namespace Library
{
	enum ShaderAttributes
	{
		ShaderAttributesPosition = 0,
		ShaderAttributesTexCoodinates,
		ShaderAttributesNormal,
		ShaderAttributesTangent,
		ShaderAttributesBitangents,
		ShaderAttributesColor,
		ShaderAttributesSize
	};

	class Shader
	{
	public:
		Shader(std::string vertexShader, std::string fragmentShader);
		~Shader();

		void Use();

		GLuint ID() const;

		GLint GetUniform(std::string uniformName) const;
		GLint GetAttribute(ShaderAttributes attribute) const;

		const std::map<std::string, GLuint>& Uniforms() const;

	private:
		GLuint mID;
		GLuint mVertexShaderID;
		GLuint mFragmentShaderID;

		GLuint mAttributes[ShaderAttributesSize];
		static char* mAttributesName[ShaderAttributesSize];

		std::map<std::string, GLuint> mUniforms;

		GLchar* ReadFile(std::string filePath);
		GLuint CreateShader(GLchar* sourceCode, int shaderType);
		void GetUniforms();

		Shader(const Shader& rhs);
		Shader& operator=(const Shader& rhs);

	};
}
