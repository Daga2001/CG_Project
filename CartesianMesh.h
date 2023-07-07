#pragma once
#include "Mesh.h"
#include "VectorMesh.h"
#include <vector>
#include <glm.hpp>

class CartesianMesh :
    public Mesh
{
public:
    CartesianMesh(double xPos, double yPos);
    CartesianMesh(double xPos, double yPos, double zPos);
    void drawPlane();
    void renderPlane();
    glm::vec3 getDim();
    ~CartesianMesh();
private:
    double x;
    double y;
    double z;
    std::vector<VectorMesh*> vectorMeshList;
};

