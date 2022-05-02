#version 460
#pragma shader_stage(vertex)



//layout(location = 3) in vec2 Temptest;
//layout(location = 4) in vec3 inColor2;
//layout(location = 5) out vec3 fragColor2;

void main() {
   const vec2 positions[3] = vec2[3](
		vec2(1.f,1.f),
		vec2(-1.f,1.f),
		vec2(0.f,-1.f)
	);

	//const array of colors for the triangle
	const vec3 colors[3] = vec3[3](
		vec3(1.0f, 0.0f, 0.0f), //red
		vec3(0.0f, 1.0f, 0.0f), //green
		vec3(00.f, 0.0f, 1.0f)  //blue
	);
  gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);
  //fragColor2 = inColor2;
}