#version 430 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexUV;
layout(location = 3) in vec3 vertexColor;
layout(location = 4) in vec3 vertexTangent;

uniform mat4 model, view, projection;
uniform mat4 lightOffsetMVP;
uniform vec3 globalLightPos;

uniform sampler2D heightMap;

out float displacement;
out vec3 fragNormal, fragNormalMV, fragNormalM;
out vec3 fragVertexPos;
out vec3 lightDirection, viewDirection;
out vec2 fragUV;
out vec4 ShadowCoord;
out vec4 oLightPosM;
out mat3 TBN;

float threshold(float value, float threshold) {
  return (value <= threshold) ? value : threshold;
}

void main(){

  // Calculate tangent to world space matrix
  vec3 T = normalize(vec3( model * vec4(vertexTangent,   0.0)));
  //vec3 B = normalize(vec3( model * vec4(vertexBitangent, 0.0)));
  vec3 N = normalize(vec3( model * vec4(vertexNormal,    0.0)));
  vec3 B  = cross(N,T);
  TBN = mat3(T, B, N);
  

  float heightScale = 0.15;

  // Get the height from the heightmap
  displacement = 1.0 - texture(heightMap, vertexUV).x;

  // Compute the displacement along the normal
  //vec3 vertexPosDisplaced = vertexPos + vertexNormal * displacement * heightScale;
  vec3 vertexPosDisplaced = vertexPos + vec3(0,1,0) * displacement * heightScale;

  // Transform vertex position into homogeneous coordinates
  vec4 oVertexPosM = model * vec4(vertexPosDisplaced, 1.0);
  vec4 oVertexPosMV = view * model * vec4(vertexPosDisplaced, 1.0);
  vec4 oLightPosM = model * vec4(globalLightPos, 1.0);
  vec4 oLightPosMV = view * model * vec4(globalLightPos, 1.0);

  // Compute the tangents
  vec2 lookup = vertexUV;
  vec2 offset = vec2(0.02, 0.0);  // Offset to Neighbors
  vec3 left = vec3(lookup-offset.xy, texture(heightMap, lookup-offset.xy).r*heightScale);
  vec3 right = vec3(lookup+offset.xy, texture(heightMap, lookup+offset.xy).r*heightScale);
  vec3 top = vec3(lookup+offset.yx, texture(heightMap, lookup+offset.yx).r*heightScale);
  vec3 bottom = vec3(lookup-offset.yx, texture(heightMap, lookup-offset.yx).r*heightScale);

  vec3 tx = right-left;
  vec3 ty = top-bottom;

  // Recompute the normal
  fragNormal = normalize(cross(tx,ty));

  // correct projection of normals
  mat3 normal_matrix = transpose(inverse(mat3(view*model)));
  mat3 normal_matrix_2 = transpose(inverse(mat3(model)));

  // Compute the Normal in Model View
  fragNormalMV = normalize(normal_matrix*fragNormal);
  fragNormalM = normalize(normal_matrix_2*fragNormal);
  
  // compute the light direction light_dir
  lightDirection = oVertexPosM.xyz-oLightPosM.xyz;

  // compute the view direction view_dir
  viewDirection = normalize(-oVertexPosMV.xyz);

  // UV Coordinates
  fragUV = vertexUV;

  // Fragment position
  //fragVertexPos = oVertexPosMV.xyz;
  fragVertexPos = oVertexPosM.xyz;

  ShadowCoord = lightOffsetMVP * model * vec4(vertexPosDisplaced, 1.0);

  // Transform vertex position into eye coordinates
  gl_Position = projection * oVertexPosMV;
}
