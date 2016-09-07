#version 430 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D scene; // normal scene texture
uniform sampler2D bloomBlur; // bloom texture

void main()
{             
    vec3 bloomImage = texture(scene, TexCoords).rgb;      
    vec3 bloomcolor = texture(bloomBlur, TexCoords).rgb;

	bloomImage += bloomcolor;

    FragColor = vec4(bloomImage, 1.0f);
}