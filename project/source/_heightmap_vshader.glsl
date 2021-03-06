#version 430 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexUV;

out vec2 fragUV;

void main(){
  gl_Position = vec4(vertexPos, 1.0);
  fragUV = vertexUV;
}
