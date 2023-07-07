#pragma once
#include "Mesh.h"
#include <glm.hpp>

class VectorMesh :
    public Mesh
{
public: 
    VectorMesh();
    VectorMesh(double xPos);
    VectorMesh(double xPos, double yPos);
    VectorMesh(double xPos, double yPos, double zPos);
    VectorMesh(double xPos, double yPos, double zPos, glm::vec3 orig);
    glm::vec3 getCoordinates();
    glm::vec3 getOrigin();
    void drawVector();
    void renderVector();
    ~VectorMesh();

private:
    double x;
    double y;
    double z;
    glm::vec3 origin;
};

