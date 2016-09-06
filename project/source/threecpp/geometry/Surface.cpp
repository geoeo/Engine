#include "Surface.h"

Surface::Surface(unsigned int nTriangles) {

  // Left Bottom Corner, Right Top Corner
  lb = 0;
  rt = 1;

  // number of rows and cols of triangles
  nRows = int(ceil(sqrt(nTriangles/2.0)));
  nCols = nRows;

  // defines number of vertices in the surface
  nVertices = (nCols+1)*6*nRows;
  nColors = nNormals = nTangents = nBitangents = nUVs = nVertices;

  // Vertices of the surface
  vertices = new vec3[nVertices];

  // Normals of the surface
  normals = new vec3[nVertices];

  // tangent of the surface at the vertecies
  tangent = new vec3[nVertices];

  // bitangent of the surface at the vertecies
  bitangent = new vec3[nVertices];

  // Colors of the surface
  colors = new vec3[nVertices];

  // UVs of the surface
  UVs = new vec2[nVertices];

  drawMode = GL_TRIANGLES;

  load();
}

void Surface::load() {

  float i = rt - lb;
  float o = (rt - lb)*0.5;

  float triangleHeight = i / float(nRows);
  float triangleWidth = i / float(nCols);

  // std::cout << "Number of Rows: " << nRows << ", Number of Cols: " << nCols << endl;
  // std::cout << "Overall width: " << nRows*triangleHeight << ", Overall height: " << nCols*triangleWidth << endl;

  for (int row = 0;row < nRows; row++) {

    for (int col = 0;col <= nCols; col++) {

      // Calculate the vertex indices, such that we can insert 2 points
      int index = (col + row * (nCols+1)) * 6;

      // Calculate top and left starting point, for centered plane
      float top = triangleHeight * row - nRows / 2 * triangleHeight;
      float left = triangleWidth * col - nCols / 2 * triangleWidth;

      // Triangle 1
      vertices[index+0] = vec3(top + triangleHeight,0.0,left);
      vertices[index+1] = vec3(top,0.0,left);
      vertices[index+2] = vec3(top + triangleHeight,0.0,left + triangleWidth);

      // Triangle 2
      vertices[index+3] = vec3(top,0.0,left);
      vertices[index+4] = vec3(top,0.0,left + triangleWidth);
      vertices[index+5] = vec3(top + triangleHeight,0.0,left + triangleWidth);

      // Triangle 1
      normals[index+0] = vec3(0.0,0.0,1.0);
      normals[index+1] = vec3(0.0,0.0,1.0);
      normals[index+2] = vec3(0.0,0.0,1.0);

      // Triangle 2
      normals[index+3] = vec3(0.0,0.0,1.0);
      normals[index+4] = vec3(0.0,0.0,1.0);
      normals[index+5] = vec3(0.0,0.0,1.0);



      // Calculate top and left starting point, for UV coordinates
      float uv_top = (top + o)/i;
      float uv_left = (left + o)/i;

      // Triangle 1
      UVs[index+0] = vec2(uv_top + triangleHeight/i,uv_left);
      UVs[index+1] = vec2(uv_top,uv_left);
      UVs[index+2] = vec2(uv_top + triangleHeight/i,uv_left + triangleWidth/i);

      // Triangle 2
      UVs[index+3] = vec2(uv_top,uv_left);
      UVs[index+4] = vec2(uv_top,uv_left + triangleWidth/i);
      UVs[index+5] = vec2(uv_top + triangleHeight/i,uv_left + triangleWidth/i);

      colors[index+0] = vec3(0.0,0.0,0.0);
      colors[index+1] = vec3(0.0,0.0,0.0);
      colors[index+2] = vec3(0.0,0.0,0.0);
      colors[index+3] = vec3(0.0,0.0,0.0);
      colors[index+4] = vec3(0.0,0.0,0.0);
      colors[index+5] = vec3(0.0,0.0,0.0);

	  /* Bitangent calc dont seem to work? Implemented as cross product in water v shader */

	  //Triangle 1
	  vec3 edge1 = vertices[index + 1] - vertices[index + 0];
	  vec3 edge2 = vertices[index + 2] - vertices[index + 1];

	  vec2 deltaUV1 = UVs[index + 1] - UVs[index + 0];
	  vec2 deltaUV2 = UVs[index + 2] - UVs[index + 1];

	  GLfloat f = 1.0f / (deltaUV1.x() * deltaUV2.y() - deltaUV2.x() * deltaUV1.y());

	  vec3 tangent1 = vec3(0.0, 0.0, 0.0);

	  tangent1(0) = f * (deltaUV2.y() * edge1.x() - deltaUV1.y() * edge2.x());
	  tangent1(1) = f * (deltaUV2.y() * edge1.y() - deltaUV1.y() * edge2.y());
	  tangent1(2) = f * (deltaUV2.y() * edge1.z() - deltaUV1.y() * edge2.z());
	  tangent1.normalize();

	  tangent[index + 0] = tangent1;
	  tangent[index + 1] = tangent1;
	  tangent[index + 2] = tangent1;

	  vec3 bitangent1 = vec3(0.0, 0.0, 0.0);

	  bitangent1(0) = f * (-deltaUV2.x() * edge1.x() + deltaUV1.x() * edge2.x());
	  bitangent1(1) = f * (-deltaUV2.x() * edge1.y() + deltaUV1.x() * edge2.y());
	  bitangent1(2) = f * (-deltaUV2.x() * edge1.z() + deltaUV1.x() * edge2.z());
	  bitangent1.normalize();

	  bitangent[index + 0] = bitangent1;
	  bitangent[index + 1] = bitangent1;
	  bitangent[index + 2] = bitangent1;

	  // triangle 2

	  edge1 = vertices[index + 4] - vertices[index + 3];
	  edge2 = vertices[index + 5] - vertices[index + 4];
	  deltaUV1 = UVs[index + 4] - UVs[index + 3];
	  deltaUV2 = UVs[index + 5] - UVs[index + 4];

	  f = 1.0f / (deltaUV1.x() * deltaUV2.y() - deltaUV2.x() * deltaUV1.y());

	  vec3 tangent2 = vec3(0.0, 0.0, 0.0);

	  tangent2(0) = f * (deltaUV2.y() * edge1.x() - deltaUV1.y() * edge2.x());
	  tangent2(1) = f * (deltaUV2.y() * edge1.y() - deltaUV1.y() * edge2.y());
	  tangent2(2) = f * (deltaUV2.y() * edge1.z() - deltaUV1.y() * edge2.z());
	  tangent2.normalize();

	  tangent[index + 3] = tangent2;
	  tangent[index + 4] = tangent2;
	  tangent[index + 5] = tangent2;

	  vec3 bitangent2 = vec3(0.0, 0.0, 0.0);

	  bitangent2(0) = f * (-deltaUV2.x() * edge1.x() + deltaUV1.x() * edge2.x());
	  bitangent2(1) = f * (-deltaUV2.x() * edge1.y() + deltaUV1.x() * edge2.y());
	  bitangent2(2) = f * (-deltaUV2.x() * edge1.z() + deltaUV1.x() * edge2.z());
	  bitangent2.normalize();

	  bitangent[index + 3] = bitangent2;
	  bitangent[index + 4] = bitangent2;
	  bitangent[index + 5] = bitangent2;

    }
  }

  std::cout << "Created Surface with " << nVertices << " vertices" <<endl;
}