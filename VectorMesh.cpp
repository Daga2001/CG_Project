#include "VectorMesh.h"

/**
 * The VectorMesh constructor initializes the x, y, and z values to 1, 0, and 0 respectively, and sets
 * the origin to (0, 0, 0).
 */
VectorMesh::VectorMesh() : Mesh()
{
	x = 1;
	y = 0;
	z = 0;
	origin = glm::vec3(0.0f, 0.0f, 0.0f);
}

/**
 * This is a constructor for the VectorMesh class that initializes the x position and sets the y and z
 * positions to 0, and sets the origin to (0,0,0).
 * 
 * @param xPos xPos is a double value representing the x-coordinate of the VectorMesh object.
 */
VectorMesh::VectorMesh(double xPos) : Mesh()
{
	x = xPos;
	y = 0;
	z = 0;
	origin = glm::vec3(0.0f, 0.0f, 0.0f);
}

/**
 * This is a constructor for the VectorMesh class that initializes the x, y, and z positions and sets
 * the origin to (0,0,0).
 * 
 * @param xPos The x-coordinate of the position of the VectorMesh object being created.
 * @param yPos The parameter `yPos` is a double that represents the y-coordinate of the position of the
 * `VectorMesh` object being created.
 */
VectorMesh::VectorMesh(double xPos, double yPos) : Mesh()
{
	x = xPos;
	y = yPos;
	z = 0;
	origin = glm::vec3(0.0f, 0.0f, 0.0f);
}

/**
 * This is a constructor for the VectorMesh class that initializes the x, y, and z positions and sets
 * the origin to (0,0,0).
 * 
 * @param xPos The x-coordinate of the position of the VectorMesh object.
 * @param yPos The y-coordinate position of the VectorMesh object in 3D space.
 * @param zPos zPos is a double precision floating point number representing the z-coordinate of the
 * position of the VectorMesh object being created.
 */
VectorMesh::VectorMesh(double xPos, double yPos, double zPos) : Mesh()
{
	x = xPos;
	y = yPos;
	z = zPos;
	origin = glm::vec3(0.0f, 0.0f, 0.0f);
}

/**
 * This is a constructor for the VectorMesh class that initializes the x, y, z positions and origin
 * vector.
 * 
 * @param xPos The x-coordinate of the position of the VectorMesh object.
 * @param yPos The parameter `yPos` is a double that represents the y-coordinate of the position of the
 * `VectorMesh` object being created.
 * @param zPos zPos is a double precision floating point number representing the z-coordinate of the
 * position of the VectorMesh object in 3D space.
 * @param orig `orig` is a `glm::vec3` variable that represents the origin point of the `VectorMesh`.
 * It is a 3D vector that contains the x, y, and z coordinates of the origin point.
 */
VectorMesh::VectorMesh(double xPos, double yPos, double zPos, glm::vec3 orig) : Mesh()
{
	x = xPos;
	y = yPos;
	z = zPos;
	origin = orig;
}

/**
 * This function returns a 3D vector of coordinates.
 * 
 * @return A glm::vec3 object containing the x, y, and z coordinates of a point in 3D space.
 */
glm::vec3 VectorMesh::getCoordinates()
{
	return glm::vec3(x, y, z);
}

/**
 * This function returns the origin vector of a vector mesh.
 * 
 * @return A `glm::vec3` object representing the origin of the mesh.
 */
glm::vec3 VectorMesh::getOrigin()
{
	return origin;
}

/**
 * This function draws a vector using OpenGL by creating and binding vertex and index buffers.
 */
void VectorMesh::drawVector()
{
	float ox = origin.x;
	float oy = origin.y;
	float oz = origin.z;

	unsigned int numOfVertices = 6;
	unsigned int numOfIndices = 2;
	unsigned int vectorindices[] = {
		0, 1,
	};
	GLfloat vectorVertices[] = {
		//	x		y		z
			ox,		oy,		oz,
			x,		y,		z,
	};

	indexCount = numOfIndices;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vectorindices[0]) * numOfIndices, vectorindices, GL_STATIC_DRAW);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vectorVertices[0]) * numOfVertices, vectorVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/**
 * This function renders a vector mesh using OpenGL.
 */
void VectorMesh::renderVector()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_LINES, indexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

/**
 * This is a destructor for the VectorMesh class that clears the mesh.
 */
VectorMesh::~VectorMesh()
{
	ClearMesh();
}