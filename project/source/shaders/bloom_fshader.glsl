#version 430 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D scene; // normal scene texture
uniform sampler2D bloomBlur; // bloom texture

void main()
{             
    const float gamma = 1.2;
	const float exposure = 1.0;

    vec3 hdrimage = texture(scene, TexCoords).rgb;      
    vec3 bloomcolor = texture(bloomBlur, TexCoords).rgb;

	hdrimage += bloomcolor;
    // tone mapping and gamma correction. If we don't do this the image hdr image is very dark
	vec3 result = vec3(1.0) - exp(-hdrimage * exposure);
    result = pow(hdrimage, vec3(1.0 / gamma));

    FragColor = vec4(result, 1.0f);
}