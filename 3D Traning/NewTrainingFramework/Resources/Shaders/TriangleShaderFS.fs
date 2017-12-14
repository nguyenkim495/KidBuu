precision mediump float;
//varying vec4 	VColor;

varying	vec2 v_uv;
uniform sampler2D u_s_Texture;


void main()
{
	gl_FragColor = texture2D(u_s_Texture, v_uv);
	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
