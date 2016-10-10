#version 430 core

out vec4 FragColor;
in vec2 fragUV;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

uniform vec3 camPos;
uniform vec3 lightPos;

void main()
{             
    // Retrieve data from G-buffer
    vec3 FragPos = texture(gPosition, fragUV).rgb;
    vec3 Normal = texture(gNormal, fragUV).rgb;
    vec3 Albedo = texture(gAlbedoSpec, fragUV).rgb;
    float Specular = texture(gAlbedoSpec, fragUV).a;
    
    // Then calculate lighting as usual
    vec3 lighting = Albedo; // hard-coded ambient component
    vec3 viewDir = normalize(camPos - FragPos);

    // Diffuse
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Albedo;
    lighting += diffuse;
    
    
    FragColor = vec4(lighting, 1.0);
} 