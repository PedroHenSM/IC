#include "Mesh.h"
#include "Utility.h"
#include "VectorHelper.h"
#include "Material.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Library
{
	const GLsizei Mesh::vertexStride = 14 * sizeof(GLfloat);
	const void* Mesh::positionOffset = 0;
	const void* Mesh::uvOffset = (void*)(3 * sizeof(GLfloat));
	const void* Mesh::normalOffset = (void*)(5 * sizeof(GLfloat));
	const void* Mesh::tangentOffset = (void*)(8 * sizeof(GLfloat));
	const void* Mesh::bitangentOffset = (void*)(11 * sizeof(GLfloat));

	Mesh::Mesh()
		: mVertexArrayID(0), mVertexBuffer(0), mIndexBuffer(0),
		  mVertexData(), mIndexData(), mNeedToBuffer(false)
	{}

	Mesh::Mesh(std::vector<GLfloat> vertexData, std::vector<GLushort> indexData)
		: mVertexArrayID(0), mVertexBuffer(0), mIndexBuffer(0),
		  mVertexData(vertexData), mIndexData(indexData), mNeedToBuffer(false)
	{}

	Mesh::Mesh(std::string filePath)
		: mVertexArrayID(0), mVertexBuffer(0), mIndexBuffer(0),
		  mVertexData(), mIndexData(), mNeedToBuffer(true)
	{
		Assimp::Importer importer;
		unsigned int loadFlags = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs | aiProcess_CalcTangentSpace;

		const aiScene *scene = importer.ReadFile(Utility::GetPath(filePath), loadFlags);

		if (!scene)
		{
			throw RendererException("Assimp::Importer::ReadFile() failed.");
		}

		unsigned int meshStart = 0;

		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh& mesh = *scene->mMeshes[i];
			int iMeshFaces = mesh.mNumFaces;

			for (int j = 0; j < iMeshFaces; j++)
			{
				const aiFace& face = mesh.mFaces[j];
				PushFace(face.mIndices[0] + meshStart, face.mIndices[1] + meshStart, face.mIndices[2] + meshStart);
			}

			for (unsigned int j = 0; j < mesh.mNumVertices; j++)
			{
				vec3 aiPos = VectorHelper::Vec3Cast(mesh.mVertices[j]);
				vec3 aiUV = mesh.HasTextureCoords(0) ? VectorHelper::Vec3Cast(mesh.mTextureCoords[0][j]) : vec3(0,0,0);
				vec3 aiNormal, aiTangent, aiBitangent;
				if (mesh.HasNormals())
				{
					aiNormal = VectorHelper::Vec3Cast(mesh.mNormals[j]);
					aiTangent = VectorHelper::Vec3Cast(mesh.mTangents[j]);
					aiBitangent = VectorHelper::Vec3Cast(mesh.mBitangents[j]);
				}
				else
				{
					aiNormal = VectorHelper::Up;
					aiTangent = VectorHelper::Forward;
					aiBitangent = VectorHelper::Right;
				}

				PushVertex(aiPos, aiUV, aiNormal, aiTangent, aiBitangent);
			}

			meshStart += mesh.mNumVertices;
		}
	}

	Mesh::~Mesh()
	{
		glDeleteVertexArrays(1, &mVertexArrayID);
		glDeleteBuffers(1, &mVertexBuffer);
		glDeleteBuffers(1, &mIndexBuffer);
	}

	void Mesh::Initialize()
	{
		glGenVertexArrays(1, &mVertexArrayID);
		glBindVertexArray(mVertexArrayID);

		glGenBuffers(1, &mVertexBuffer);
		glGenBuffers(1, &mIndexBuffer);

		if ((!mVertexData.empty() && !mIndexData.empty()) || mNeedToBuffer)
		{
			BufferData();
		}

		glBindVertexArray(0);

	}

	const std::vector<GLfloat>& Mesh::VertexData() const
	{
		return mVertexData;
	}

	const std::vector<GLushort>& Mesh::IndexData() const
	{
		return mIndexData;
	}

	void Mesh::PushFace(GLushort a, GLushort b, GLushort c)
	{
		mNeedToBuffer = true;

		mIndexData.push_back(a);
		mIndexData.push_back(b);
		mIndexData.push_back(c);
	}

	void Mesh::PushFace(GLushort a, GLushort b, GLushort c, GLushort d)
	{
		mNeedToBuffer = true;

		mIndexData.push_back(a);
		mIndexData.push_back(b);
		mIndexData.push_back(c);

		mIndexData.push_back(a);
		mIndexData.push_back(c);
		mIndexData.push_back(d);
	}

	GLushort Mesh::PushVertex(vec3 & pos, vec3 & uv, vec3 & normal)
	{
		mNeedToBuffer = true;

		mVertexData.push_back(pos.x);
		mVertexData.push_back(pos.y);
		mVertexData.push_back(pos.z);
		mVertexData.push_back(uv.x);
		mVertexData.push_back(uv.y);
		mVertexData.push_back(normal.x);
		mVertexData.push_back(normal.y);
		mVertexData.push_back(normal.z);

		vec3 t = cross(VectorHelper::Right, normal);
		vec3 t2 = cross(VectorHelper::Forward, normal);
		if (t.length() >= t2.length())
		{
			vec3 b = cross(t, normal);
			mVertexData.push_back(t.x);
			mVertexData.push_back(t.y);
			mVertexData.push_back(t.z);
			mVertexData.push_back(b.x);
			mVertexData.push_back(b.y);
			mVertexData.push_back(b.z);
		}
		else
		{
			vec3 b = cross(t2, normal);
			mVertexData.push_back(t2.x);
			mVertexData.push_back(t2.y);
			mVertexData.push_back(t2.z);
			mVertexData.push_back(b.x);
			mVertexData.push_back(b.y);
			mVertexData.push_back(b.z);
		}

		return ((GLushort)mVertexData.size() / 14) - 1;
	}

	GLushort Mesh::PushVertex(vec3 & pos, vec3 & uv, vec3 & normal, vec3 & tangent, vec3 & bitangent)
	{
		mNeedToBuffer = true;

		mVertexData.push_back(pos.x);
		mVertexData.push_back(pos.y);
		mVertexData.push_back(pos.z);
		mVertexData.push_back(uv.x);
		mVertexData.push_back(uv.y);
		mVertexData.push_back(normal.x);
		mVertexData.push_back(normal.y);
		mVertexData.push_back(normal.z);
		mVertexData.push_back(tangent.x);
		mVertexData.push_back(tangent.y);
		mVertexData.push_back(tangent.z);
		mVertexData.push_back(bitangent.x);
		mVertexData.push_back(bitangent.y);
		mVertexData.push_back(bitangent.z);

		return ((GLushort)mVertexData.size() / 14) - 1;
	}

	void Mesh::SetMaterial(Material & material)
	{

		glBindVertexArray(mVertexArrayID);

		glEnableVertexAttribArray(material.Position());
		glEnableVertexAttribArray(material.TexCoord());

		if (material.Normal() != 0)
		{
			glEnableVertexAttribArray(material.Normal());
			glEnableVertexAttribArray(material.Tangent());
			glEnableVertexAttribArray(material.Bitangent());
		}

		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);

		glVertexAttribPointer(
			material.Position(),
			3,
			GL_FLOAT,
			GL_FALSE,
			vertexStride,
			positionOffset
			);

		glVertexAttribPointer(
			material.TexCoord(),
			2,
			GL_FLOAT,
			GL_FALSE,
			vertexStride,
			uvOffset
			);

		if (material.Normal() != 0)
		{
			glVertexAttribPointer(
				material.Normal(),
				3,
				GL_FLOAT,
				GL_FALSE,
				vertexStride,
				normalOffset
				);

			glVertexAttribPointer(
				material.Tangent(),
				3,
				GL_FLOAT,
				GL_FALSE,
				vertexStride,
				tangentOffset
				);

			glVertexAttribPointer(
				material.Bitangent(),
				3,
				GL_FLOAT,
				GL_FALSE,
				vertexStride,
				bitangentOffset
				);
		}

	}

	void Mesh::Draw(Material& material, RendererTime & rendererTime)
	{
		if (mNeedToBuffer)
		{
			BufferData();
			return;
		}

		glBindVertexArray(mVertexArrayID);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
		glDrawElements(GL_TRIANGLES, mIndexData.size(), GL_UNSIGNED_SHORT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

	}

	void Mesh::BufferData()
	{
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*mVertexData.size(), mVertexData.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*mIndexData.size(), mIndexData.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		mNeedToBuffer = false;
	}



}
