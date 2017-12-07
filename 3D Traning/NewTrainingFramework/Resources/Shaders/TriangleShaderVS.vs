precision mediump float;
attribute vec3  a_posL;
attribute vec4 	a_AColor;
uniform   mat4	u_WVP; //world view projection
varying   vec4	VColor;
void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = u_WVP * posL;
	VColor = a_AColor;
}
   