#version 430 core

uniform vec3 color;
uniform vec3 globalLightPos;
uniform vec3 globalLightIa, globalLightId, globalLightIs;
uniform vec3 ka, kd, ks;
uniform vec3 camPos;
uniform float p;

uniform float time;

uniform sampler2D wavesMap;
uniform samplerCube cubeSampler;
uniform sampler2D refractionObjects;
uniform mat4 model, view;

uniform uint featureShadows;
uniform uint featureSmoothShadows;
uniform uint featureReflection;
uniform uint debugVisibility;
uniform uint debugNormals;
uniform uint debugReflection;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

layout (location = 2) out vec3 gPosition;
layout (location = 3) out vec3 gNormal;
layout (location = 4) out vec4 gAlbedoSpec;

// Input data
in vec3 fragNormal;
in vec3 fragNormalMV;
in vec3 lightDirection, viewDirection;
in vec4 ShadowCoord;
in vec4 oLightPosM;
in mat3 TBN;

//gBufferValues
in vec3 fragPos;
in vec3 fragNormalM;
in vec2 fragUV;

// ShadowMap
uniform sampler2DShadow shadowMap;

// Ouput data
out vec4 outColor;

// Soft Shadows
// @src: http://www.learnopengl.com/#!Advanced-Lighting/Shadows/Shadow-Mapping
float simpleShadow(vec3 offset, float bias) {
    // Resolution of Shadowmap == 1 Pixel
    float kernel = 1.0/1024.0;
    // map coordiantes to texel space [0,1]
    //vec3 proj = (ShadowCoord.xyz/ShadowCoord.w) * 0.5 + vec3(0.5);
    //return textureProj(shadowMap, proj /* + vec3(offset.x*kernel, offset.y*kernel, bias) */);
    //vec4 s = ShadowCoord*0.5 +  + vec4(0.5);
    //return shadow2DProj(shadowMap,ShadowCoord+vec4(offset.x*kernel*ShadowCoord.w, offset.y*kernel*ShadowCoord.w, bias,0)).w;

   // perform perspective divide
    vec3 projCoords = ShadowCoord.xyz / ShadowCoord.w;
    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + vec3(0.5);
    // Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    vec3 coords = projCoords.xyz;
    float closestDepth = texture(shadowMap, coords + offset * kernel).r; 
    // Get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // Check whether current frag pos is in shadow
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

    return shadow;
}

float smoothShadow(vec3 normal, vec3 lightDir) {
    float bias = max(0.9 * (1.0 - dot(normal, lightDir)), 0.05);

    float visibility = 1.0;
    float shadow = 0.0;

    if (ShadowCoord.w > 1.0) {
        float x = 0;
        float y = 0;

        for (y = -1.0 ; y <=1.0 ; y+=1.0) {
            for (x = -1.0 ; x <=1.0 ; x+=1.0) {
                shadow += simpleShadow(vec3(x,y,0),bias);
            }
        }

        shadow /= 9.0 ;
        //shadow += 0.2;
    }
    return shadow;
}

void main(){

    vec3 fragColor = color;
    vec3 reflectColor = vec3(0.0,0.0,0.0);
    
    float waveFreq = 20.0;
   float waveAmpl = 0.5;
    

   vec3 normal = texture(wavesMap, fragUV*waveFreq + time*0.05).xyz;
   // map from texel [0,1] to vector [-1,1] range
   normal = normalize(normal *2.0 -1.0);
   normal = normalize(TBN * normal); 

   //vec3 normal_r =  vec3(0,1,0);
   //normal = transpose(inverse(mat3(model))) * normal;
   //normal_r = normalize(normal_r);
   
   //normal = normal_r;

    if (featureReflection == 1){
        float air_to_water_fresnel = 1.00 / 1.52;
        vec3 I = normalize(camPos-fragPos);
        vec3 R = reflect(I, normal);
        reflectColor = texture(cubeSampler, R).xyz;


        fragColor = reflectColor;
    }

    //vec2 wavesSample = waveAmpl * texture(wavesMap, fragUV * waveFreq + 0.05).xy;
    //vec4 refractColor = texture(refractionObjects,(I.xy*2)-1) + vec4(0.2,0,0,0);
    
    vec3 lightDir = normalize(globalLightPos- fragPos);

    // compute ambient term
    vec3 t_ambient = 3*(globalLightIa*ka)*fragColor / 4;

    // compute diffuse term
    //vec3 t_diffuse = globalLightId*kd*fragColor*max(dot(fragNormalMV, normalize(lightDirection)),0.0);
    vec3 t_diffuse = globalLightId*kd*fragColor*max(dot(normal,lightDir),0.0);

    // compute specular term
    //vec3 R = normalize(2.0 * dot(fragNormalMV, lightDirection)*fragNormalMV - lightDirection);
    //vec3 t_specular = globalLightIs*ks*fragColor * pow(max(dot(normalize(viewDirection), R), 0.0), p);
    
    vec3 R = normalize(2.0 * dot(normal, lightDir)*normal - lightDir);
    float spec = pow(max(dot(normalize(camPos-fragPos), R), 0.0), p);
    vec3 t_specular = globalLightIs*ks*fragColor*spec;

    float visibility = 1.0;

    if (featureShadows == 1){
        visibility = simpleShadow(vec3(0.0), 1e-6);

        if (featureSmoothShadows == 1){
            visibility = 1.0 - smoothShadow(normal,lightDir);
        }
    }
   
    outColor = vec4(t_ambient +  t_diffuse  *visibility + t_specular*visibility, 1.0);
    
    //outColor = vec4(normal_r,1.0);

    if (debugReflection == 1) {
        // DEBUG Reflection
        outColor = vec4(reflectColor, 1.0);
    }

    if (debugNormals == 1){
        // DEBUG normalmap
        outColor = vec4(fragNormalMV, 1.0);
    }

    // DEBUG t_ambient
    // outColor = vec4(t_ambient, 1.0);

    if (debugVisibility == 1){
        // DEBUG visibility
        outColor = vec4(vec3(visibility), 1.0);
    }
    //FragColor = vec4(TBN[1],1.0);
    
    //FragColor = vec4(view[1][0],view[1][1],view[1][2],1.0);
    
    FragColor = outColor;

    gPosition = fragPos;
    gNormal = normal;
    gAlbedoSpec.rgb = t_diffuse * visibility;
    gAlbedoSpec.a = spec;

    float brightness = dot(outColor.xyz, vec3(0.2126, 0.5152, 0.0722));
    if(brightness > 0.6) {
        BrightColor =  outColor;
    }
    else {
        BrightColor = vec4(0,0,0,1);
    }
}