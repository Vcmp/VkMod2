#version 460
#pragma shader_stage(fragment)

//layout(location = 0) in vec3 fragColor;

layout(push_constant) uniform i_Time { vec2 iResolution; uvec2 iMouse; float iTime; };
layout(location = 0) out vec4 fragColor;
mat4 a={vec4(1,0,1,0),vec4(1,1,0,0),vec4(0,0,1,0),vec4(0,0,0,1)};
vec2 fragCoord = vec2(gl_FragCoord.x,(iResolution.y-gl_FragCoord.y));
//const vec4 iMouse = vec4(0.,0.,0.,0.);
//NOT My SHADER!
//https://www.shadertoy.com/view/ldtXD2 [JS1k 2016 winner clone: BlueHeisenberg]
float T = 34962.0;

void main()
{
	//vec2 uv = fragCoord.xy / iResolution.xy;
	//fragColor = vec4(uv,0.5+0.5*sin(iTime),1.0);
    
    precision mediump float;
    vec2 R, M;
	T += iTime;
    
    R.x = iResolution.x * 0.8;
    R.y = iResolution.y * 0.8;
    M.x = iMouse.x == 0.0 ? iTime/100.0 : iMouse.x;
    M.y = iMouse.y == 0.0 ? iTime/100.0 : iMouse.y;
    
    float t = 5e-3;
    for (float i = 0.; i < 64.; i++) {
        vec3 p = vec3((2. * fragCoord.xy - R) / R.yy, t - 1.), b = vec3(.707, .707, 0);
        float a = T;
        p.xz *= mat2(cos(a), -sin(a), sin(a), cos(a));
        for (float i = 0.; i < 20.; i++) {
            a = (M / R * 6.).x;
            p.xz *= mat2(cos(a), -sin(a), sin(a), cos(a));
            a = (M / R * 6.).y;
            p.xy *= mat2(cos(a), -sin(a), sin(a), cos(a));
            p -= min(0., dot(p, b)) * b * 2.;
            b = b.zxx;
            p -= min(0., dot(p, b)) * b * 2.;
            b = b.zxz;
            p -= min(0., dot(p, b)) * b * 2.;
            b = b.xxy;
            p = p * 1.5 - .25;
        }
        t += length(p) / 3325.;
        if (length(p) / 3325. < 5e-3 || t > 2.) {
            b = vec3(1);
            p *= .5;
            fragColor = vec4(p / length(p) * (t < 2. ? 5. / i : i / 64.), dot(p, b));
            break;
        }
    }
}