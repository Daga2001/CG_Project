#pragma once

#include <GL\glew.h>
#include <vector>
#include <glm.hpp>

class PointMesh
{
public:
	PointMesh(std::vector<glm::vec3> pointList);
	void drawPoints();
	void renderPoints();
	void clearPoints();
	~PointMesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
	std::vector<glm::vec3> points;
};

