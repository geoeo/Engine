#version 430 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexUVs;
layout(location = 3) in vec3 vertexColor;
layout(location = 4) in vec3 vertexTangent;
layout(location = 5) in vec3 vertexBitangent;

uniform float time;
uniform mat4 model, view, projection;
uniform mat4 lightOffsetMVP;
uniform vec3 globalLightPos;

uniform sampler2D wavesMap;

out vec3 fragNormal;
out vec3 fragNormalMV,fragNormalM;
out vec3 fragVertexPos;
out vec3 lightDirection, viewDirection;
out vec2 fragUV;
out vec4 ShadowCoord;
out vec4 oLightPosM;
out mat3 TBN;

void main(){

  // Calculate tangent to world space matrix
   vec3 T = normalize(vec3( model * vec4(vertexTangent,   0.0)));
   //vec3 B = normalize(vec3( model * vec4(vertexBitangent, 0.0)));
   vec3 N = normalize(vec3( model * vec4(vertexNormal,    0.0)));
   vec3 B  = cross(N,T);
   TBN = mat3(T, B, N);

  mat4 model_view = view * model;
  // Transform vertex position into homogeneous coordinates
  vec4 oVertexPosMV = model_view* vec4(vertexPos, 1.0);
  vec4 oVertexPosM = model * vec4(vertexPos, 1.0);
  vec4 oLightPosMV = model_view* vec4(globalLightPos, 1.0);
  vec4 oLightPosM = vec4(globalLightPos, 1.0);

  // Transform vertex position into eye coordinates
  gl_Position = projection * oVertexPosMV;

  // Fragment position
  //fragVertexPos = oVertexPosMV.xyz;
  fragVertexPos = oVertexPosM.xyz;   

  ShadowCoord = lightOffsetMVP* model * vec4(vertexPos, 1.0);

  // Load the offset normal from the normalmap
  float waveFreq = 20.0;
  float waveAmpl = 0.5;

  //vec3 normalMap = waveAmpl * texture(wavesMap, vertexUVs * waveFreq + time*0.05).xyz;

  fragNormal = vertexNormal;

  // correct projection of normals
  mat3 normal_matrix = transpose(inverse(mat3(model_view)));
  mat3 normal_matrix_2 = transpose(inverse(mat3(model)));

  // Compute the Normal in Model View
  fragNormalMV = normalize(normal_matrix*fragNormal);
  fragNormalM = normalize(normal_matrix_2*fragNormal);

  // compute the light direction light_dir
  lightDirection = normalize(oLightPosMV.xyz - oVertexPosMV.xyz);

  // compute the view direction view_dir
  viewDirection = normalize(-oVertexPosMV.xyz);

  fragUV = vertexUVs;
}