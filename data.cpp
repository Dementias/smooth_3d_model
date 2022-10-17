#include "data.h"

aiScene* Data::Export (aiScene *scene)
{
    for (uint32_t i = 0; i < meshes_.size(); ++i)
    {
        const auto &faces = meshes_[i].GetFaces();
        const auto &vertices = meshes_[i].GetVertices();
        
        scene->mMeshes[i]->mVertices = new aiVector3D[vertices.size()];
        scene->mMeshes[i]->mFaces = new aiFace[faces.size()];

        for (uint32_t j = 0; j < vertices.size(); ++j)
        {
            scene->mMeshes[i]->mVertices[j] = vertices[j];
        }

        for (uint32_t j = 0; j < faces.size(); ++j)
        {
            scene->mMeshes[i]->mFaces[j] = faces[j];
        }

        scene->mMeshes[i]->mNumVertices = vertices.size();
        scene->mMeshes[i]->mNumFaces = faces.size();
    }
    return scene;
}

void Data::ExtractDataFrom (aiScene *scene)
{
    if (meshes_.size() != 0)
    {
        meshes_.clear();
        meshes_.shrink_to_fit();
    }
    
    for (uint32_t i = 0; i < scene->mNumMeshes; ++i)
    {
        ModifiedMesh mesh;
        meshes_.push_back(mesh);
        meshes_[i].Set(scene->mMeshes[i]);

        // Free data info in scene
        delete[] scene->mMeshes[i]->mFaces;
        delete[] scene->mMeshes[i]->mVertices;
        scene->mMeshes[i]->mNumFaces = 0;
        scene->mMeshes[i]->mNumVertices = 0;
    }
}

void Data::SmoothSharpLedges (double sharp_ledge_parameter, uint32_t num_of_iterations)
{
    for (uint32_t i = 0; i < meshes_.size(); ++i)
    {
        meshes_[i].SmoothSharpLedges(sharp_ledge_parameter, num_of_iterations);
    }
}