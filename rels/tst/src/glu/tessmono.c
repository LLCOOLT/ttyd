/*
 * libtess (SGI OpenGL Sample Implementation GLU): tessellation of monotone regions.
 * Author: Eric Veach, July 1994.
 *
 * tst.rel carries a copy of the GLU polygon tessellator from the OpenGL Sample Implementation (Silicon Graphics,
 * Inc., SGI Free Software License B). The assertions of this copy are compiled in, and each one passes its source
 * line to __assert, so the layout of every file follows the original: the license and author header take the
 * first lines, and the functions keep their original order and length.
 *
 * Contents of this file:
 *
 *   __gl_meshTessellateMonoRegion  triangulates one monotone face
 *   __gl_meshTessellateInterior    triangulates every face marked inside
 *   __gl_meshDiscardExterior       zaps every face not marked inside
 *   __gl_meshSetWindingNumber      sets boundary windings, optionally keeps only the boundary
 *
 * They run after the sweep (sweep.c) has split the arrangement into monotone regions and marked
 * each one inside or outside by the winding rule; gluTessEndPolygon (tess.c) picks which of
 * them to call:
 *
 *   - triangles:        __gl_meshTessellateInterior, then the mesh is rendered (render.c);
 *   - boundary only:    __gl_meshSetWindingNumber( mesh, 1, TRUE ), then the contours are
 *                       rendered;
 *   - mesh callback:    __gl_meshDiscardExterior, and the client gets the mesh itself.
 *
 * The faces made by __gl_meshConnect are inserted before the face being split, so the
 * loops over the face list never visit a new triangle.
 *
 * Inlining: with deferred inlining nothing here is inlined into a caller in this file
 * except through the geom.h macros (VertLeq, EdgeGoesLeft, EdgeGoesRight); EdgeSign stays
 * a call to __gl_edgeSign in geom.c.
 *
 * Emission order: deferred inlining emits the functions last to first, so
 * __gl_meshSetWindingNumber comes first in .text.
 *
 * Assertions: __gl_meshTessellateMonoRegion checks that the face has at least three
 * edges, and that the fan it builds at the end has a triangle left to cut off.
 *
 * Memory: a failed __gl_meshConnect makes the caller return 0, which tess.c turns into
 * GLU_OUT_OF_MEMORY.
 *
 *
 *
 */

#include <stdlib.h>
#include "glu/gluos.h"
#include "glu/geom.h"
#include "glu/mesh.h"
#include "glu/tessmono.h"

#define AddWinding(eDst, eSrc) (eDst->winding += eSrc->winding, eDst->Sym->winding += eSrc->Sym->winding)

/* __gl_meshTessellateMonoRegion( face ) tessellates a monotone region
 * (what else would it do??)  The region must consist of a single
 * loop of half-edges (see mesh.h) oriented CCW.  "Monotone" in this
 * case means that any vertical line intersects the interior of the
 * region in a single interval.
 *
 * Tessellation consists of adding interior edges (actually pairs of
 * half-edges), to split the region into non-overlapping triangles.
 *
 * The basic idea is explained in Preparata and Shamos (which I don''t
 * have handy right now), although their implementation is more
 * complicated than this one.  The are two edge chains, an upper chain
 * and a lower chain.  We process all vertices from both chains in order,
 * from right to left.
 *
 * The algorithm ensures that the following invariant holds after each
 * vertex is processed: the untessellated region consists of two
 * chains, where one chain (say the upper) is a single edge, and
 * the other chain is concave.  The left vertex of the single edge
 * is always to the left of all vertices in the concave chain.
 *
 * Each step consists of adding the rightmost unprocessed vertex to one
 * of the two chains, and forming a fan of triangles from the rightmost
 * of two chain endpoints.  Determining whether we can add each triangle
 * to the fan is a simple orientation test.  By making the fan as large
 * as possible, we restore the invariant (check it yourself).
 */
int __gl_meshTessellateMonoRegion(GLUface* face) {
    GLUhalfEdge *up, *lo;

    /* All edges are oriented CCW around the boundary of the region.
     * First, find the half-edge whose origin vertex is rightmost.
     * Since the sweep goes from left to right, face->anEdge should
     * be close to the edge we want.
     */
    up = face->anEdge;
    assert( up->Lnext != up && up->Lnext->Lnext != up );

    for (; VertLeq(up->Dst, up->Org); up = up->Lprev)
        ;
    for (; VertLeq(up->Org, up->Dst); up = up->Lnext)
        ;
    lo = up->Lprev;

    while (up->Lnext != lo) {
        if (VertLeq(up->Dst, lo->Org)) {
            /* up->Dst is on the left.  It is safe to form triangles from lo->Org.
             * The EdgeGoesLeft test guarantees progress even when some triangles
             * are CW, given that the upper and lower chains are truly monotone.
             */
            while (lo->Lnext != up &&
                   (EdgeGoesLeft(lo->Lnext) || EdgeSign(lo->Org, lo->Dst, lo->Lnext->Dst) <= 0)) {
                GLUhalfEdge* tempHalfEdge = __gl_meshConnect(lo->Lnext, lo);
                if (tempHalfEdge == NULL) return 0;
                lo = tempHalfEdge->Sym;
            }
            lo = lo->Lprev;
        } else {
            /* lo->Org is on the left.  We can make CCW triangles from up->Dst. */
            while (lo->Lnext != up &&
                   (EdgeGoesRight(up->Lprev) || EdgeSign(up->Dst, up->Org, up->Lprev->Org) >= 0)) {
                GLUhalfEdge* tempHalfEdge = __gl_meshConnect(up, up->Lprev);
                if (tempHalfEdge == NULL) return 0;
                up = tempHalfEdge->Sym;
            }
            up = up->Lnext;
        }
    }

    /* Now lo->Org == up->Dst == the leftmost vertex.  The remaining region
     * can be tessellated in a fan from this leftmost vertex.
     */
    assert( lo->Lnext != up );
    while (lo->Lnext->Lnext != up) {
        GLUhalfEdge* tempHalfEdge = __gl_meshConnect(lo->Lnext, lo);
        if (tempHalfEdge == NULL) {
            return 0;
        }
        lo = tempHalfEdge->Sym;
    }

    return 1;
}

/* __gl_meshTessellateInterior( mesh ) tessellates each region of
 * the mesh which is marked "inside" the polygon.  Each such region
 * must be monotone.
 */
int __gl_meshTessellateInterior(GLUmesh* mesh) {
    GLUface *f, *next;

    /*LINTED*/
    for (f = mesh->fHead.next; f != &mesh->fHead; f = next) {
        /* Make sure we don''t try to tessellate the new triangles. */
        next = f->next;
        if (f->inside) {
            if (!__gl_meshTessellateMonoRegion(f)) {
                return 0;
            }
        }
    }

    return 1;
}

/* __gl_meshDiscardExterior( mesh ) zaps (ie. sets to NULL) all faces
 * which are not marked "inside" the polygon.  Since further mesh operations
 * on NULL faces are not allowed, the main purpose is to clean up the
 * mesh so that exterior loops are not represented in the data structure.
 */
void __gl_meshDiscardExterior(GLUmesh* mesh) {
    GLUface *f, *next;

    /*LINTED*/
    for (f = mesh->fHead.next; f != &mesh->fHead; f = next) {
        /* Since f will be destroyed, save its next pointer. */
        next = f->next;
        if (!f->inside) {
            __gl_meshZapFace(f);
        }
    }
}

#define MARKED_FOR_DELETION 0x7fffffff

/* __gl_meshSetWindingNumber( mesh, value, keepOnlyBoundary ) resets the
 * winding numbers on all edges so that regions marked "inside" the
 * polygon have a winding number of "value", and regions outside
 * have a winding number of 0.
 *
 * If keepOnlyBoundary is TRUE, it also deletes all edges which do not
 * separate an interior region from an exterior one.
 */
int __gl_meshSetWindingNumber(GLUmesh* mesh, int value, GLboolean keepOnlyBoundary) {
    GLUhalfEdge *e, *eNext;

    for (e = mesh->eHead.next; e != &mesh->eHead; e = eNext) {
        eNext = e->next;
        if (e->Rface->inside != e->Lface->inside) {
            /* This is a boundary edge (one side is interior, one is exterior). */
            e->winding = (e->Lface->inside) ? value : -value;
        } else {
            /* Both regions are interior, or both are exterior. */
            if (!keepOnlyBoundary) {
                e->winding = 0;
            } else {
                if (!__gl_meshDelete(e)) {
                    return 0;
                }
            }
        }
    }
    return 1;
}
