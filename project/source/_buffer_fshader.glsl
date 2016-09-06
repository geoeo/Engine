#version 430 core

uniform sampler2D textureSampler;

out vec4 outColor;

 layout (location = 0) out vec4 FragColor;
 layout (location = 1) out vec4 BrightColor;

void main() {

    vec4 color = vec4(0.0, 0.0, 0.0, 0.0);
    vec2 lookup = vec2(gl_FragCoord.x/1024.0, gl_FragCoord.y/768.0);

    vec2 offset_x2 = vec2(1.0/1024.0, 0.0);
    vec2 offset_y2 = vec2(0.0, 1.0/768.0);

    color += texture(textureSampler, lookup.xy);
    color += texture(textureSampler, lookup.xy+offset_x2);
    color += texture(textureSampler, lookup.xy-offset_x2);
    color += texture(textureSampler, lookup.xy+offset_y2);
    color += texture(textureSampler, lookup.xy-offset_y2);
    color /= 5.0;

    outColor = vec4(color.rgb, 1.0);

     FragColor = outColor;
     BrightColor = vec4(0);
}