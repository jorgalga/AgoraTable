#version 150
#extension GL_ARB_texture_rectangle : enable
layout(origin_upper_left) in vec4 gl_FragCoord;
varying vec2 texCoord;

uniform sampler2DRect tex;


uniform float globalAlpha;
uniform float borderLeft;
uniform float borderRight;

void main()
{
    
    //Sample our textures..
    gl_FragColor = texture2DRect(tex, texCoord);

    //Cut everything on the left and right side of the slider.
    if(gl_FragCoord.x < borderLeft || gl_FragCoord.x > borderRight)
    {
        gl_FragColor.a =  0.0;
    }
    else
    {
	gl_FragColor.a =  globalAlpha;
    }
    
}
