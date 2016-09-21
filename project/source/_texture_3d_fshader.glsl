#version 430 core

in vec3 fragUVCube;

uniform samplerCube cubeSampler;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

out vec4 outColor;

void main(){
    outColor = texture(cubeSampler, fragUVCube);
    float brightness = dot(outColor.xyz, vec3(0.2126, 0.7152, 0.0722));
    FragColor = outColor;
    if(brightness > 1) {
        BrightColor =  outColor;
    }
    else {
        BrightColor = vec4(0,0,0,1);
    }
}
