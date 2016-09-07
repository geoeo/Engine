#version 430 core

// Interpolated values from the vertex shaders
//in vec3 fragColor;


// Ouput data
out vec4 outColor;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

void main(){
    // Output color = color specified in the vertex shader,
    // interpolated between all 3 surrounding vertices
    outColor = vec4(1.0,0,0, 1.0);
     FragColor = outColor;
     //BrightColor = vec4(0,0,0,1);
}