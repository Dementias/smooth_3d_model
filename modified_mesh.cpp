#include "modified_mesh.h"
#include "utils.h"
#include <iostream>

const std::vector<aiFace>& ModifiedMesh::GetFaces() const
{
    return faces_;
}

const std::vector<aiVector3D>& ModifiedMesh::GetVertices() const
{
    return vertices_;
}

void ModifiedMesh::Clear()
{
    edges_.clear();
    edges_.shrink_to_fit();
    faces_.clear();
    faces_.shrink_to_fit();
    vertices_.clear();
    vertices_.shrink_to_fit();
}

void ModifiedMesh::Set (aiMesh *mesh)
{
    if (vertices_.size() != 0)
    {
        Clear();
    }

    for (uint32_t i = 0; i < mesh->mNumVertices; ++i)
    {
        vertices_.push_back(mesh->mVertices[i]);
    }

    for (uint32_t i = 0; i < mesh->mNumVertices; ++i)
    {
        edges_.push_back(std::set<uint32_t>());
    }

    for (uint32_t i = 0; i < mesh->mNumFaces; ++i)
    {
        faces_.push_back(mesh->mFaces[i]);

        edges_[mesh->mFaces[i].mIndices[0]].insert(i);
        edges_[mesh->mFaces[i].mIndices[1]].insert(i);
        edges_[mesh->mFaces[i].mIndices[2]].insert(i);
    }
}

double ModifiedMesh::SumVertexAngle (uint32_t vertex_index)
{
    double angle = 0;
    aiVector3D a, b, c;

    for (const auto & triangle_index: edges_[vertex_index])
    {
        for (int j = 0; j < 3; ++j)
        {
            if (faces_[triangle_index].mIndices[j] == vertex_index)
            {
                // Puts vertex with vertex_index into variable "a" and others in b and c
                auto vect = faces_[triangle_index].mIndices;
                a = vertices_[vect[j]];
                b = vertices_[vect[(j + 1) % 3]];
                c = vertices_[vect[(j + 2) % 3]];
                break;
            }
        }

        // Finds angle between vectors ac and ab
        b -= a;
        c -= a;
        auto current_angle = FindAngle(b, c);
        angle += current_angle;
    }

    return angle;
}

// Moves vertex to new coords so that the ledge is no more sharp
void ModifiedMesh::MoveVertex(uint32_t vertex_index, std::set<uint32_t>& adjacent_vertices, double gamma) 
{
    auto add_vector = CenterOfMass(adjacent_vertices, vertices_);
    add_vector -= vertices_[vertex_index];
    add_vector *=  (1 - gamma * MOVE_RATIO);
    vertices_[vertex_index] += add_vector;
}

void ModifiedMesh::SmoothSharpLedges (double sharp_ledge_parameter, uint32_t num_of_iterations)
{
    double sharp_ledge_angle = 2 * M_PI * sharp_ledge_parameter;

    for (uint32_t i = 0; i < num_of_iterations; ++i)
    {
        std::cout << i * 100 / num_of_iterations << "%" << std::endl;
        uint32_t N = vertices_.size();
        
        // process the vertices_ one by one
        while(N--)
        {
            auto current_vertex = N;
            double angle = SumVertexAngle(current_vertex);

            if (angle < sharp_ledge_angle)
            {
                double gamma = angle / sharp_ledge_angle;
                std::set<uint32_t> adjacent_vertices;

                for (const auto & triangle: edges_[current_vertex])
                {
                    adjacent_vertices.insert(faces_[triangle].mIndices[0]);
                    adjacent_vertices.insert(faces_[triangle].mIndices[1]);
                    adjacent_vertices.insert(faces_[triangle].mIndices[2]);
                }

                MoveVertex(current_vertex, adjacent_vertices, gamma);
            }
        }
    }
}
