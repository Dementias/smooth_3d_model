#include "model_wrapper.h"

ModelWrapper::ModelWrapper(): scene(nullptr)
{}

ModelWrapper::ModelWrapper(const char *file_name)
{
    Assimp::Importer importer;
    const aiScene * ai_scene = importer.ReadFile(file_name, aiProcess_Triangulate);
    scene = importer.GetOrphanedScene();
    data.ExtractDataFrom(scene);
}

ModelWrapper::~ModelWrapper()
{
    delete scene;
}

void ModelWrapper::ImportModel(const char *file_name)
{
    delete scene;
    Assimp::Importer importer;
    const aiScene * ai_scene = importer.ReadFile(file_name, aiProcess_Triangulate);
    if (!ai_scene) {
        throw std::runtime_error("Import Error");
    }
    scene = importer.GetOrphanedScene();
    data.ExtractDataFrom(scene);
}

void ModelWrapper::ExportModel(const char *format_name, const char *file_name)
{
    Assimp::Exporter exporter;
    aiScene *sc = data.Export(scene);
    exporter.Export(sc, format_name, file_name);
}

void ModelWrapper::SmoothSharpLedges(double sharp_ledge_parameter)
{
    data.SmoothSharpLedges(sharp_ledge_parameter, DEFAULT_NUM_OF_ITERATIONS);
}