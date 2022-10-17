#include "data.h" // - modified scene for easier use

const uint32_t DEFAULT_NUM_OF_ITERATIONS = 32;

class ModelWrapper
{
public:
    ModelWrapper();
    ModelWrapper(const char *file_name);
    ModelWrapper(const ModelWrapper &) = delete;
    ~ModelWrapper();

    void ImportModel(const char *file_name);
    void ExportModel(const char *format_name, const char *file_name);

    void SmoothSharpLedges(double sharp_ledge_parameter);

private:
    aiScene *scene; // only used for import and export.
    Data data; // stores vertices and faces
};