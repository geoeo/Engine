#version 430 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexUV;

uniform mat4 model, view, projection;

out vec3 FragPos;
out vec3 Normal;
out vec2 fragUV;
//out vec3 fragUV;

void main(){

  vec4 worldPos =  model * vec4(vertexPosition, 1.0);
  FragPos = worldPos.xyz;
  fragUV = vertexUV;
  //fragUV = vertexPosition;
  mat3 normalMatrix = transpose(inverse(mat3(model)));
  Normal = normalMatrix * vertexNormal;

  gl_Position = projection * view * worldPos;
}