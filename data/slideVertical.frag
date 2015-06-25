#version 150
#extension GL_ARB_texture_rectangle : enable
layout(origin_upper_left) in vec4 gl_FragCoord;
varying vec2 texCoord;

uniform sampler2DRect tex;

vec4 cropLeft;
vec4 cropRight;

uniform vec4 _borderLeft;
uniform vec4 _borderRight;

uniform float useGlobalAlpha;
uniform float globalAlpha;
uniform float borderTop;
uniform float borderBottom;

void main()
{
    cropLeft = _borderLeft;
    cropRight = _borderRight;

    //Sample our textures..
    gl_FragColor = texture2DRect(tex, texCoord);

    //Cut everything on the left and right side of the slider.
    if(gl_FragCoord.y < borderTop || gl_FragCoord.y > borderBottom)
    {
        gl_FragColor.a =  0.0;
    }
    else if(useGlobalAlpha == 1.0)
    {
	gl_FragColor.a =  globalAlpha;
    }
    
}
