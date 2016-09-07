#version 430 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexUV;

uniform mat4 model, view, projection;

//out vec2 fragUV;
out vec3 fragUV;

void main(){

  //fragUV = vertexUV;
    fragUV = vertexPosition;

  gl_Position = projection * view * model * vec4(vertexPosition, 1.0);
}