#version 430 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D textureSampler;
uniform bool horizontal;

// blur from http://learnopengl.com/#!Advanced-Lighting/Bloom
uniform float weight[5] = float[] (0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);

void main()
{
     int interations = 5;
     vec2 tex_offset = 1.0 / textureSize(textureSampler, 0); // gets size of single texel
     vec3 textureSample = texture(textureSampler, TexCoords).rgb;
     vec3 result = textureSample * weight[0];
     if(horizontal)
     {
    // samples along the horizonal and adds the blurred sample value to the result
         for(int i = 1; i < interations; ++i)
         {
            result += texture(textureSampler, TexCoords + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(textureSampler, TexCoords - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
         }
     }
     else
     {
     // samples along the vertical and adds the blurred sample value to the result
         for(int i = 1; i < interations; ++i)
         {
             result += texture(textureSampler, TexCoords + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
             result += texture(textureSampler, TexCoords - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
         }
     }
     
     FragColor =vec4(result,1.0);
     // DEBUG
     //FragColor = vec4(1.0,0,0, 1.0);
}