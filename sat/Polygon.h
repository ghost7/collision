#ifndef _SAT_POLYGON_H_
#define _SAT_POLYGON_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



class Polygon 
{
private:
	int numVerts;
	glm::vec2 *vertices;
	glm::vec2 *normalAxes;
	glm::mat4 model;
	class Projection
	{	
		float min;
		float max;
	public:
		Projection(float min, float max) : min(min), max(max)
		{
		}
		float getOverlap(Projection other);
	};

	Projection project(glm::vec2 axis);

public:
	Polygon(glm::vec2 *vertices, int numVerts);
	~Polygon();

	void translate(float x, float y);

	bool intersects(Polygon* polygon, glm::vec2 &mtv);

	glm::vec2 *getVertices();
	int getNumVerts();
	glm::mat4 getModel();
};

#endif
