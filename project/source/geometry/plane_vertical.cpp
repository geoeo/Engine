#include "plane_vertical.h"

Plane_Vertical::Plane_Vertical(mat4 model) : Geometry(model){

	drawMode = GL_TRIANGLE_STRIP;

	nVertices = 4;

	vertices = new vec3[nVertices];

	vertices[0] = vec3(-1.0f, 1.0f, 0.0f);
	vertices[1] = vec3(-1.0f, -1.0f, 0.0f);
	vertices[2] = vec3(1.0f, 1.0f, 0.0f);
	vertices[3] = vec3(1.0f, -1.0f, 0.0f);

	UVs = new vec2[nVertices];
	UVs[0] = vec2(0.0f, 1.0f);
	UVs[1] = vec2(0.0f, 0.0f);
	UVs[2] = vec2(1.0f, 1.0f);
	UVs[3] = vec2(1.0f, 0.0f);


}

Plane_Vertical::~Plane_Vertical(){

}