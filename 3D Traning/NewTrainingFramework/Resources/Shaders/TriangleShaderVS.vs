precision mediump float;
attribute   vec3  a_posL;
varying		vec2 v_uv;

attribute vec4 	a_AColor;
uniform   mat4	u_WVP; //world view projection
attribute   vec2	a_uv;



void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = u_WVP * posL;
	v_uv = a_uv;
}
   