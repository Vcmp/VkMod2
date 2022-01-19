#version 450
// layout(binding = 0) uniform UniformBufferObject {
//     mat4 model;
// //    mat4 proj;
// //    mat4 view;
// } ubo;

// layout(location = 0) in vec3 inPosition;
// //layout(location = 1) in vec3 inColor;
// layout(location = 2) in vec2 inTexCoord;

// //layout(location = 0) out vec3 fragColor;
// layout(location = 1) out vec2 fragTexCoord;

void main() {
//    vec2 aa =inPosition.yz*ubo.model;
//    vec2 aaa =inPosition.xy*ubo.model;
    //gl_Position = vec4(inPosition, aa*aaa);

    const vec3 positions[3] = vec3[3](
		vec3(1.f,1.f, 0.0f),
		vec3(-1.f,1.f, 0.0f),
		vec3(0.f,-1.f, 0.0f)
	);
    gl_Position = vec4(positions[gl_VertexIndex], 1.0);
    //fragColor = inColor;
    // fragTexCoord = inTexCoord;
}
