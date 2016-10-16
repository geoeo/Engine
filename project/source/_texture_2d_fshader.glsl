#version 430 core

in vec2 fragUV;

// gBuffer values
in vec2 TexCoords;
in vec3 FragPos; // Worldspace
in vec3 Normal;

uniform sampler2D textureSamplerDiffuse;
uniform sampler2D textureSamplerSpecular;
uniform sampler2D textureSamplerNormal;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

layout (location = 2) out vec4 gPosition;
layout (location = 3) out vec3 gNormal;
layout (location = 4) out vec4 gAlbedoSpec;

out vec4 outColor;

float near = 0.1f; 
float far  = 1000.0; 
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main() {

  vec4 diffuseColor = texture(textureSamplerDiffuse, fragUV);
  vec4 MaterialSpecularCoeff = texture(textureSamplerSpecular, fragUV);

  gPosition.rgb = FragPos;
  gPosition.a = LinearizeDepth(gl_FragCoord.z)/far;
  gNormal = normalize(Normal);
  gAlbedoSpec.rgb = diffuseColor.rgb;
  gAlbedoSpec.a = MaterialSpecularCoeff.r;
  
  outColor = diffuseColor;
  //outColor = vec4(diffuseColor.a,diffuseColor.a,diffuseColor.a,1); // hack for visualising the specular coeff
  //outColor = vec4(1,0,0,1);
  //FragColor = outColor;
  BrightColor = vec4(0,0,0,1);
}