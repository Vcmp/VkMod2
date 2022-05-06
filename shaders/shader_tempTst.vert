#version 460
#pragma shader_stage(vertex)
layout(binding = 0) uniform UBO { mat4 model; }
ubo;

layout(location = 1) in vec3 inPosition;
layout(location = 2) in vec3 inColor;

layout(location = 0) out vec3 fragColor;

void main() {
  gl_Position = ubo.model * vec4(inPosition, 1.0);
  //fragColor = inColor;
}