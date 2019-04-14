#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include "Shader.h"

namespace Library
{
    Mesh::Mesh ( Model& model, ModelMaterial* material ) :
        mModel(model),
        mMaterial(nullptr),
        mName( ),
        mVertexData( ),
        mIndexData( ),
        mVertexArray(0),
        mVertexBuffer(0),
        mIndexBuffer(0),
        mIndexCount(0),
        mVertexCount(0),
        mFaceCount(0),
        mAttributeInfo( )
    {
    }

    Mesh::Mesh ( Model& model, aiMesh& mesh ) :
        mModel(model),
        mMaterial(nullptr),
        mName( mesh.mName.C_Str() ),
        mVertexData( ),
        mIndexData( ),
        mVertexArray(0),
        mVertexBuffer(0),
        mIndexBuffer(0),
        mIndexCount(  mesh.mNumFaces * 3 ),
        mVertexCount( mesh.mNumVertices ),
        mFaceCount( mesh.mNumFaces ),
        mAttributeInfo( )
    {
        // Build material properties based in vertices properties
        unsigned int offset = 0;
        if(mesh.HasPositions())
        {
            AttributeInfo attInfo = {ShaderAttributes::ShaderAttributesPosition, 3, GL_FLOAT, 0, (void*)(intptr_t)offset};
            mAttributeInfo.push_back(attInfo);
            offset += 3 * sizeof(float);
        }
        if(mesh.HasTextureCoords(0))
        {
            AttributeInfo attInfo = {ShaderAttributes::ShaderAttributesTexCoodinates, 2, GL_FLOAT, 0, (void*)(intptr_t)offset};
            mAttributeInfo.push_back(attInfo);
            offset += 2 * sizeof(float);
        }
        if(mesh.HasNormals())
        {
            AttributeInfo attInfo = {ShaderAttributes::ShaderAttributesNormal, 3, GL_FLOAT, 0, (void*)(intptr_t)offset};
            mAttributeInfo.push_back(attInfo);
            offset += 3 * sizeof(float);
        }
        if(mesh.HasTangentsAndBitangents())
        {
            AttributeInfo attInfo = {ShaderAttributes::ShaderAttributesTangent, 3, GL_FLOAT, 0, (void*)(intptr_t)offset};
            mAttributeInfo.push_back(attInfo);
            offset += 3 * sizeof(float);
            AttributeInfo attInfo2 = {ShaderAttributes::ShaderAttributesBitangents, 3, GL_FLOAT, 0, (void*)(intptr_t)offset};
            mAttributeInfo.push_back(attInfo2);
            offset += 3 * sizeof(float);
        }
        // Update the stride in the AttributeInfo list
        for(size_t i = 0; i < mAttributeInfo.size(); i++)
        {
            mAttributeInfo[i].stride = offset;
        }

        // Read triangle vertices index
        for (unsigned int i = 0; i < mesh.mNumFaces; i++)
        {
            const aiFace& face = mesh.mFaces[i];
            mIndexData.push_back(face.mIndices[0]);
            mIndexData.push_back(face.mIndices[1]);
            mIndexData.push_back(face.mIndices[2]);
        }

        // Fill vertex data vector
        for(unsigned int i = 0; i < mesh.mNumVertices; i++)
        {
            if(mesh.HasPositions())
            {
                mVertexData.push_back(mesh.mVertices[i].x);
                mVertexData.push_back(mesh.mVertices[i].y);
                mVertexData.push_back(mesh.mVertices[i].z);
            }
            if(mesh.HasTextureCoords(0))
            {
                mVertexData.push_back(mesh.mTextureCoords[0][i].x);
                mVertexData.push_back(mesh.mTextureCoords[0][i].y);
            }
            if(mesh.HasNormals())
            {
                mVertexData.push_back(mesh.mNormals[i].x);
                mVertexData.push_back(mesh.mNormals[i].y);
                mVertexData.push_back(mesh.mNormals[i].z);
            }
            if(mesh.HasTangentsAndBitangents())
            {
                mVertexData.push_back(mesh.mTangents[i].x);
                mVertexData.push_back(mesh.mTangents[i].y);
                mVertexData.push_back(mesh.mTangents[i].z);

                mVertexData.push_back(mesh.mBitangents[i].x);
                mVertexData.push_back(mesh.mBitangents[i].y);
                mVertexData.push_back(mesh.mBitangents[i].z);
            }
        }

        glGenVertexArrays(1, &mVertexArray);
		glBindVertexArray(mVertexArray);

		glGenBuffers(1, &mVertexBuffer);
		glGenBuffers(1, &mIndexBuffer);

		glBindVertexArray(0);

		BufferData();

    }

    Mesh::~Mesh( )
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &mVertexBuffer);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &mIndexBuffer);

        glBindVertexArray(0);
        glDeleteVertexArrays(1, &mVertexArray);
    }

    void Mesh::BufferData()
    {
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*mVertexData.size(), mVertexData.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short)*mIndexData.size(), mIndexData.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        mVertexData.clear();
        mIndexData.clear();
    }

    Model& Mesh::GetModel( )
    {
        return mModel;
    }
    ModelMaterial* Mesh::GetMaterial()
    {
        return mMaterial;
    }

    const std::string& Mesh::Name ( ) const
    {
        return mName;
    }
    const std::vector< float >& Mesh::VertexData ( ) const
    {
        return mVertexData;
    }

    unsigned int Mesh::FaceCount ( ) const
    {
        return mFaceCount;
    }
    const std::vector<unsigned short>& Mesh::Indices ( ) const
    {
        return mIndexData;
    }

    void CreateIndexBuffer ( GLuint* indexBuffer )
    {
    }



}
