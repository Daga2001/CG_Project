#pragma once
#include <glm.hpp>
#include <vector>
#include <algorithm>

class MathOGL
{
public:
	MathOGL();
	glm::vec3 vecSum(glm::vec3 vec1, glm::vec3 vec2);
	glm::vec3 vectorSubtraction(glm::vec3 vec1, glm::vec3 vec2);
	glm::vec3 scalarMultiplication(glm::vec3 vec1, double escalar);
	glm::vec3 crossProduct(glm::vec3 vec1, glm::vec3 vec2);
	double dotProduct(glm::vec3 vec1, glm::vec3 vec2);
	glm::vec3 scalarDivision(glm::vec3 vec1, double escalar);
	double angleBetween(glm::vec3 vec1, glm::vec3 vec2);
	glm::vec3 normalize(glm::vec3 vec1);
	glm::mat4 translate(glm::vec3 t);
	std::vector<glm::vec3> drawLineBasic(double x1, double y1, double x2, double y2);
	std::vector<glm::vec3> drawLineBres(double x1, double y1, double x2, double y2);
	std::vector<glm::vec3> drawLineDDA(double x1, double y1, double x2, double y2);
	std::vector<glm::vec3> midPointCircleDraw(double x_centre, double y_centre, double r);
	std::vector<glm::vec3> BresenhamCircle(double x_center, double y_center, double r, double z);

	~MathOGL();

private:
	void BresenhamCirclePoints(double x_center, double y_center, double x, double y, double z, std::vector<glm::vec3>& points );
	static bool compareVecByElems(const glm::vec3& a, const glm::vec3& b);

};

