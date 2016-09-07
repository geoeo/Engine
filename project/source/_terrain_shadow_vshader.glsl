#version 430 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexUV;

uniform sampler2D heightMap;

uniform mat4 model,view,projection;
uniform mat4 lightMVP;

out float heightMapVal;

void main(){

  float heightScale = 0.15;

  // Get the height from the heightmap
  float displacement = 1.0 - texture(heightMap, vertexUV).x;

  // Compute the displacement along the normal
  vec3 vertexPosDisplaced = vertexPos + vec3(0,1,0) * displacement * heightScale;
  heightMapVal = texture(heightMap, vertexUV).x;
  gl_Position = (lightMVP * model * vec4(vertexPosDisplaced, 1.0));

}
