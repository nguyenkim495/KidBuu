precision mediump float;

uniform sampler2D u_s_Texture;
uniform sampler2D u_s_TextureDispl;
uniform sampler2D u_s_TextureMask;
varying	vec2 v_uv;
uniform float   u_Time;
uniform float   dMax = 0.05;


void main()
{
    vec2 disp = texture2D(u_s_TextureDispl, vec2(v_uv.x, v_uv.y + u_Time)).rg;
    vec2 offset = (2.0 * disp - 1.0) * dMax;
    vec2 Tex_coords_displaced = v_uv + offset;
    vec4 fire_color = texture2D(u_s_Texture, Tex_coords_displaced);
    vec4 AlphaValue = texture2D(u_s_TextureMask, v_uv);
    gl_FragColor = fire_color * (1.0, 1.0, 1.0, AlphaValue.r);
}
