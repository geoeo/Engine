#include "Geometry.h"

Geometry::Geometry(){

  vertices = new vec3[0];
  colors = new vec3[0];
  normals = new vec3[0];
  UVs = new vec2[0];
  tangent = new vec3[0];
  bitangent = new vec3[0];
  children = new Geometry[0];
}

Geometry::Geometry(vector<vec3> verticesIn, vector<vec3> normalsIn,vector<vec3> tangentsIn,vector<vec3> bitangentsIn, vector<vec2> textureCoordiantesIn, vector<GLuint> indicesIn){

	nVertices = verticesIn.size();
	vertices = new vec3[nVertices];
	for (int i = nVertices-1; i >=0 ; i--){
		vertices[i] = verticesIn.back();
		verticesIn.pop_back();
	}

	nNormals = normalsIn.size();
	normals = new vec3[nNormals];
	for (int i = nNormals - 1; i >= 0; i--){
		normals[i] = normalsIn.back();
		normalsIn.pop_back();
	}

	nUVs = textureCoordiantesIn.size();
	UVs = new vec2[nUVs];
	for (int i = nNormals - 1; i >= 0; i--){
		UVs[i] = textureCoordiantesIn.back();
		textureCoordiantesIn.pop_back();
	}
	

	nTangents = tangentsIn.size();
	tangent = new vec3[nNormals];
	for (int i = nTangents - 1; i >= 0; i--){
		tangent[i] = tangentsIn.back();
		tangentsIn.pop_back();
	}

	nBitangents = bitangentsIn.size();
	bitangent = new vec3[nBitangents];
	for (int i = nTangents - 1; i >= 0; i--){
		bitangent[i] = bitangentsIn.back();
		bitangentsIn.pop_back();
	}

	indices = indicesIn;
	colors = new vec3[0];
	nColors = 0;
	drawMode = GL_TRIANGLES;
}

Geometry::~Geometry(){
    delete vertices;
    delete colors;
    delete normals;
    delete UVs;
	delete tangent;
	delete bitangent;
	delete children;
}