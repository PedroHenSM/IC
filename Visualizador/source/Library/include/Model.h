#pragma once

#include "Common.h"

namespace Library
{
    class Renderer;
    class Mesh;
    class ModelMaterial;

    class Model
    {
        friend class Mesh;

    public:
        Model(Renderer& renderer, const std::string& filename, bool flipUVs = true, bool calcTangentSpace = true);
        ~Model();

        Renderer &GetRenderer();
        bool HasMashes() const;
        bool HasMaterials() const;

        const std::vector<Mesh*>& Meshes() const;
        const std::vector<ModelMaterial*>& Materials() const;

    private:
        Model(const Model& rhs);
        Model& operator=(const Model& rhs);

        Renderer& mRenderer;
        std::vector<Mesh*> mMeshes;
        //std::vector<ModelMaterial*> mMaterials;
    };
}
