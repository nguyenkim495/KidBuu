precision mediump float;
attribute	vec3	a_posL;
attribute	vec2	a_uv;
varying		vec2	v_uv;

attribute	vec4	a_AColor;
uniform	mat4	u_WVP; //world view projection

void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	v_uv = a_uv;
	gl_Position = u_WVP * posL;
}
   