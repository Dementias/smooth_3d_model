#include <assimp/scene.h> 
#include <vector>
#include <cmath>

double FindAngle (const aiVector3D &v1, const aiVector3D &v2)
{
    double cos_angle = (v1 * v2) / (sqrt(v1.SquareLength()) * sqrt(v2.SquareLength()));
    return acos(cos_angle);
}

template<typename T>
aiVector3D CenterOfMass(const T &vertices_indices, const std::vector<aiVector3D> &vertices_coords)
{
    aiVector3D center(0, 0, 0);
    for (const auto & vertex: vertices_indices)
    {
        center += vertices_coords[vertex];
    }
    center /= vertices_indices.size();
    return center;
}