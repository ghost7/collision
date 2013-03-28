#include "PolygonArtist.h"

#include <GL/glew.h>

void PolygonArtist::render(Polygon* poly)
{
    // Don't know if this is the best way to do this, but I'm still learning
    // OpenGL :)
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(2, GL_FLOAT, 0, poly->getVertices());
    glDrawArrays(GL_POLYGON, 0, poly->getNumVerts());

    glDisableClientState(GL_VERTEX_ARRAY);
}