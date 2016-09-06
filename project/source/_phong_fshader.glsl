#version 430 core

uniform vec3 color;
uniform vec3 globalLightIa, globalLightId, globalLightIs;
uniform vec3 ka, kd, ks;
uniform float p;

// Input data
in vec3 fragVertexPos;
in vec3 lightDirection, viewDirection;
in vec4 ShadowCoord;

 layout (location = 0) out vec4 FragColor;
 layout (location = 1) out vec4 BrightColor;

// ShadowMap
uniform sampler2DShadow shadowMap;

// Ouput data
out vec4 outColor;

// Soft Shadows
// @src: http://fabiensanglard.net/shadowmappingPCF/index.php
float lookupShadow(vec2 offset, float bias) {
    // Resolution of Shadowmap == 1 Pixel
    float kernel = 1.0/1024.0;
    // map coordiantes to texel space [0,1]
    vec3 proj = (ShadowCoord.xyz/ShadowCoord.w) * 0.5 + vec3(0.5);
    return texture(shadowMap, proj + vec3(offset.x*kernel, offset.y*kernel, bias));
}

float getShadow() {
    float bias = -1e-6;
    float visibility = 1.0;
    float shadow = 0.0;

    if (ShadowCoord.w > 1.0) {
        float x = 0;
        float y = 0;

        for (y = -1.5 ; y <=1.5 ; y+=1.0) {
            for (x = -1.5 ; x <=1.5 ; x+=1.0) {
                shadow += lookupShadow(vec2(x,y),bias);
            }
        }

        shadow /= 16.0 ;
        shadow += 0.2;
    }
    return shadow;
}

void main(){

    // Estimate the normal
    vec3 X = dFdx(fragVertexPos);
    vec3 Y = dFdy(fragVertexPos);
    vec3 normal = normalize(cross(X, Y));

    // compute ambient term
    vec3 t_ambient = globalLightIa*ka*color;

    // compute diffuse term
    vec3 t_diffuse = globalLightId*kd*color*max(dot(normal, normalize(lightDirection)),0.0);

    // compute specular term
    vec3 R = normalize(2.0 * dot(normal, lightDirection)*normal - lightDirection);
    vec3 t_specular = globalLightIs*ks*color * pow(max(dot(normalize(viewDirection), R), 0.0), p);

    float visibility = getShadow();

    outColor = vec4(t_ambient + t_diffuse + t_specular, 1.0);

    // DEBUG visibility
    // outColor = vec4(vec3(visibility), 1.0);
     FragColor = outColor;
     BrightColor = vec4(0,0,0,1);
}