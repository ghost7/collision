#ifndef _SAT_POLYGON_H_
#define _SAT_POLYGON_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Polygon 
{
private:
	int numVerts;
	glm::vec2 *vertices;
	glm::mat4 model;

public:
	Polygon(glm::vec2 *vertices, int numVerts);

	void translate(float x, float y);

	glm::vec2 *getVertices();
	int getNumVerts();
	glm::mat4 getModel();
};

#endif
