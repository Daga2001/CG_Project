#include "CartesianMesh.h"

CartesianMesh::CartesianMesh(double xPos, double yPos) : Mesh()
{
	x = xPos;
	y = yPos;
	z = 0;
	if (x <= 50 || y <= 50)
	{
		throw std::exception("Invalid coordinate, please provide a value greater than 50!");
	}
}


CartesianMesh::CartesianMesh(double xPos, double yPos, double zPos) : Mesh()
{
	x = xPos;
	y = yPos;
	z = zPos;
	if (x <= 50 || y <= 50 || z <= 50)
	{
		throw std::exception("Invalid coordinate, please provide a value greater than 50!");
	}
}

void CartesianMesh::drawPlane() 
{
	//makes a X-axis in cartesian plane
	VectorMesh* obj3 = new VectorMesh(x, 0.0f, 0.0f, glm::vec3(-x, 0.0f, 0.0f));
	obj3->drawVector();
	vectorMeshList.push_back(obj3);

	//makes a Y-axis in cartesian plane
	VectorMesh* obj4 = new VectorMesh(0.0f, y, 0.0f, glm::vec3(0.0f, -y, 0.0f));
	obj4->drawVector();
	vectorMeshList.push_back(obj4);

	//makes a Z-axis in cartesian plane
	VectorMesh* obj5 = new VectorMesh(0.0f, 0.0f, z, glm::vec3(0.0f, 0.0f, -z));
	obj5->drawVector();
	vectorMeshList.push_back(obj5);
}

void CartesianMesh::renderPlane()
{
	vectorMeshList[0]->renderVector();
	vectorMeshList[1]->renderVector();
	vectorMeshList[2]->renderVector();
}

glm::vec3 CartesianMesh::getDim()
{
	glm::vec3 dimension = glm::vec3(x, y, z);
	return dimension;
}

CartesianMesh::~CartesianMesh()
{
	ClearMesh();
}