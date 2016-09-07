#version 430 core
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(vertex, 1.0f);
    vs_out.FragPos = vec3(model * vec4(vertex, 1.0));   
        
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vs_out.Normal = normalize(normalMatrix * normal);
}