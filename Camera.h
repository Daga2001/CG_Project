#pragma once

#include <GL\glew.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

#include <GLFW\glfw3.h>

class Camera
{
public:
	Camera();
	
	/**
	* StartPosition: posición inicial
	* StartUp: vector normal para indicar la inclinación inicial, se deja usualmente 1.0f en el eje y para que se muestren los ejes en su posición natural.
	* Si pusieramos por ejemplo 1.0f en el eje x, se vería dicho eje verticalmente, como si fuera el eje y.
	* startYaw: inclinación inicial Yaw (eje y)
	* startPitch: inclinación inicial Pitch (eje x)
	* StartMoveSpeed: Velocidad de movimiento
	* StartTurnSpeed: Velocidad de giro
	*/
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange);

	glm::vec3 getCameraPosition();
	glm::vec3 getCameraDirection();
	GLfloat getYaw();
	GLfloat getPitch();

	glm::mat4 calculateViewMatrix();

	~Camera();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat moveSpeed;
	GLfloat turnSpeed;

	void update();
};

