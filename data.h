#include "modified_mesh.h"

class Data
{
public:
    Data() = default;
    ~Data() = default;

    // Moves Mesh data from scene to Data structure. Invalidates scene ptr
    void ExtractDataFrom (aiScene *scene);
    
    // Exports data back to scene
    aiScene *Export (aiScene *scene);

    void SmoothSharpLedges (double sharp_ledge_parameter, uint32_t num_of_iterations);
    
private:
    std::vector<ModifiedMesh> meshes_;        
};