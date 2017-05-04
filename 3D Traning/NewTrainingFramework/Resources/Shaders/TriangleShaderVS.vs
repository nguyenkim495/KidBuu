attribute vec3 a_posL;
attribute vec4 	AColor;
varying vec4 	VColor;
void main()
{
vec4 posL = vec4(a_posL, 1.0);
gl_Position = posL;
VColor = AColor;
}
   