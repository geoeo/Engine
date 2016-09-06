#version 430 core

layout(location = 0) in vec3 vertexPos;

uniform mat4 model, view, projection;
uniform mat4 lightOffsetMVP;
uniform vec3 globalLightPos;

out vec3 fragVertexPos;
out vec3 lightDirection, viewDirection;
out vec4 ShadowCoord;

void main(){
  // Transform vertex position into homogeneous coordinates
  vec4 oVertexPosMV = view * model * vec4(vertexPos, 1.0);
  vec4 oLightPosMV = view * model * vec4(globalLightPos, 1.0);

  // Transform vertex position into eye coordinates
  gl_Position = projection * oVertexPosMV;

  // Fragment position
  fragVertexPos = oVertexPosMV.xyz;

  // compute the light direction light_dir
  lightDirection = normalize(oLightPosMV.xyz - oVertexPosMV.xyz);

  // compute the view direction view_dir
  viewDirection = normalize(-oVertexPosMV.xyz);

  ShadowCoord = lightOffsetMVP * vec4(vertexPos, 1.0);
}