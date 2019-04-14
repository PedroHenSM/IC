#pragma once

#include "Common.h"

namespace Library
{
    class RendererObject;
	class RendererTime;
	class Transform;
	class Camera;
	class Shader;

    typedef struct _AttributeInfo
    {
        GLuint attribType;
        GLuint components;
        GLuint glType;
        GLuint stride;
        void* offset;
    } AttributeInfo;

	class Material
	{

	public:
	    Material(std::string name);
		Material(std::string vertexShader, std::string fragmentShader);
		Material(Shader* shader);
		~Material();

        const std::string Name() const;

		virtual void Initialize();
		virtual void Setup(RendererObject &ro); //Inicializa parametros constantes
		virtual void Use(const RendererTime& rendererTime, Transform& transform, RendererObject &ro); //Atualiza parametros que mudam por frame

		GLuint Position() const;
		GLuint TexCoord() const;
		GLuint Normal() const;
		GLuint Tangent() const;
		GLuint Bitangent() const;

		unsigned int ID() const;

	protected:
		const unsigned int mID;

		GLuint mPosition;
		GLuint mTexCoord;
		GLuint mNormal;
		GLuint mTangent;
		GLuint mBitangent;

		GLuint mMVP;
		GLuint mMV;

		Shader* mShader;
	private:
	    std::string mName;
		bool mNeedToDeleteShader;
		std::string mVertexShaderPath, mFragmentShaderPath;
		static unsigned int IDgen;

		unsigned int mMeshUsing;

		Material(const Material& rhs);
		Material& operator=(const Material& rhs);
	};
}
