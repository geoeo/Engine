#version 430 core

in vec2 fragUV;

uniform sampler2D textureSampler;

 layout (location = 0) out vec4 FragColor;
 layout (location = 1) out vec4 BrightColor;

out vec4 outColor;

void main() {

  outColor = texture(textureSampler, fragUV);
  FragColor = outColor;
  BrightColor = vec4(0,0,0,1);
}