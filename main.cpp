#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include "CommonValues.h"

#include "Window.h"
#include "Mesh.h"
#include "VectorMesh.h"
#include "Shader.h"
#include "Camera.h"
#include "MathOGL.h"
#include "CartesianMesh.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
#include "PointMesh.h"

#include "Model.h"

//--------------------------------------------------------------------------------------------------
// Creación de variables
//--------------------------------------------------------------------------------------------------

//Estado de camara
float initCameraX = -30.627256;
float initCameraY = 9.392557;
float initCameraZ = 20.028461;
float initCameraSpeed = 5.0f;
float initCameraSpeedRot = 0.5f;
float initPitch = -10.500000;
float initYaw = -35.500000;

// Estado de x-wing
/*
* Controles:
* 1 y 5: para avanzar el x-wing adelante
* 2 y 6: para ir hacía atras
* 4: bajar
* 3: subir
*/
float xWingPosX = 16.300026;
float xWingPosY = -6.199996;
float xWingPosZ = -4.399998;
float rot_x_wing = 28.300184;
float centerX = 18.500034f;
float centerY = -0.800000;
float centerZ = 3.199999;

// Algoritmos de rasterización
std::vector<glm::vec3> points;
std::string algorithm_name;
double ox = 0;
double oy = 0;
double oz = 0;
double oxf = 0;
double oyf = 0;
double ozf = 0;
double radius = 0;
double tolRadius = 20;
double timeBCA = 0;
double tolTimeBCA = 100;
unsigned int nVectors = 0;
unsigned int nVectorsDrawn = 0;
int widthWin = 800;
int heightWin = 600;
std::vector<VectorMesh*> vectorMeshList;
std::vector<PointMesh*> pointsList;
std::vector<PointMesh*> pointsDrawn;
std::vector<glm::vec3> point_tmp;
MathOGL mathGL = MathOGL();

// constante para convertir grados a radianes
const float toRadians = 3.14159265f / 180.0f;

// variables para proyección
const float nearPlane = 0.1f;
const float farPlane = 100.0f;
const float deltaPlane = glm::abs(farPlane - nearPlane);

// Ventana principal y shaders
Window mainWindow;
std::vector<Shader> shaderList;

// plano cartesiano
CartesianMesh* plane;

// Camara
Camera camera;

// Texturas
Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;

Material shinyMaterial;
Material dullMaterial;

// Modelos de objetos para crear escena
std::vector<Mesh*> meshList;
Model xwing;
Model blackhawk;
Model gear;
Model column, column2, column3;
Model rock, rock2, rock3, rock4;

// Tipos de luz
DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Variable para controlar mejor el movimiento de la camara
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag";

//--------------------------------------------------------------------------------------------------
// Métodos/Funciones auxiliares
//--------------------------------------------------------------------------------------------------

/**
 * This function takes a vector of 3D points and returns a reordered vector where each point is
 * adjacent to its closest neighbor.
 *
 * @param puntos a vector of glm::vec3 points that needs to be reordered in such a way that the points
 * are adjacent to each other based on their distance.
 *
 * @return A reordered vector of glm::vec3 points where each point is adjacent to the previous one.
 */
std::vector<glm::vec3> reorder_points_adjacent(std::vector<glm::vec3> puntos) {
	std::vector<glm::vec3> resultado;
	resultado.push_back(puntos[0]);

	while (resultado.size() < puntos.size()) {
		glm::vec3 ultimo_punto = resultado.back();
		float distancia_minima = FLT_MAX;
		glm::vec3 mejor_punto;
		for (glm::vec3 punto : puntos) {
			if (std::find(resultado.begin(), resultado.end(), punto) != resultado.end()) {
				// This point has been added to result
				continue;
			}
			float distancia = glm::distance(ultimo_punto, punto);
			if (distancia < distancia_minima) {
				distancia_minima = distancia;
				mejor_punto = punto;
			}
		}
		resultado.push_back(mejor_punto);
	}

	return resultado;
}


/**
 * The function draws vectors between points in a vector and adds them to a list.
 *
 * @param points A vector of glm::vec3 objects representing the points in 3D space that the vectors
 * will be drawn between.
 */
void drawVectors(std::vector<glm::vec3> points)
{
	double numberOfPoints = points.size();
	for (unsigned int i = 1; i < numberOfPoints; i++) {
		VectorMesh* vecs = new VectorMesh(points[i].x, points[i].y, points[i].z,
			glm::vec3(points[i - 1].x, points[i - 1].y, points[i - 1].z));
		vecs->drawVector();
		vectorMeshList.push_back(vecs);
		nVectors++;
	}
}

/**
 * This function draws vectors using Bresenham's algorithm based on a list of 3D points.
 *
 * @param points A vector of glm::vec3 points representing the endpoints of the vectors to be drawn
 * using Bresenham's line algorithm.
 */
void drawVectorsBresenh(std::vector<glm::vec3> points)
{
	double numberOfPoints = points.size();
	for (unsigned int i = 1; i < numberOfPoints; i++) {
		VectorMesh* vecs = new VectorMesh(points[i].x, points[i].y, points[i].z,
			glm::vec3(points[i - 1].x, points[i - 1].y, points[i - 1].z));
		vecs->drawVector();
		vectorMeshList.push_back(vecs);
		nVectors++;
	}
	// links final vector with initial one
	VectorMesh* vecs = new VectorMesh(points[0].x, points[0].y, points[0].z,
		glm::vec3(points[nVectors].x, points[nVectors].y, points[nVectors].z));
	vecs->drawVector();
	vectorMeshList.push_back(vecs);
	nVectors++;
}

/**
 * This function renders a list of vectors using their respective meshes.
 */
void renderVectors()
{
	for (unsigned int i = 0; i < nVectors; i++) {
		vectorMeshList[i]->renderVector();
	}
}


/**
 * This function draws a circle using the midpoint algorithm and reorders the points to cover all four
 * quadrants.
 *
 * @param x_center The x-coordinate of the center of the circle.
 * @param y_center The y-coordinate of the center of the circle.
 * @param points A vector of 3D points that represent the circumference of a circle.
 */
void drawMidPointCircle(double x_center, double y_center, std::vector<glm::vec3> points)
{
	// List of points to reorder points later
	std::vector<glm::vec3> listPoints;

	double numberOfPoints = points.size();
	// Quadrant - 1 x = +, y = +
	// we store here Quadrant 2's points
	listPoints.push_back(glm::vec3(-points[0].x + 2 * x_center, points[0].y, points[0].z));
	for (unsigned int i = 1; i < numberOfPoints; i++) {
		VectorMesh* vecs = new VectorMesh(points[i].x, points[i].y, points[i].z,
			glm::vec3(points[i - 1].x, points[i - 1].y, points[i - 1].z));
		vecs->drawVector();
		listPoints.push_back(glm::vec3(-points[i].x + 2 * x_center, points[i].y, points[i].z));
		//printf("point1: (%f, %f, %f)\n", points[i].x, points[i].y, points[i].z);
		vectorMeshList.push_back(vecs);
		nVectors++;
	}

	// reorder points
	points = reorder_points_adjacent(listPoints);
	listPoints.clear();

	// Quadrant - 2 x = -, y = +
	// we store here Quadrant 3's points
	// NOTE: x is store as it comes due to points vector has its x-axis values stored as negative.
	listPoints.push_back(glm::vec3(points[0].x, -points[0].y + 2 * y_center, points[0].z));
	for (unsigned int i = 1; i < numberOfPoints; i++) {
		VectorMesh* vecs = new VectorMesh(points[i].x, points[i].y, points[i].z,
			glm::vec3(points[i - 1].x, points[i - 1].y, points[i - 1].z));
		vecs->drawVector();
		listPoints.push_back(glm::vec3(points[i].x, -points[i].y + 2 * y_center, points[i].z));
		//printf("point2: (%f, %f, %f)\n", points[i].x, points[i].y, points[i].z);
		vectorMeshList.push_back(vecs);
		nVectors++;
	}

	// reorder points
	points = reorder_points_adjacent(listPoints);
	listPoints.clear();

	// Quadrant - 3 x = -, y = -
	// we store here Quadrant 4's points
	// NOTE: same logic applied as before, we must take into account the previous signs.
	listPoints.push_back(glm::vec3(-points[0].x + 2 * x_center, points[0].y, points[0].z));
	for (unsigned int i = 1; i < numberOfPoints; i++) {
		VectorMesh* vecs = new VectorMesh(points[i].x, points[i].y, points[i].z,
			glm::vec3(points[i - 1].x, points[i - 1].y, points[i - 1].z));
		vecs->drawVector();
		listPoints.push_back(glm::vec3(-points[i].x + 2 * x_center, points[i].y, points[i].z));
		//printf("point3: (%f, %f, %f)\n", points[i].x, points[i].y, points[i].z);
		vectorMeshList.push_back(vecs);
		nVectors++;
	}

	// reorder points
	points = reorder_points_adjacent(listPoints);
	listPoints.clear();

	// Quadrant - 4 x = +, y = -
	for (unsigned int i = 1; i < numberOfPoints; i++) {
		VectorMesh* vecs = new VectorMesh(points[i].x, points[i].y, points[i].z,
			glm::vec3(points[i - 1].x, points[i - 1].y, points[i - 1].z));
		vecs->drawVector();
		//printf("point4: (%f, %f, %f)\n", points[i].x, points[i].y, points[i].z);
		vectorMeshList.push_back(vecs);
		nVectors++;
	}
}

/**
 * The function renders a circle by rendering a list of vectors.
 */
void renderCircle()
{
	for (unsigned int i = 0; i < nVectors; i++) {
		vectorMeshList[i]->renderVector();
	}
}

/**
 * The function prints out the values of a 4x4 matrix.
 *
 * @param matrix The parameter "matrix" is a 4x4 matrix of type glm::mat4. It is a matrix used for
 * transformations in computer graphics, such as translation, rotation, and scaling. The function
 * "printMatrix" takes this matrix as input and prints its values to the console.
 */
void printMatrix(glm::mat4 matrix) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void calcAverageNormals(unsigned int * indices, unsigned int indiceCount, GLfloat * vertices, unsigned int verticeCount, 
						unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);
		
		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

void CreateObjects() 
{
	// Indices y vertices
	unsigned int indices[] = {		
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
	//	x      y      z			u	  v			nx	  ny    nz
		-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-deltaPlane, 0.0f, -deltaPlane,		0.0f, 0.0f,				0.0f, -1.0f, 0.0f,
		deltaPlane, 0.0f, -deltaPlane,		deltaPlane, 0.0f,		0.0f, -1.0f, 0.0f,
		-deltaPlane, 0.0f, deltaPlane,		0.0f, deltaPlane,		0.0f, -1.0f, 0.0f,
		deltaPlane, 0.0f, deltaPlane,		deltaPlane, deltaPlane,	0.0f, -1.0f, 0.0f
	};

	unsigned int surfaceIndices[] = {
		0, 2, 3,
		0, 3, 1,
	};

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	// Dibujar el suelo
	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	// Dibujar el plano cartesiano
	plane = new CartesianMesh(51, deltaPlane, deltaPlane);
	plane->drawPlane();

}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

void clearMemory()
{
	for (int i = 0; i < nVectors; i++)
	{
		delete vectorMeshList[i];
	}

	delete pointsList[0];

	pointsList.clear();
	vectorMeshList.clear();
	nVectors = 0;
}

//--------------------------------------------------------------------------------------------------
// Función principal
//--------------------------------------------------------------------------------------------------

int main()
{
	// Handles the input UI.
	std::cout << "Cual sera la velocidad de traslacion de la camara? (Se recomienda un valor de 5.0f):\n";
	std::cin >> initCameraSpeed;
	std::cout << "Cual sera la velocidad de rotacion de la camara? (Se recomienda un valor de 0.5f):\n";
	std::cin >> initCameraSpeedRot;

	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(initCameraX, initCameraY, initCameraZ), glm::vec3(0.0f, 1.0f, 0.0f), initYaw, initPitch, initCameraSpeed, initCameraSpeedRot);

	// Se cargan las texturas
	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();

	shinyMaterial = Material(4.0f, 256);
	dullMaterial = Material(0.3f, 4);

	// Se cargan los modelos
	xwing = Model();
	xwing.LoadModel("Models/x-wing.obj");

	blackhawk = Model();
	blackhawk.LoadModel("Models/uh60.obj");

	gear = Model();
	gear.LoadModel("Models/Gear2.obj");

	column = Model();
	column.LoadModel("Models/Tree_stump_002_RAW.obj");

	column2 = Model();
	column2.LoadModel("Models/Tree_stump_002_RAW.obj");

	column3 = Model();
	column3.LoadModel("Models/Tree_stump_002_RAW.obj");

	rock = Model();
	rock.LoadModel("Models/RockWalkway03.obj");

	rock2 = Model();
	rock2.LoadModel("Models/RockWalkway03.obj");

	rock3 = Model();
	rock3.LoadModel("Models/RockWalkway03.obj");

	rock4 = Model();
	rock4.LoadModel("Models/RockWalkway03.obj");

	// Se crean las luces del escenario
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f, 
								0.3f, 0.6f,
								0.0f, 0.0f, -1.0f);

	unsigned int pointLightCount = 0;
	pointLights[0] = PointLight(0.0f, 0.0f, 1.0f,
								0.0f, 0.1f,
								0.0f, 0.0f, 0.0f,
								0.3f, 0.2f, 0.1f);
	pointLightCount++;
	pointLights[1] = PointLight(0.0f, 1.0f, 0.0f,
								0.0f, 0.1f,
								-4.0f, 2.0f, 0.0f,
								0.3f, 0.1f, 0.1f);
	pointLightCount++;

	unsigned int spotLightCount = 0;
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
						0.0f, 2.0f,
						0.0f, 0.0f, 0.0f,
						0.0f, -1.0f, 0.0f,
						1.0f, 0.0f, 0.0f,
						20.0f);
	spotLightCount++;
	spotLights[1] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, -1.5f, 0.0f,
		-100.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		20.0f);
	spotLightCount++;

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	// Se define una proyección perspectiva para la escena.
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), nearPlane, farPlane);

	// Loop until window closed
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime(); // SDL_GetPerformanceCounter();
		deltaTime = now - lastTime; // (now - lastTime)*1000/SDL_GetPerformanceFrequency();
		lastTime = now;

		// Get + Handle User Input
		glfwPollEvents();

		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		// aquí se establece el color de fondo de la pantalla, cada valor está normalizado.
		glClearColor(0.6f, 0.8f, 1.0f, 0.15f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// se usan los shaders para gráficar la escena.
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;

		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		//--------------------------------------------------------------------------------------------------
		// Se renderizan los modelos
		//--------------------------------------------------------------------------------------------------
		// Suelo
		glm::mat4 model(1.0f);	

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dirtTexture.UseTexture();
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[0]->RenderMesh();

		//x-wing
		model = glm::mat4(1.0f);
		// Posición x-wing
		xWingPosX = camera.getCameraPosition().x + centerX;
		xWingPosY = camera.getCameraPosition().y + centerY;
		xWingPosZ = camera.getCameraPosition().z - centerZ;
		model = glm::translate(model, glm::vec3(xWingPosX, xWingPosY, xWingPosZ));
		// Giro de x-wing
		if (mainWindow.getsKeys()[GLFW_KEY_E])
		{
			rot_x_wing += 0.5f;
		}
		else if (mainWindow.getsKeys()[GLFW_KEY_Q])
		{
			rot_x_wing -= 0.5f;
		}
		// Movimiento de x-wing
		else if (mainWindow.getsKeys()[GLFW_KEY_1])
		{
			centerX += 0.1f;
		}
		else if (mainWindow.getsKeys()[GLFW_KEY_2])
		{
			centerX -= 0.1f;
		}
		else if (mainWindow.getsKeys()[GLFW_KEY_3])
		{
			centerY += 0.1f;
		}
		else if (mainWindow.getsKeys()[GLFW_KEY_4])
		{
			centerY -= 0.1f;
		}
		else if (mainWindow.getsKeys()[GLFW_KEY_5])
		{
			centerZ += 0.1f;
		}
		else if (mainWindow.getsKeys()[GLFW_KEY_6])
		{
			centerZ -= 0.1f;
		}
		if (rot_x_wing > 360.0f)
		{
			rot_x_wing = 0.0f;
		}
		else if (rot_x_wing < 0.0f)
		{
			rot_x_wing = 360.0f;
		}
		printf("x-wing -- rotation: %f, centerX: %f, centerY: %f, centerZ: %f \n", rot_x_wing, centerX, centerY, centerZ);
		model = glm::rotate(model, 82.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rot_x_wing * toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.006f, 0.006f, 0.006f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		xwing.RenderModel();

		// helicoptero blackhawk
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(5.0f, 2.0f, 0.0f));
		model = glm::rotate(model, -90.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		blackhawk.RenderModel();

		// engranaje
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 9.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		gear.RenderModel();

		// Columnas
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(7.0f, -2.0f, -7.0f));
		model = glm::scale(model, glm::vec3(40.0f, 40.0f, 40.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		column.RenderModel();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-6.0f, -2.0f, -7.0f));
		model = glm::scale(model, glm::vec3(40.0f, 40.0f, 40.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		column2.RenderModel();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 7.0f));
		model = glm::scale(model, glm::vec3(40.0f, 40.0f, 40.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		column3.RenderModel();

		// Rocas del suelo
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.3f, 9.0f));
		model = glm::rotate(model, -180.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		rock.RenderModel();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(9.0f, -1.3f, 0.0f));
		model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		rock2.RenderModel();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-9.0f, -1.3f, 0.0f));
		model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		rock3.RenderModel();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.3f, -9.0f));
		model = glm::rotate(model, 180.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		rock4.RenderModel();

		// Dibujar puntos con la tecla f.
		if (mainWindow.getsKeys()[GLFW_KEY_F])
		{
			point_tmp.push_back(glm::vec3(
				-(camera.getCameraPosition().x + initCameraX) * (initCameraSpeed + initCameraSpeedRot),
				 (camera.getCameraPosition().y + initCameraY) * (initCameraSpeed + initCameraSpeedRot),
				-(camera.getCameraPosition().z - 1.0 + initCameraZ) * (initCameraSpeed + initCameraSpeedRot)
			));
			PointMesh* pointDrawn = new PointMesh(point_tmp);
			pointDrawn->drawPoints();
			pointsDrawn.push_back(pointDrawn);
			nVectorsDrawn += 1;
			printf("pointsDrawn: %d \n", pointsDrawn.size());
		}

		if (nVectorsDrawn > 0)
		{
			pointsDrawn[nVectorsDrawn - 1]->renderPoints();
		}

		// Borrar los puntos dibujados con la tecla f, usando la tecla c.
		if (mainWindow.getsKeys()[GLFW_KEY_C])
		{
			for (int i = 0; i < nVectorsDrawn; i++)
			{
				delete pointsDrawn[i];
			}
			point_tmp.clear();
			pointsDrawn.clear();
			nVectorsDrawn = 0;
		}

		// Dibujar Circulo con algoritmo BCA (Bresenham circle algorithm).
		ox = 50.0f;
		oy = 130.0f;

		if (radius < tolRadius)
		{
			radius += 1.0f;
		}
		else if (radius >= tolRadius)
		{
			radius = 0.0f;
		}

		points = mathGL.BresenhamCircle(ox, oy, radius, 50);
		points = reorder_points_adjacent(points);

		PointMesh* pointMesh = new PointMesh(points);
		pointMesh->drawPoints();
		pointsList.push_back(pointMesh);

		drawVectorsBresenh(points);

		// Renderizar circulo con algoritmo BCA (Bresenham circle algorithm).
		renderVectors();
		pointsList[0]->renderPoints();
		clearMemory();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}