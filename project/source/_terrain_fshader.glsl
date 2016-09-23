#version 430 core

uniform vec3 color;
uniform vec3 globalLightPos,globalLightIa, globalLightId, globalLightIs;
uniform vec3 ka, kd, ks;
uniform vec3 camPos;
uniform float p;

uniform sampler2D snowTexture;
uniform sampler2D rockTexture;
uniform sampler2D landTexture;
uniform sampler2D woodTexture;
uniform sampler2D sandTexture;

// ShadowMap
uniform sampler2DShadow shadowMap;

uniform uint featureTextures;
uniform uint featureSteepTextures;
uniform uint featureShadows;
uniform uint featureSmoothShadows;
uniform uint debugSlope;
uniform uint debugDisplacement;
uniform uint debugVisibility;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

layout (location = 2) out vec3 gPosition;
layout (location = 3) out vec3 gNormal;
layout (location = 4) out vec4 gAlbedoSpec;

// Input data
in float displacement;
in vec2 fragUV;
in vec3 fragVertexPos, fragVertexPosMW;
in vec3 fragNormal, fragNormalMW,fragNormalM;
in vec3 lightDirection, viewDirection;
in vec4 ShadowCoord;
in vec4 oLightPosM;

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
    float bias = max(0.85 * (1.0 - dot(normal, lightDir)), 0.005);
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

float scale(float _val, float _min, float _max) {
  return clamp(abs((_val - _min) / (_max - _min)), 0, 1);
}

void main() {

    vec3 fragColor = color;
    float slope = 1.0 - abs(dot(fragNormal, vec3(0.0, 0.0, 1.0)));
    float rockStep = smoothstep(0.3, 0.35, slope);

    float snowFreq = 10.0;
    vec3 snowColor = texture(snowTexture, fragUV*snowFreq).xyz;
    float snowLimit = 0.8;

    float rockFreq = 20.0;
    vec3 rockColor = texture(rockTexture, fragUV*rockFreq).xyz;
    float rockLimit = snowLimit - 0.2;

    float landFreq = 30.0;
    vec3 landColor = texture(landTexture, fragUV*landFreq).xyz;
    float landLimit = rockLimit - 0.2;

    float woodFreq = 30.0;
    vec3 woodColor = texture(woodTexture, fragUV*woodFreq).xyz;
    float woodLimit = landLimit - 0.2;

    float sandFreq = 30.0;
    vec3 sandColor = texture(sandTexture, fragUV*sandFreq).xyz;
    float sandLimit = woodLimit - 0.2;

    if (featureTextures == 1) {
        if (displacement > snowLimit) {
          fragColor = snowColor;
        }
        else if (displacement > rockLimit) {
          fragColor = mix(rockColor, snowColor, scale(displacement, rockLimit, snowLimit));
        }
        else if (displacement > landLimit) {
          fragColor = mix(landColor, rockColor, scale(displacement, landLimit, rockLimit));
        }
        else if (displacement > woodLimit) {
          fragColor = mix(woodColor, landColor, scale(displacement, woodLimit, landLimit));
        }
        else {
          fragColor = sandColor;
        }

        if (featureSteepTextures == 1) {
            // Rocks, when too steep
            fragColor = mix(fragColor, rockColor, rockStep);
        }
    }

    // compute ambient term
    vec3 t_ambient = globalLightIa*ka*fragColor;
    
    vec3 lightDir = normalize(globalLightPos-fragVertexPos);

    // compute diffuse term
    //vec3 t_diffuse = globalLightId*kd*fragColor*max(dot(fragNormal, normalize(lightDirection)),0.0);
    vec3 t_diffuse = globalLightId*kd*fragColor*max(dot(fragNormalM, lightDir),0.0);

    // compute specular term
    //vec3 R = normalize(2.0 * dot(fragNormal, lightDirection)*fragNormal - lightDirection);
    //vec3 t_specular = globalLightIs*ks*fragColor * pow(max(dot(normalize(viewDirection), R), 0.0), p);
    
    vec3 R = normalize(2.0 * dot(fragNormalM, lightDir)*fragNormalM - lightDir);
    float spec = pow(max(dot(normalize(camPos-fragVertexPos), R), 0.0), p);
    vec3 t_specular = globalLightIs*ks*fragColor*spec;

    float visibility = 1.0;
    if (featureShadows == 1){
        visibility = simpleShadow(vec3(0.0), 1e-6);

        if (featureSmoothShadows == 1){
            visibility = 1.0 - smoothShadow(fragNormalM,lightDir);
        }
    }

    outColor = vec4(t_ambient + t_diffuse *visibility + t_specular*visibility, 1.0);
    gPosition = fragVertexPos;
    gNormal = fragNormalM;
    gAlbedoSpec.rgb = t_ambient;
    gAlbedoSpec.a = spec;

    if (debugVisibility == 1) {
        // DEBUG visibility
        outColor = vec4(vec3(visibility), 1.0);
    }
    // outColor = vec4(vec3(lookupShadow(vec2(0.0), 0.0), 1.0, 0.0), 1.0);

    // DEBUG texture
    // outColor = vec4(fragColor, 1.0);

    if (debugSlope == 1) {
        // DEBUG slope
        outColor = vec4(vec3(slope), 1.0);
    }

    if (debugDisplacement == 1) {
        // DEBUG displacement
        outColor = vec4(vec3(displacement),1.0);
    }
     FragColor = outColor;
     BrightColor = vec4(0,0,0,1);
}