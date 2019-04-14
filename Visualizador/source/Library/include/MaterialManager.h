#pragma once

#include "Common.h"
#include "Material.h"

#include <list>

struct aiMaterial;

namespace Library
{
    // Need to be ordered by draw priority
    enum MaterialType
    {
        MaterialTypeOpaquePass = 0,
        MaterialTypeSimpleDiffuse,

        MaterialTypeTranslucentPass,

        MaterialTypeSize
    };

    class MaterialManager
    {
    public:
        static const Material* CreateMaterial(std::string name, MaterialType type);
        static const Material* CreateMaterial(aiMaterial* assimpMaterial);

        static const Material* GetMaterial(std::string name);
        static void DeleteMaterial(std::string name);

        static void Clear();
    private:
        static std::list<Material*> mMaterialList;
    };

}
