//Model is lighted
//vertex shader

precision mediump float;
attribute	vec3	a_posL;

attribute   vec4    a_posW;
varying     vec4    v_posW;

attribute	vec2	a_uv;
varying		vec2	v_uv;

attribute	vec3	a_normal;
varying		vec3	v_normal;

uniform	mat4	u_WVP; //world view projection
uniform mat4	u_World;

void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	v_uv = a_uv;
    v_posW = a_posW*u_World;
	v_normal = a_normal;
	gl_Position = u_WVP * posL;
}
   