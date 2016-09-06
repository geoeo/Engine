#version 430 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
} fs_in;

//uniform vec3 lightColor;

void main()
{           
    FragColor = vec4(2.0,2.0,2.0, 1.0); // bright white light
    float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    //if(brightness > 1.0)
    BrightColor = vec4(FragColor.rgb, 1.0);
}