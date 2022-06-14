#version 460
#pragma shader_stage(vertex)
layout(binding = 0) uniform UBO { mat4 model; }
ubo;

//layout(location = 1) in vec3 inPosition;
//layout(location = 2) in vec3 inColor;

layout(location = 0) out vec3 fragColor;

const vec2 tri[3] = vec2[3](
    vec2(1.f,1.f),
    vec2(1.f,-3.f),
    vec2(-3.f,1.f)
);

void main() {
  gl_Position = vec4(tri[gl_VertexIndex], 0.0, 1.0);
  //fragColor = inColor;
}