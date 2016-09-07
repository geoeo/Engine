#version 430 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexUV;
layout(location = 3) in vec3 vertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 fragUV;

void main(){

  // vec3 translation_world = vec3(model[0][3], model[1][3], model[2][3]);
  // vec3 cam_right_world = vec3(view[0][0], view[1][0], view[2][0]);
  // vec3 cam_up_world = vec3(view[0][1], view[1][1], view[2][1]);

  // vec3 vertexPos_worldspace = translation_world + cam_right_world *model[0][0]* vertexPos.x + cam_up_world *model[1][1] *vertexPos.y;

  vec4 oVertexPos = vec4(vertexPos, 1.0);

  gl_Position = projection * view * model * oVertexPos;

  fragUV = vertexUV;
}