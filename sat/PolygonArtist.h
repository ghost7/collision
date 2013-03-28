/**
* Helper class used to render a polygon.
*/

#ifndef _SAT_POLY_ARTIST_H_
#define _SAT_POLY_ARTIST_H_

#include "Polygon.h"

class PolygonArtist
{
public:
    /**
    * Renders a polygon.
    *
    * @param polygon Polygon to render.
    */
    static void render(Polygon *polygon);
};

#endif