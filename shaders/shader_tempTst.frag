#version 460
#pragma shader_stage(fragment)

//layout(location = 0) in vec3 fragColor;

layout(push_constant) uniform i_Time { vec2 iResolution; float iTime; float sTime; };
layout(location = 0) out vec4 fragColor;
mat4 a={vec4(1,0,1,0),vec4(1,1,0,0),vec4(0,0,1,0),vec4(0,0,0,1)};
vec2 fragCoord = vec2(gl_FragCoord.x,(iResolution.y-gl_FragCoord.y));
const vec4 iMouse = vec4(0.,0.,0.,0.);
//NOT My SHADER!
// http://www.pouet.net/prod.php?which=57245
// If you intend to reuse this shader, please add credits to 'Danilo Guanabara'

#define t iTime
#define r iResolution.xy

void main(){
	vec3 c;
	float l,z=t;
	for(int i=0;i<3;i++) {
		vec2 uv,p=fragCoord.xy/r;
		uv=p;
		p-=.5;
		p.x*=r.x/r.y;
		z+=.07;
		l=length(p);
		uv+=p/l*(sin(z)+1.)*abs(sin(l*9.-z-z));
		c[i]=.01/length(mod(uv,1.)-.5);
	}
	fragColor=vec4(c/l,t);
}