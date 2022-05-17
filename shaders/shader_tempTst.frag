#version 460
#pragma shader_stage(fragment)

//layout(location = 0) in vec3 fragColor;

layout(location = 0) out vec4 outColor;
mat4 a={vec4(1,0,1,0),vec4(1,1,0,0),vec4(0,0,1,0),vec4(0,0,0,1)};

void main() { outColor = a*vec4(1.f,0.f,0.f,1.0f); }