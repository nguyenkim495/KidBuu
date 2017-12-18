//Model is lighted
//frag shader
precision mediump float;

uniform sampler2D u_s_Texture;

varying	vec2 v_uv;
varying vec4 v_posW;
varying vec3 v_normal;

uniform vec4 u_EyePos;//camera position
uniform vec3 u_LightDirection;
uniform float weight = 0.90;// 0-1
uniform vec4 LightDiffuseColor = vec4(1.0, 1.0, 1.0, 1.0);
uniform vec4 LightSpecularColor = vec4 (1.0, 1.0, 1.0, 1.0);


void main()
{   //
    vec4 Normal = vec4(v_normal, 1.0);
    vec4 LightDirection = v_posW - vec4(u_LightDirection, 1.0);
    //
    vec4 ObjColor = texture2D( u_s_Texture, v_uv );
    vec4 AmbientComponent = vec4(0.3,0.3,0.3,1.0);//dark
    //vec4 DiffuseComponent = max(dot(Normal, -LightDirection), 0.0)* LightDiffuseColor;
	
	vec4 DiffuseComponent = max(dot(Normal, -LightDirection), 0.0)* LightDiffuseColor;
    
	vec4 reflectVector = normalize((reflect(LightDirection, Normal)));
    vec4 toEye = normalize(u_EyePos - v_posW);
    vec4 SpecularComponent = pow(max(dot(reflectVector,toEye),0.0),20.0)* LightSpecularColor;
    
	vec4 FinalColor = vec4(((AmbientComponent * weight + DiffuseComponent * (1 - weight)) * ObjColor + SpecularComponent).xyz, ObjColor.w);
   
    gl_FragColor = FinalColor;
    
    //بارگیری(<span dir="ltr">{loaded}</span> MB از {total} <span dir="ltr">MB</span>)
}
