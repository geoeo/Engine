#version 430 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 vertexUv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragUVCube;

void main(){
  // Transform vertex position into homogeneous coordinates
  vec4 oVertexPos = vec4(vertexPos, 1.0);

  // Transform vertex position into eye coordinates
  gl_Position = projection * view * model * oVertexPos;

  fragUVCube = vertexPos;
}
