#include "Model.h"
#include "Renderer.h"
#include "RendererException.h"
#include "Utility.h"
#include "Mesh.h"
#include "ModelMaterial.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Library
{
    Model::Model( Renderer& renderer, const std::string& filename, bool flipUVs, bool calcTangentSpace )
        : mRenderer( renderer ), mMeshes( )//, mMaterials( )
    {
        Assimp::Importer importer;

        unsigned int flags = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices |
                             aiProcess_SortByPType;
        if ( flipUVs )
        {
            flags |= aiProcess_FlipUVs;
        }
        if ( calcTangentSpace )
        {
            flags |= aiProcess_CalcTangentSpace;
        }

        const aiScene* scene = importer.ReadFile( Utility::GetPath(filename), flags );

        if ( scene == nullptr )
        {
            throw RendererException( importer.GetErrorString( ) );
        }

        /*if ( scene->HasMaterials( ) )
        {
            for( unsigned int i = 0; i < scene->mNumMaterials; i++ )
            {
                mMaterials.push_back( new ModelMaterial( *this, scene->mMaterials[i] ) );
            }
        }*/

        if ( scene->HasMeshes( ) )
        {
            for ( unsigned int i = 0; i < scene->mNumMeshes; i++ )
            {
                Mesh* mesh = new Mesh( *this, *( scene->mMeshes[i] ) );
                mMeshes.push_back(mesh);
            }
        }
    }

    Model::~Model( )
    {
        for ( Mesh* mesh : mMeshes )
        {
            delete mesh;
        }

        /*for ( ModelMaterial* material : mMaterials )
        {
            delete material;
        }*/
    }

    Renderer& Model::GetRenderer( )
    {
        return mRenderer;
    }

    bool Model::HasMashes( ) const
    {
        return ( mMeshes.size( ) > 0 );
    }

    /*bool Model::HasMaterials( ) const
    {
        return ( mMaterials.size( ) > 0 );
    }*/

    const std::vector<Mesh*>& Model::Meshes() const
    {
        return mMeshes;
    }

    /*const std::vector< ModelMaterial* >& Model::Materials( ) const
    {
        return mMaterials;
    }*/
}
