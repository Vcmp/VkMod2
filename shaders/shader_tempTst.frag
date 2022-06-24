#version 460
#pragma shader_stage(fragment)

//layout(location = 0) in vec3 fragColor;

layout(push_constant) uniform i_Time { ivec2 iResolution; float iTime; float sTime; };
layout(location = 0) out vec4 fragColor;
mat4 a={vec4(1,0,1,0),vec4(1,1,0,0),vec4(0,0,1,0),vec4(0,0,0,1)};
ivec2 fragCoord = ivec2(gl_FragCoord.x,(iResolution.y-gl_FragCoord.y));
const vec4 iMouse = vec4(0.,0.,0.,0.);
//NOT My SHADER!
        /////////////////////////////////////////////////////////////////
       //                                                            ////
      //  "little debugging font"                                   // //
     //                                                            //  //
    //  This utility uses a small bitmapped font (3x5) to render  //   //
   //  floats, primarily intended for debugging. The code can    //    //
  //  be copy/pasta'd into the Common tab as needed.            //     //
 //                                                            //     //
////////////////////////////////////////////////////////////////     //
//                                                            //    //
// Creative Commons Attribution-NonCommercial-ShareAlike      //   //                                       //  //
// 3.0 Unported License                                       //  //
//                                                            // //
// by Val "valalalalala" GvM 💃 2021                          ////
//                                                            ///
////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////
       //                                                            ////
      //  "little debugging font"                                   // //
     //                                                            //  //
    //  This utility uses a small bitmapped font (3x5) to render  //   //
   //  floats, primarily intended for debugging. The code can    //    //
  //  be copy/pasta'd into the Common tab as needed.            //     //
 //                                                            //     //
////////////////////////////////////////////////////////////////     //
//                                                            //    //
// Creative Commons Attribution-NonCommercial-ShareAlike      //   //                                       //  //
// 3.0 Unported License                                       //  //
//                                                            // //
// by Val "valalalalala" GvM 💃 2021                          ////
//                                                            ///
////////////////////////////////////////////////////////////////

const int CHARACTERS[14] = int[14](31599,9362,31183,31207,23524,29671,29679,30994,31727,31719,1488,448,2,3640);

float digitIsOn( int digit, vec2 id ) {   
    if ( id.x < .0 || id.y < .0 || id.x > 2. || id.y > 4. ) return .0;
    return floor( mod( float( CHARACTERS[ int( digit ) ] ) / pow( 2., id.x + id.y * 3. ), 2. ) );
}

float digitSign( float v, vec2 id ) {
    return digitIsOn( 10 - int( ( sign( v ) - 1. ) * .5 ), id );
}

int digitCount( float v ) {
    return int( floor( log( max( v, 1. ) ) / log( 10. ) ) );
}

float digitFirst( vec2 uv, float scale, float v, int decimalPlaces ) {
    vec2 id = floor( uv * scale );

    if ( .0 < digitSign( v, id ) ) return 1.;
    v = abs( v );
    
    int digits = digitCount( v );
    float power = pow( 10., float( digits ) );
    
    float offset = floor( .1 * scale );
    id.x -= offset;
    
    float n;
    for ( int i = 0 ; i < 33 ; i++, id.x -= offset, v -= power * n, power /= 10. ) {
        n = floor( v / power );
        if ( .0 < digitIsOn( int( n ), id ) ) return 1.;   
        if ( i == digits ) {
            id.x -= offset;
            if ( .0 < digitIsOn( int( 12 ), id ) ) return 1.;
        }  
        if ( i >= digits + decimalPlaces ) return .0;    
    }  
    return .0;
}

float digitFirst( vec2 uv, float scale, float v ) {
    return digitFirst( uv, scale, v, 3 );
}

vec3 digitIn( vec3 color, vec3 fontColor, vec2 uv, float scale, float v ) {
    float f = digitFirst( uv, scale, v );
    return mix( color, fontColor, f );
}

vec3 digitIn( vec3 color, vec2 uv, float scale, float v ) {
    return digitIn( color, vec3(1.), uv, scale, v );
}


#define FROM_SCREEN(uv)  ( ( uv - iResolution.xy *.5 ) / iResolution.y * 2. )

vec3 showcase( in vec2 uv ) {
    vec2 id = floor( ( uv + vec2( .5, 1. ) ) * 2.5 );    
    float digit = floor( mod( iTime * 2., 14. ) );
    return vec3( digitIsOn( int( digit ), id ) );
}

void main() {
    vec2 uv = FROM_SCREEN( fragCoord );
    vec2 ms = FROM_SCREEN( iMouse.xy );
    
    vec3 color = showcase( uv );
    vec3 toMix = vec3( 1., .0, .0 );
    
    // this demonstrates typical use
    
    float scale = 70. + 30. * sin( iTime );
    // color = digitIn( color, toMix, uv + vec2( 1.7, -.8 ), scale, 100. * cos( iTime  * .5 ) );
    // color = digitIn( color, toMix, uv + vec2( 1.7, -.6 ), scale, scale ); 
    
    // color = digitIn( color, toMix, uv - ms, scale, ms.x );
    // color = digitIn( color, toMix, uv - ms - vec2(.0,.2), scale, ms.y );
    
    color = digitIn( color, uv - vec2(.8), 44., iTime * .1 ); // white is the default color

    fragColor = vec4( color, 1.0 );
}