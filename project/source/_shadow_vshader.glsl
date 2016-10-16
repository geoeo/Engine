#version 430 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexUV;

uniform mat4 model,view,projection;
uniform mat4 lightMVP;

void main(){

  gl_Position = (lightMVP * model * vec4(vertexPos, 1.0));

}
