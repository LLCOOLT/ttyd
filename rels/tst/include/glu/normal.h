#pragma once

/* libtess sweep-plane projection (normal.c). */

#include "glu/tess.h"

/* __gl_projectPolygon( tess ) determines the polygon normal
 * and project vertices onto the plane of the polygon.
 */
void __gl_projectPolygon(GLUtesselator* tess);
