#version 430 core

 layout(location = 0) out float fragDepth;
 in float heightMapVal;

 void main(){
   fragDepth = gl_FragCoord.z;
 }


// DEBUG
out vec4 fragColor;

float getLinDepth() {
  float n = 0.1; // camera z near or gl_DepthRange.near
  float f = 5.0f; // camera z far or gl_DepthRange.far
  float z = gl_FragCoord.z;
  return (2.0 * n) / (f + n - z * (f - n));
}

//void main(){
//  float v = gl_FragCoord.z/gl_FragCoord.w;
//  fragColor = vec4(vec3(getLinDepth()), 1.0);
  //fragColor = vec4(heightMapVal,heightMapVal,heightMapVal,1.0);
//}