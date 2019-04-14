#include "MaterialManager.h"

#include <assimp/material.h>
#include <assimp/types.h>

namespace Library
{
    std::list<Material*> MaterialManager::mMaterialList = std::list<Material *>();

    const Material* MaterialManager::CreateMaterial(std::string name, MaterialType type)
    {
        // Check for existing material with the same name
        for(Material* matIt : mMaterialList)
        {
            if(matIt->Name() == name)
            {
                return matIt;
            }
        }

        switch(type)
        {
        case MaterialTypeSimpleDiffuse:
            {
                Material* mat = new Material(name);
                mMaterialList.push_back(mat);
                return mat;
            }
        default:
            return nullptr;
        }
    }

    const Material* MaterialManager::CreateMaterial(aiMaterial* assimpMaterial)
    {
        //From the assimp material, define witch material type to use
        // TODO

        //Get Material Name
        //aiString name;
        //assimpMaterial->Get(AI_MATKEY_NAME, name);

        //const Material *m = CreateMaterial(std::string(name.C_Str()), MaterialTypeSimpleDiffuse);

        //Set Parameters according to material

        // Then return the material
        //return m;
        return nullptr;
    }
}
