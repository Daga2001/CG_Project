#include "PointMesh.h"

/**
 * This is a constructor for a PointMesh object that takes in a vector of 3D points and sets the
 * object's "points" attribute to that vector.
 * 
 * @param pointList pointList is a vector of glm::vec3 objects that contains a list of points in 3D
 * space. This constructor initializes the "points" member variable of the PointMesh class with the
 * provided pointList.
 */
PointMesh::PointMesh(std::vector<glm::vec3> pointList)
{
	points = pointList;
}

/**
 * This function draws points in a 3D space using OpenGL.
 */
void PointMesh::drawPoints()
{
	// Get the total number of points and vertices.
	unsigned int numOfIndices = points.size(); // number of points
	unsigned int numOfVertices = numOfIndices * 3; // Each point has 3 coordinates.

	std::vector<GLfloat> pointVertices;
	for (unsigned int i = 0; i < numOfIndices; i++) {
		pointVertices.push_back(points[i].x);
		pointVertices.push_back(points[i].y);
		pointVertices.push_back(points[i].z);
	}

	std::vector<unsigned int> pointIndices(numOfIndices);
	for (unsigned int i = 0; i < numOfIndices; i++) {
		pointIndices[i] = i;
	}

	indexCount = numOfIndices;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pointIndices[0]) * numOfIndices, pointIndices.data(), GL_STATIC_DRAW);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pointVertices[0]) * numOfVertices, pointVertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/**
 * This function renders points using OpenGL.
 */
void PointMesh::renderPoints()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_POINTS, indexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

/**
 * The function clears the buffers and vertex arrays used for rendering a point mesh.
 */
void PointMesh::clearPoints()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	indexCount = 0;
}

/**
 * This is the destructor for the PointMesh class that clears all points.
 */
PointMesh::~PointMesh()
{
	clearPoints();
}