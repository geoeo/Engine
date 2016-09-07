#version 430 core

in vec2 fragUV;

uniform sampler2D textureSampler;

out vec4 outColor;

// layout (location = 0) out vec4 FragColor;
// layout (location = 1) out vec4 BrightColor;

void main() {

  outColor = texture(textureSampler, fragUV);

  // FragColor = outColor;
  // BrightColor = vec4(0.0);
}