#include <math.h>

#include <dolphin/gx.h>
#include <dolphin/os.h>

#include "__gx.h"

static GXVtxDescList vcd[27];
static GXVtxAttrFmtList vat[27];

/**
 * Saves the current vertex descriptor and the format table 3 attributes, then sets up float position and normal,
 * direct, in vertex format 3 for the shape drawing functions.
 */
static void GetVertState(void) {
    GXGetVtxDescv(vcd);
    GXGetVtxAttrFmtv(GX_VTXFMT3, vat);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
}

/** Restores the vertex descriptor and format table 3 saved by GetVertState. */
static void RestoreVertState(void) {
    GXSetVtxDescv(vcd);
    GXSetVtxAttrFmtv(GX_VTXFMT3, vat);
}

/** Computes u = p2 - p1 for 3D vectors. */
static void vsub(f32 p1[3], f32 p2[3], f32 u[3]) {
    u32 i;

    for (i = 0; i < 3; i++) {
        u[i] = p2[i] - p1[i];
    }
}

/** Computes the cross product n = u x v of two 3D vectors. */
static void vcross(f32 u[3], f32 v[3], f32 n[3]) {
    f32 n1[3];

    n1[0] = (u[1] * v[2]) - (u[2] * v[1]);
    n1[1] = (u[2] * v[0]) - (u[0] * v[2]);
    n1[2] = (u[0] * v[1]) - (u[1] * v[0]);
    n[0] = n1[0];
    n[1] = n1[1];
    n[2] = n1[2];
}

/** Scales a 3D vector to unit length in place. */
static void normalize(f32 v[3]) {
    f32 d = sqrtf((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]));

    ASSERTMSGLINE(137, d != 0.0f, "normalize: zero length vector");
    v[0] /= d;
    v[1] /= d;
    v[2] /= d;
}

/** Sends one vertex (position v and normal n) to the FIFO. */
static void myvertex(f32 v[3], f32 n[3]) {
    GXPosition3f32(v[0], v[1], v[2]);
    GXNormal3f32(n[0], n[1], n[2]);
}

/** Draws one triangle of a unit sphere approximation, using each vertex position as its normal. */
static void DumpTriangle(f32 v0[3], f32 v1[3], f32 v2[3]) {
    GXBegin(GX_TRIANGLES, GX_VTXFMT3, 3);
    myvertex(v0, v0);
    myvertex(v1, v1);
    myvertex(v2, v2);
    GXEnd();
}

/**
 * Draws a triangle on the unit sphere split recursively into four (edge midpoints pushed out to the sphere) down
 * to the given depth.
 */
static void Subdivide(u8 depth, f32 v0[3], f32 v1[3], f32 v2[3]) {
    f32 v01[3];
    f32 v12[3];
    f32 v20[3];
    u32 i;

    if (depth == 0) {
        DumpTriangle(v0, v1, v2);
        return;
    }

    for (i = 0; i < 3; i++) {
        v01[i] = v0[i] + v1[i];
        v12[i] = v1[i] + v2[i];
        v20[i] = v2[i] + v0[i];
    }

    normalize(v01);
    normalize(v12);
    normalize(v20);
    Subdivide(depth - 1, v0, v01, v20);
    Subdivide(depth - 1, v1, v12, v01);
    Subdivide(depth - 1, v2, v20, v12);
    Subdivide(depth - 1, v01, v12, v20);
}

/** Draws triangle i of an index table, subdivided to the given depth. */
static void SubDivTriangle(u8 depth, u8 i, f32 (*data)[3], u8 (*ndx)[3]) {
    f32 *x0 = data[ndx[i][0]];
    f32 *x1 = data[ndx[i][1]];
    f32 *x2 = data[ndx[i][2]];

    Subdivide(depth, x0, x1, x2);
}

/**
 * Draws a cylinder of radius 1 from z = -1 to z = 1 with numEdges sides:
 * a triangle strip for the side and fans for the two caps, with normals.
 */
void GXDrawCylinder(u8 numEdges) {
    s32 i;
    f32 top;
    f32 bottom;
    f32 x[100];
    f32 y[100];
    f32 angle;

    top = 1.0f;
    bottom = -top;
    ASSERTMSGLINE(216, numEdges <= 99, "GXDrawCylinder: too many edges");

    GetVertState();

    for (i = 0; i <= numEdges; i++) {
        angle = (3.1415927f * (2.0f * i)) / numEdges;
        x[i] = cosf(angle);
        y[i] = sinf(angle);
    }

    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT3, (numEdges + 1) * 2);
    for (i = 0; i <= numEdges; i++) {
        GXPosition3f32(x[i], y[i], bottom);
        GXNormal3f32(x[i], y[i], 0.0f);
        GXPosition3f32(x[i], y[i], top);
        GXNormal3f32(x[i], y[i], 0.0f);

    }
    GXEnd();

    GXBegin(GX_TRIANGLEFAN, GX_VTXFMT3, numEdges + 2);
    GXPosition3f32(0.0f, 0.0f, top);
    GXNormal3f32(0.0f, 0.0f, 1.0f);
    for (i = 0; i <= numEdges; i++) {
        GXPosition3f32(x[i], -y[i], top);
        GXNormal3f32(0.0f, 0.0f, 1.0f);

    }
    GXEnd();

    GXBegin(GX_TRIANGLEFAN, GX_VTXFMT3, numEdges + 2);
    GXPosition3f32(0.0f, 0.0f, bottom);
    GXNormal3f32(0.0f, 0.0f, -1.0f);
    for (i = 0; i <= numEdges; i++) {
        GXPosition3f32(x[i], y[i], bottom);
        GXNormal3f32(0.0f, 0.0f, -1.0f);
    }
    GXEnd();

    RestoreVertState();
}

/**
 * Draws a torus whose tube has radius rc (ring radius 1 - rc),
 * with numc segments around the tube and numt around the ring,
 * with normals and texture coordinates if texture 0 is in use.
 */
void GXDrawTorus(f32 rc, u8 numc, u8 numt) {
    GXAttrType ttype;
    s32 i, j, k;
    f32 s, t;
    f32 x, y, z;
    f32 twopi = 6.2831855f;
    f32 rt;

    ASSERTMSGLINE(316, rc < 1.0f, "GXDrawTorus: doughnut too fat");

    rt = 1.0f - rc;
    GXGetVtxDesc(GX_VA_TEX0, &ttype);
    GetVertState();

    if (ttype != GX_NONE) {
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    }

    for (i = 0; i < numc; i++) {
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT3, (numt + 1) * 2);
        for (j = 0; j <= numt; j++) {
            for (k = 1; k >= 0; k--) {
                s = (i + k) % numc;
                t = j % numt;
                x = (rt - rc * cosf(s * twopi / numc)) * cosf(t * twopi / numt);
                y = (rt - rc * cosf(s * twopi / numc)) * sinf(t * twopi / numt);
                z = rc * sinf(s * twopi / numc);
                GXPosition3f32(x, y, z);
                x = -cosf(t * twopi / numt) * cosf(s * twopi / numc);
                y = -sinf(t * twopi / numt) * cosf(s * twopi / numc);
                z = sinf(s * twopi / numc);
                GXNormal3f32(x, y, z);
                if (ttype != GX_NONE) {
                    GXTexCoord2f32((i + k) / (f32)numc, j / (f32)numt);
                }
            }
        }
        GXEnd();
    }
    RestoreVertState();
}

/**
 * Draws a unit sphere as numMajor bands of triangle strips with numMinor steps around,
 * with normals and texture coordinates if texture 0 is in use.
 */
void GXDrawSphere(u8 numMajor, u8 numMinor) {
    GXAttrType ttype;
    f32 radius = 1.0f;
    f32 majorStep = 3.1415927f / numMajor;
    f32 minorStep = 6.2831855f / numMinor;
    s32 i, j;
    f32 a, b;
    f32 r0, r1;
    f32 z0, z1;
    f32 c;
    f32 x, y;

    GXGetVtxDesc(GX_VA_TEX0, &ttype);
    GetVertState();

    if (ttype != GX_NONE) {
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0);
    }

    for (i = 0; i < numMajor; i++) {
        a = i * majorStep;
        b = a + majorStep;
        r0 = radius * sinf(a);
        r1 = radius * sinf(b);
        z0 = radius * cosf(a);
        z1 = radius * cosf(b);
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT3, (numMinor + 1) * 2);
        for (j = 0; j <= numMinor; j++) {
            c = j * minorStep;
            x = cosf(c);
            y = sinf(c);
            GXPosition3f32(x * r1, y * r1, z1);
            GXNormal3f32((x * r1) / radius, (y * r1) / radius, z1 / radius);
            if (ttype != GX_NONE) {
                GXTexCoord2f32((f32)j / (f32)numMinor, (f32)(i + 1) / (f32)numMajor);
            }
            GXPosition3f32(x * r0, y * r0, z0);
            GXNormal3f32((x * r0) / radius, (y * r0) / radius, z0 / radius);
            if (ttype != GX_NONE) {
                GXTexCoord2f32((f32)j / (f32)numMinor, (f32)i / (f32)numMajor);
            }
        }
        GXEnd();
    }
    RestoreVertState();
}

/**
 * Draws one face of the cube as a quad of four vertices from the face's normal, tangent and binormal vectors.
 * The tangent and binormal are sent as extra normals and texture coordinates only
 * when those attributes are in use.
 */
static void GXDrawCubeFace(f32 nx, f32 ny, f32 nz, f32 tx, f32 ty, f32 tz, f32 bx, f32 by, f32 bz, GXAttrType binormal, GXAttrType texture) {
    GXPosition3f32(0.57735026f * (nx + tx + bx), 0.57735026f * (ny + ty + by), 0.57735026f * (nz + tz + bz));
    GXNormal3f32(nx, ny, nz);

    if (binormal != GX_NONE) {
        GXNormal3f32(tx, ty, tz);
        GXNormal3f32(bx, by, bz);
    }

    if (texture != GX_NONE) {
        GXTexCoord2s8(1, 1);
    }

    GXPosition3f32(0.57735026f * (nx - tx + bx), 0.57735026f * (ny - ty + by), 0.57735026f * (nz - tz + bz));
    GXNormal3f32(nx, ny, nz);

    if (binormal != GX_NONE) {
        GXNormal3f32(tx, ty, tz);
        GXNormal3f32(bx, by, bz);
    }

    if (texture != GX_NONE) {
        GXTexCoord2s8(0, 1);
    }

    GXPosition3f32(0.57735026f * (nx - tx - bx), 0.57735026f * (ny - ty - by), 0.57735026f * (nz - tz - bz));
    GXNormal3f32(nx, ny, nz);

    if (binormal != GX_NONE) {
        GXNormal3f32(tx, ty, tz);
        GXNormal3f32(bx, by, bz);
    }

    if (texture != GX_NONE) {
        GXTexCoord2s8(0, 0);
    }

    GXPosition3f32(0.57735026f * (nx + tx - bx), 0.57735026f * (ny + ty - by), 0.57735026f * (nz + tz - bz));
    GXNormal3f32(nx, ny, nz);

    if (binormal != GX_NONE) {
        GXNormal3f32(tx, ty, tz);
        GXNormal3f32(bx, by, bz);
    }

    if (texture != GX_NONE) {
        GXTexCoord2s8(1, 0);
    }
}

/**
 * Draws a cube with corners at plus and minus 0.577 (inscribed in the unit sphere) as six quads,
 * with normals (and tangent/binormal and texture coordinates if in use).
 */
void GXDrawCube(void) {
    GXAttrType ntype;
    GXAttrType ttype;

    GXGetVtxDesc(GX_VA_NBT, &ntype);
    GXGetVtxDesc(GX_VA_TEX0, &ttype);
    GetVertState();
    if (ntype != GX_NONE) {
        GXSetVtxDesc(GX_VA_NBT, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_NBT, GX_TEX_ST, GX_RGBA6, 0);
    }
    if (ttype != GX_NONE) {
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_TEX0, GX_TEX_ST, GX_RGB8, 0);
    }

    GXBegin(GX_QUADS, GX_VTXFMT3, 24);
    GXDrawCubeFace(-1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, ntype, ttype);
    GXDrawCubeFace(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, ntype, ttype);
    GXDrawCubeFace(0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, ntype, ttype);
    GXDrawCubeFace(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, ntype, ttype);
    GXDrawCubeFace(0.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, ntype, ttype);
    GXDrawCubeFace(0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, ntype, ttype);
    GXEnd();

    RestoreVertState();
}

/** The dodecahedron's 12 faces as five corner indexes into verts. */
static u32 polygons[12][5] = {
    {  0, 12, 10, 11, 16 },
    {  1, 17,  8,  9, 13 },
    {  2, 14,  9,  8, 18 },
    {  3, 19, 11, 10, 15 },
    {  4, 14,  2,  3, 15 },
    {  5, 12,  0,  1, 13 },
    {  6, 17,  1,  0, 16 },
    {  7, 19,  3,  2, 18 },
    {  8, 17,  6,  7, 18 },
    {  9, 14,  4,  5, 13 },
    { 10, 12,  5,  4, 15 },
    { 11, 19,  7,  6, 16 },
};

/** The dodecahedron's 20 corners. */
static f32 verts[20][3] = {
    { -0.809015f,  0.0f,       0.309015f },
    { -0.809015f,  0.0f,      -0.309015f },
    {  0.809015f,  0.0f,      -0.309015f },
    {  0.809015f,  0.0f,       0.309015f },
    {  0.309015f, -0.809015f,  0.0f },
    { -0.309015f, -0.809015f,  0.0f },
    { -0.309015f,  0.809015f,  0 },
    {  0.309015f,  0.809015f,  0 },
    {  0.0f,       0.309015f, -0.809015f },
    {  0.0f,      -0.309015f, -0.809015f },
    {  0.0f,      -0.309015f,  0.809015f },
    {  0.0f,       0.309015f,  0.809015f },
    { -0.5f,      -0.5f,       0.5 },
    { -0.5f,      -0.5f,      -0.5 },
    {  0.5f,      -0.5f,      -0.5 },
    {  0.5f,      -0.5f,       0.5 },
    { -0.5f,       0.5f,       0.5 },
    { -0.5f,       0.5f,      -0.5 },
    {  0.5f,       0.5f,      -0.5 },
    {  0.5f,       0.5f,       0.5 },
};

/** Draws a regular dodecahedron as 12 pentagon fans, each with its face normal. */
void GXDrawDodeca(void) {
    u32 i;
    f32 *p0;
    f32 *p1;
    f32 *p2;
    f32 u[3];
    f32 v[3];
    f32 n[3];

    GetVertState();
    for (i = 0; i < 12; i++) {
        p0 = verts[polygons[i][0]];
        p1 = verts[polygons[i][1]];
        p2 = verts[polygons[i][2]];
        vsub(p1, p2, u);
        vsub(p1, p0, v);
        vcross(u, v, n);
        normalize(n);
        GXBegin(GX_TRIANGLEFAN, GX_VTXFMT3, 5);
        myvertex(verts[polygons[i][4]], n);
        myvertex(verts[polygons[i][3]], n);
        myvertex(p2, n);
        myvertex(p1, n);
        myvertex(p0, n);
        GXEnd();
    }
    RestoreVertState();
}

/** The octahedron's six corners (unit length along each axis). */
static f32 odata[6][3] = {
    {  1.0f,  0.0f,  0.0f },
    { -1.0f,  0.0f,  0.0f },
    {  0.0f,  1.0f,  0.0f },
    {  0.0f, -1.0f,  0.0f },
    {  0.0f,  0.0f,  1.0f },
    {  0.0f,  0.0f, -1.0f },
};

/** The octahedron's eight faces as corner indexes into odata. */
static u8 ondex[8][3] = {
    { 0, 4, 2 },
    { 1, 2, 4 },
    { 0, 3, 4 },
    { 1, 4, 3 },
    { 0, 2, 5 },
    { 1, 5, 2 },
    { 0, 5, 3 },
    { 1, 3, 5 },
};

/** Draws a regular octahedron of unit radius as 8 triangles. */
void GXDrawOctahedron(void) {
    s32 i;

    GetVertState();
    for (i = 7; i >= 0; i--) {
        SubDivTriangle(0, i, odata, ondex);
    }
    RestoreVertState();
}

/** The icosahedron's 12 corners (unit length). */
static f32 idata[12][3] = {
    { -0.5257311f,  0.0f,        0.8506508f },
    {  0.5257311f,  0.0f,        0.8506508f },
    { -0.5257311f,  0.0f,       -0.8506508f },
    {  0.5257311f,  0.0f,       -0.8506508f },
    {  0.0f,        0.8506508f,  0.5257311f },
    {  0.0f,        0.8506508f, -0.5257311f },
    {  0.0f,       -0.8506508f,  0.5257311f },
    {  0.0f,       -0.8506508f, -0.5257311f },
    {  0.8506508f,  0.5257311f,  0.0f },
    { -0.8506508f,  0.5257311f,  0.0f },
    {  0.8506508f, -0.5257311f,  0.0f },
    { -0.8506508f, -0.5257311f,  0.0f },
};

/** The icosahedron's 20 faces as corner indexes into idata; GXDrawSphere1 subdivides them. */
static u8 index[20][3] = {
    {  0,  4,  1 },
    {  0,  9,  4 },
    {  9,  5,  4 },
    {  4,  5,  8 },
    {  4,  8,  1 },
    {  8, 10,  1 },
    {  8,  3, 10 },
    {  5,  3,  8 },
    {  5,  2,  3 },
    {  2,  7,  3 },
    {  7, 10,  3 },
    {  7,  6, 10 },
    {  7, 11,  6 },
    { 11,  0,  6 },
    {  0,  1,  6 },
    {  6,  1, 10 },
    {  9,  0, 11 },
    {  9, 11,  2 },
    {  9,  2,  5 },
    {  7,  2, 11 },
};

/** Draws a regular icosahedron of unit radius as 20 triangles. */
void GXDrawIcosahedron(void) {
    s32 i;

    GetVertState();
    for (i = 19; i >= 0; i--) {
        SubDivTriangle(0, i, idata, index);
    }
    RestoreVertState();
}

/** Draws a sphere made by subdividing the icosahedron's 20 triangles to the given depth. */
void GXDrawSphere1(u8 depth) {
    s32 i;

    GetVertState();
    for (i = 19; i >= 0; i--) {
        SubDivTriangle(depth, i, idata, index);
    }
    RestoreVertState();
}

/** Returns true if two normals are exactly equal. */
static u32 CmpNormal32(f32 n1[3], f32 n2[3]) {
    u32 i;

    for (i = 0; i < 3; i++) {
        if (n1[i] != n2[i])
            return FALSE;
    }
    return TRUE;
}

static u32 nrm_cnt;
static f32* nrm_tab;

/** Adds a normal to the table being built unless an equal one is already in it. */
static void AddNormal(f32 n[3]) {
    u32 indx;
    u32 i;

    for (i = 0; i < nrm_cnt; i++) {
        if (CmpNormal32(n, &nrm_tab[i * 3]))
            return;
    }
    indx = nrm_cnt * 3;
    nrm_tab[indx + 0] = n[0];
    nrm_tab[indx + 1] = n[1];
    nrm_tab[indx + 2] = n[2];
    nrm_cnt++;
}

/**
 * Subdivides a triangle recursively as Subdivide does,
 * but adds the corner points at the final depth to the normal table.
 */
static void SubdivideNrm(u8 depth, f32 v0[3], f32 v1[3], f32 v2[3]) {
    f32 v01[3];
    f32 v12[3];
    f32 v20[3];
    u32 i;

    if (depth == 0) {
        AddNormal(v0);
        AddNormal(v1);
        AddNormal(v2);
        return;
    }

    for (i = 0; i < 3; i++) {
        v01[i] = v0[i] + v1[i];
        v12[i] = v1[i] + v2[i];
        v20[i] = v2[i] + v0[i];
    }

    normalize(v01);
    normalize(v12);
    normalize(v20);
    SubdivideNrm(depth - 1, v0, v01, v20);
    SubdivideNrm(depth - 1, v1, v12, v01);
    SubdivideNrm(depth - 1, v2, v20, v12);
    SubdivideNrm(depth - 1, v01, v12, v20);
}

/** Subdivides triangle i of an index table into the normal table. */
static void SubDivNrm(u8 depth, u8 i, f32 (*data)[3], u8 (*ndx)[3]) {
    f32* x0 = data[ndx[i][0]];
    f32* x1 = data[ndx[i][1]];
    f32* x2 = data[ndx[i][2]];

    SubdivideNrm(depth, x0, x1, x2);
}

/**
 * Fills table with the unit normals found by subdividing the 8 triangles of an octahedron to the given depth,
 * without duplicates, and returns how many there are.
 */
u32 GXGenNormalTable(u8 depth, f32* table) {
    s32 i;

    nrm_cnt = 0;
    nrm_tab = table;
    for (i = 7; i >= 0; i--) {
        SubDivNrm(depth, i, odata, ondex);
    }

    return nrm_cnt;
}
