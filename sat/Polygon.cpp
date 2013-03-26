#include "Polygon.h"


Polygon::Polygon(glm::vec2 *vertices, int numVerts)
{
	this->vertices = vertices;
	this->numVerts = numVerts;

	normalAxes = new glm::vec2[numVerts];
	for(int i = 0; i < numVerts; i++) {
		int j = (i + 1) % numVerts;
		glm::vec2 axis = glm::vec2((-vertices[j].y + vertices[i].y), 
                    (vertices[j].x - vertices[i].x));
		normalAxes[i] = glm::normalize(axis);
	}
}

Polygon::~Polygon()
{
	delete normalAxes;
}

glm::vec2 transform(glm::vec2 const & vertex, glm::mat4 const & matrix)
{
	glm::vec4 product = glm::vec4(vertex, 0, 1);
	product = matrix * product;
	return glm::vec2(product.x, product.y);
}

bool Polygon::intersects(Polygon* polygon)
{
	for(int i = 0; i < numVerts; i++) {
		glm::vec2 axis = normalAxes[i];
		Projection p1 = project(axis);
		Projection p2 = polygon->project(axis);
		if(p1.overlap(p2)) {
			return false;
		}
	}

	for(int i = 0; i < polygon->numVerts; i++) {
		glm::vec2 axis = polygon->normalAxes[i];
		Projection p1 = project(axis);
		Projection p2 = polygon->project(axis);
		if(p1.overlap(p2)) {
			return false;
		}
	}

	return true;
}

Projection Polygon::project(glm::vec2 axis)
{
	glm::vec2 vertex = transform(vertices[0], model);
	float min = glm::dot(axis, vertex);
	float max = min;
	for(int i = 0; i < numVerts; i++) {
		vertex = transform(vertices[i], model);
		float magnitude = glm::dot(axis, vertex);
		if(min > magnitude) {
			min = magnitude;
		}
		if(max < magnitude) {
			max = magnitude;
		}
	}
	
	Projection proj = { min, max };
	return proj;
}

void Polygon::translate(float x, float y) 
{
	model = glm::translate(model, glm::vec3(x,y,0));
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

