/**
* Polygon class used to detect and detect and resolve collisions using the
* separatng axis theorem.
*/

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
    /**
    * Helper class to contain vector projection information
    */
    class Projection
    {	
        float min;
        float max;
    public:
        Projection(float min, float max) : min(min), max(max)
        {
        }

        /**
        * Gets the magnitude of overlap of another projection. If the 
        * projections do not overlap, the magnitude will be 0.
        *
        * @param other Projection to test against.
        */
        float getOverlap(Projection other);
    };

    /**
    * Project the polygon's vertices onto the specified axis.
    *
    * @param axis Axis to test against.
    */
    Projection project(glm::vec2 axis);

public:
    /**
    * Construct a polygon with the specified vertices.
    *
    * @param vertices Vertices that make up the polygon.
    * @param numVerts The number of vertices of the polygon.
    */
    Polygon(glm::vec2 *vertices, int numVerts);
    ~Polygon();

    /**
    * Translate the polygon's model.
    *
    * @param x Delta x to translate.
    * @param y Delta y to translate.
    */
    void translate(float x, float y);

    /**
    * Determine if this polygon intersects with another. Also, output the 
    * minimum translation vector that will resolve the collision, if there is 
    * one.
    *
    * Example Usage of resolving collison:
    * 
    * glm::vec2 mtv;
    * if(poly1.intersects(&poly2, mtv)) {
    *     poly1.translate(mtv.x, mtv.y);
    * }
    *
    * @param polygon Polygon to test against.
    * @param mtv Minimum transation vector used to resolve the collision. 
    *            Note, this function will modify this variable.
    * @return True if the polygon intersects.
    */
    bool intersects(Polygon* polygon, glm::vec2 &mtv);

    /**
    * Get the vertices that make up this polygon.
    *
    * @return Vertices that make up this polygon.
    */
    glm::vec2 *getVertices();

    /**
    * Gets the number of vertices that make up this polygon.
    *
    * @return The number of vertices that make up this polygon.
    */
    int getNumVerts();

    /**
    * Gets the matrix model for this polygon. For now, this only consists
    * of the transation vector.
    *
    * @return Model that can be used to calculate model, view, projection
    *         of a scene.
    */
    glm::mat4 getModel();
};

#endif