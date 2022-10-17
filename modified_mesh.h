#include <vector>
#include <cmath>
#include <set>
#include <stack>

#include <assimp/Importer.hpp>      // importer interface
#include <assimp/Exporter.hpp>      // exporter interface
#include <assimp/postprocess.h>     // post processing flags
#include <assimp/scene.h>           // data structures

const double MOVE_RATIO = 0.75;

class ModifiedMesh
{
public:
    ModifiedMesh() = default;
    ~ModifiedMesh() = default;

    double SumVertexAngle(uint32_t vertex_index);

    void Set(aiMesh *mesh);

    const std::vector<aiFace>& GetFaces() const;
    const std::vector<aiVector3D>& GetVertices() const;
    void SmoothSharpLedges(double sharp_ledge_parameter, uint32_t num_of_iterations);

    void Clear();

private:
    std::vector<std::set<uint32_t>> edges_; // edges[i] represents all faces containing i-th vertex
    std::vector<aiFace>  faces_;
    std::vector<aiVector3D> vertices_;

    void MoveVertex(uint32_t vertex_index, std::set<uint32_t>& adjacent_vertices, double gamma);    
};