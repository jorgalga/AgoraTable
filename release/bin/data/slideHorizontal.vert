varying vec2 texCoord;

//Pass through and transfer texture coordinate to the fragment shader.

void main()
{
    texCoord = vec2(gl_MultiTexCoord0);
    gl_Position = ftransform();
}
