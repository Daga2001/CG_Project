#include "MathOGL.h"

/**
 * This is the constructor for the MathOGL class in C++.
 */
MathOGL::MathOGL()
{

}

/**
 * The function takes two 3D vectors as input and returns their sum as a new 3D vector.
 * 
 * @param vec1 The first vector to be added.
 * @param vec2 The second vector that will be added to the first vector (vec1) in order to calculate
 * the sum of the two vectors.
 * 
 * @return The function `vecSum` returns a `glm::vec3` object which is the sum of the two input
 * `glm::vec3` objects `vec1` and `vec2`.
 */
glm::vec3 MathOGL::vecSum(glm::vec3 vec1, glm::vec3 vec2)
{
	return glm::vec3(
		vec1.x + vec2.x,
		vec1.y + vec2.y,
		vec1.z + vec2.z
	);
}

/**
 * The function performs vector subtraction between two 3D vectors using the glm library in C++.
 * 
 * @param vec1 A 3D vector representing the first vector in the subtraction operation.
 * @param vec2 The second vector that will be subtracted from the first vector (vec1) in order to
 * calculate the resulting vector.
 * 
 * @return The function `vectorSubtraction` returns a `glm::vec3` which is the result of subtracting
 * `vec2` from `vec1` component-wise.
 */
glm::vec3 MathOGL::vectorSubtraction(glm::vec3 vec1, glm::vec3 vec2)
{
	return glm::vec3(
		vec1.x - vec2.x,
		vec1.y - vec2.y,
		vec1.z - vec2.z
	);
}

/**
 * The function performs scalar multiplication on a 3D vector using a given scalar value.
 * 
 * @param vec1 A 3D vector represented as a glm::vec3 object.
 * @param escalar The parameter "escalar" is a double precision floating point number that represents
 * the scalar value to multiply with the given vector "vec1".
 * 
 * @return a new `glm::vec3` object that is the result of multiplying each component of the input
 * vector `vec1` by the scalar value `escalar`.
 */
glm::vec3 MathOGL::scalarMultiplication(glm::vec3 vec1, double escalar)
{
	return glm::vec3(
		vec1.x * escalar,
		vec1.y * escalar,
		vec1.z * escalar
	);
}

/**
 * The function calculates the cross product of two 3D vectors using the formula for cross product.
 * 
 * @param vec1 A 3D vector representing the first vector in the cross product operation.
 * @param vec2 The second vector used in the cross product calculation.
 * 
 * @return the cross product of two 3D vectors, which is a new vector that is perpendicular to both
 * input vectors. The cross product is calculated using the formula:
 */
glm::vec3 MathOGL::crossProduct(glm::vec3 vec1, glm::vec3 vec2)
{
	return glm::vec3(
		vec1.y * vec2.z - vec1.z * vec2.y,
		vec1.z * vec2.x - vec1.x * vec2.z,
		vec1.x * vec2.y - vec1.y * vec2.x
	);
}

/**
 * The function calculates the dot product of two 3D vectors using their x, y, and z components.
 * 
 * @param vec1 A 3D vector represented by the glm::vec3 class, containing the x, y, and z components of
 * the vector.
 * @param vec2 The second vector in the dot product calculation. It is a glm::vec3 type, which
 * represents a 3-dimensional vector with x, y, and z components.
 * 
 * @return the dot product of two 3D vectors, which is a scalar value of type double.
 */
double MathOGL::dotProduct(glm::vec3 vec1, glm::vec3 vec2)
{
	return
		(double)(vec1.x) * (double)(vec2.x) +
		(double)(vec1.y) * (double)(vec2.y) +
		(double)(vec1.z) * (double)(vec2.z);
}

/**
 * This function performs scalar division on a 3D vector.
 * 
 * @param vec1 A 3-component vector of type glm::vec3.
 * @param escalar The parameter "escalar" is a double precision floating point number that represents
 * the scalar value by which the components of the input vector "vec1" will be divided.
 * 
 * @return a new `glm::vec3` vector that is the result of dividing each component of the input vector
 * `vec1` by the scalar value `escalar`.
 */
glm::vec3 MathOGL::scalarDivision(glm::vec3 vec1, double escalar)
{
	return glm::vec3(
		vec1.x / escalar,
		vec1.y / escalar,
		vec1.z / escalar
	);
}

/**
 * This function calculates the angle between two 3D vectors using their dot product and their
 * magnitudes.
 * 
 * @param vec1 A 3D vector representing the first vector in the angle calculation.
 * @param vec2 The second vector in the calculation of the angle between two vectors.
 * 
 * @return the angle in radians between two 3D vectors, vec1 and vec2.
 */
double MathOGL::angleBetween(glm::vec3 vec1, glm::vec3 vec2)
{
	double dotp = dotProduct(vec1, vec2);
	double len1 = sqrt(dotProduct(vec1, vec1));
	double len2 = sqrt(dotProduct(vec2, vec2));
	double cosTheta = dotp / (len1 * len2);
	return acos(cosTheta);
}

/**
 * The function normalizes a given vector using the dot product and scalar division.
 * 
 * @param vec1 vec1 is a 3D vector of type glm::vec3 that represents the vector to be normalized.
 * 
 * @return a normalized vector of type glm::vec3.
 */
glm::vec3 MathOGL::normalize(glm::vec3 vec1)
{
	double len1 = sqrt(dotProduct(vec1, vec1));
	return scalarDivision(vec1, len1);
}

/**
 * The function returns a 4x4 matrix that represents a translation transformation based on a given 3D
 * vector.
 * 
 * @param t t is a 3D vector representing the translation values in the x, y, and z directions.
 * 
 * @return The function `translate` is returning a 4x4 transformation matrix (`glm::mat4`) that
 * represents a translation transformation by the vector `t` in 3D space. The matrix is constructed
 * using the `glm::vec4` constructor that takes the `t` vector as input and sets the fourth component
 * to 1.0f to represent a translation transformation.
 */
glm::mat4 MathOGL::translate(glm::vec3 t) {
	glm::mat4 result(1.0f);
	result[3] = glm::vec4(t, 1.0f);
	return result;
}

/**
 * This function draws a basic line using the Basic's algorithm and returns a vector of points.
 * 
 * @param x1 The x-coordinate of the starting point of the line.
 * @param y1 The y-coordinate of the starting point of the line.
 * @param x2 The x-coordinate of the end point of the line.
 * @param y2 The y-coordinate of the end point of the line.
 * 
 * @return A vector of glm::vec3 points representing a basic line drawn between two given points (x1,
 * y1) and (x2, y2).
 */
std::vector<glm::vec3> MathOGL::drawLineBasic(double x1, double y1, double x2, double y2) 
{
	std::vector<glm::vec3> points;
	double dx = abs(x2 - x1);
	double dy = abs(y2 - y1);
	double m = dy / dx;
	double xi, yi;
	int i = x1;
	yi = y1;
	points.push_back(glm::vec3(i, yi, 0));
	while (i < x2) {
		i = i + 1;
		xi = i;
		yi = roundf(yi + m);
		points.push_back(glm::vec3(xi, yi, 0));
	}
	return points;
}

/**
 * This function uses Bresenham's line algorithm to draw a line between two points and returns a vector
 * of points along the line.
 * 
 * @param x1 The x-coordinate of the starting point of the line.
 * @param y1 The y-coordinate of the starting point of the line.
 * @param x2 The x-coordinate of the end point of the line.
 * @param y2 The y-coordinate of the end point of the line.
 * 
 * @return A vector of glm::vec3 points representing a line drawn using Bresenham's line algorithm
 * between the points (x1, y1) and (x2, y2).
 */
std::vector<glm::vec3> MathOGL::drawLineBres(double x1, double y1, double x2, double y2)
{
	std::vector<glm::vec3> points;
	double dx = x2 - x1;
	double dy = y2 - y1;
	double pk = 2 * dy - dx;

	for (int x = x1, y = y1; x <= x2; x++) {

		points.push_back(glm::vec3(x, y, 0));

		dx = x2 - x;
		dy = y2 - y;

		if (pk >= 0)
		{
			pk = pk + 2 * dy - 2 * dx;
			y++;
		}
		else
		{
			pk = pk + 2 * dy;
		}

	}
	return points;
}

/**
 * This function uses the DDA algorithm to draw a line between two points and returns a vector of
 * points along the line.
 * 
 * @param x1 The x-coordinate of the starting point of the line.
 * @param y1 The y-coordinate of the starting point of the line.
 * @param x2 The x-coordinate of the end point of the line.
 * @param y2 The y-coordinate of the end point of the line to be drawn using the DDA algorithm.
 * 
 * @return A vector of glm::vec3 points representing a line drawn using the DDA algorithm between the
 * points (x1, y1) and (x2, y2).
 */
std::vector<glm::vec3> MathOGL::drawLineDDA(double x1, double y1, double x2, double y2)
{
	std::vector<glm::vec3> points;
	float dy = 0;
	float dx = 0;
	int xi, yi;
	float step = 0;
	int i = 1;

	xi = x1;
	yi = y1;
	points.push_back(glm::vec3(xi, yi, 0));

	while (xi < x2 || yi < x2) {

		dy = abs(y2 - yi);
		dx = abs(x2 - xi);

		if (dx > dy)
		{
			step = dx;
			dx = dx / step;
			xi = xi + dx;
		}
		else
		{
			step = dy;
			dy = dy / step;
			yi = yi + dy;
		}
			
		points.push_back(glm::vec3(xi, yi, 0));

		i = i + 1;
	}
	return points;
}

/**
 * The function draws a circle using the midpoint algorithm and returns a vector of points.
 * 
 * @param x_centre The x-coordinate of the center of the circle.
 * @param y_centre The y-coordinate of the center point of the circle.
 * @param r The radius of the circle to be drawn.
 * 
 * @return A vector of glm::vec3 points representing the perimeter of a circle with the given center
 * coordinates and radius.
 */
std::vector<glm::vec3> MathOGL::midPointCircleDraw(double x_centre, double y_centre, double r)
{
	std::vector<glm::vec3> points;
	int x = r, y = 0;

	// Storing the initial point on the axes
	// after translation

	// When radius is zero only a single
	// point will be printed
	if (r > 0)
	{
		points.push_back(glm::vec3((r + x_centre), (y_centre), 0));
		points.push_back(glm::vec3((x_centre), (r + y_centre), 0));
	}
	else
	{
		points.push_back(glm::vec3((x_centre), (y_centre), 0));
	}

	// Initialising the value of P
	int P = 1 - r;
	while (x > y)
	{
		y++;
		// Mid-point is inside or on the perimeter
		if (P <= 0)
			P = P + 2 * y + 1;
		// Mid-point is outside the perimeter
		else
		{
			x--;
			P = P + 2 * y - 2 * x + 1;
		}

		// All the perimeter points have already been printed
		if (x < y)
			break;

		// Printing the generated point and its reflection
		// in the other octants after translation
		points.push_back(glm::vec3((x + x_centre), (y + y_centre), 0));

		// If the generated point is on the line x = y then
		// the perimeter points have already been printed
		if (x != y) {
			points.push_back(glm::vec3((y + x_centre), (x + y_centre), 0));
		}
	}
	return points;
}

/**
 * The function uses Bresenham's algorithm to generate a vector of points that form a circle with a
 * given center and radius.
 * 
 * @param x_center The x-coordinate of the center of the circle.
 * @param y_center The y-coordinate of the center of the circle.
 * @param r The radius of the circle.
 * 
 * @return A vector of glm::vec3 points representing the pixels of a circle drawn using the Bresenham's
 * algorithm, with the center at (x_center, y_center) and radius r.
 */
std::vector<glm::vec3> MathOGL::BresenhamCircle(double x_center, double y_center, double r, double z)
{
	std::vector<glm::vec3> points;
	int x = 0;
	int y = r;
	int d = 3 - 2 * y;

    while (y >= x)
    {
		BresenhamCirclePoints(x_center, y_center, x, y, z, points);
        x++;
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;
    }

	// Order the vector so that duplicated elements remain together
	//std::sort(points.begin(), points.end());
	std::sort(points.begin(), points.end(), &MathOGL::compareVecByElems);

	// Remove duplicated elements
	auto it = std::unique(points.begin(), points.end());
	points.erase(it, points.end());

	return points;
}

/**
 * The function adds eight points to a vector representing a circle using the Bresenham algorithm.
 * 
 * @param x_center The x-coordinate of the center of the circle.
 * @param y_center The y-coordinate of the center of the circle.
 * @param x The x-coordinate of a point on the circumference of a circle.
 * @param y The y-coordinate of a point on the circle.
 * @param points a vector of glm::vec3 points that will be filled with the coordinates of the circle
 * points
 */
void MathOGL::BresenhamCirclePoints(double x_center, double y_center, double x, double y, double z, std::vector<glm::vec3>& points)
{
	points.push_back(glm::vec3(x_center + x, y_center + y, z));
	points.push_back(glm::vec3(x_center - x, y_center + y, z));
	points.push_back(glm::vec3(x_center + x, y_center - y, z));
	points.push_back(glm::vec3(x_center - x, y_center - y, z));
	points.push_back(glm::vec3(x_center + y, y_center + x, z));
	points.push_back(glm::vec3(x_center - y, y_center + x, z));
	points.push_back(glm::vec3(x_center + y, y_center - x, z));
	points.push_back(glm::vec3(x_center - y, y_center - x, z));
}

/**
 * The function compares two 3D vectors by their elements and returns a boolean value.
 * 
 * @param a a is a constant reference to a 3D vector of type glm::vec3.
 * @param b The second input parameter is a constant reference to a glm::vec3 object named "b". This is
 * a 3D vector in the glm library, which represents a point or a direction in 3D space. The function is
 * designed to compare two such vectors element-wise, and return true if
 * 
 * @return a boolean value indicating whether the first vector argument is less than the second vector
 * argument, based on the values of their x, y, and z components.
 */
bool MathOGL::compareVecByElems(const glm::vec3& a, const glm::vec3& b)
{
	if (a.x != b.x) {
		return a.x < b.x;
	}
	else if (a.y != b.y) {
		return a.y < b.y;
	}
	return a.z < b.z;
}

/**
 * This is a destructor for the MathOGL class in C++.
 */
MathOGL::~MathOGL()
{

}