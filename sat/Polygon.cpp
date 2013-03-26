#include "Polygon.h"

Polygon::Polygon(glm::vec2 *vertices, int numVerts)
{
	this->vertices = vertices;
	this->numVerts = numVerts;
}

void Polygon::translate(float x, float y) 
{
	model = glm::translate(model, glm::vec3(5,5,0));
}

glm::vec2 *Polygon::getVertices()
{
	return vertices;
}

int Polygon::getNumVerts()
{
	return numVerts;
}

glm::mat4 Polygon::getModel()
{
	return model;
}

