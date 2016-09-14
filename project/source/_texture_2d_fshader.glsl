#version 430 core

in vec2 fragUV;

uniform sampler2D textureSamplerDiffuse;
uniform sampler2D textureSamplerSpecular;
uniform sampler2D textureSamplerNormal;

 layout (location = 0) out vec4 FragColor;
 layout (location = 1) out vec4 BrightColor;

out vec4 outColor;

void main() {

  vec4 diffuseColor = texture(textureSamplerDiffuse, fragUV);
  vec4 MaterialSpecularCoeff = texture(textureSamplerSpecular, fragUV);
  
  outColor = diffuseColor;
  FragColor = outColor;
  BrightColor = vec4(0,0,0,1);
}