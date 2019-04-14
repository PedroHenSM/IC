#pragma once

#include "Common.h"
#include "Material.h"

struct aiMesh;

namespace Library
{
    class ModelMaterial;
    class Model;

    class Mesh
    {
        friend class Model;
        friend class Material;

    public:
        Mesh(Model& model, ModelMaterial* material);
        ~Mesh( );

        Model& GetModel( );
        ModelMaterial* GetMaterial();

        const std::string& Name ( ) const;
        const std::vector< float >& VertexData ( ) const;

        unsigned int FaceCount ( ) const;
        const std::vector<unsigned short>& Indices ( ) const;

        void CreateIndexBuffer ( GLuint* indexBuffer );

    private:
        Mesh ( Model& model, aiMesh& mesh );
        void BufferData();

        Mesh ( const Mesh& rhs );
        Mesh& operator= ( const Material& rhs );

        Model& mModel;
        ModelMaterial* mMaterial;

        std::string mName;
        std::vector< float > mVertexData;
        std::vector< GLushort > mIndexData;

        GLuint mVertexArray;
        GLuint mVertexBuffer;
        GLuint mIndexBuffer;

        unsigned int mIndexCount;
        unsigned int mVertexCount;
        unsigned int mFaceCount;

        std::vector< AttributeInfo > mAttributeInfo;
    };
}
