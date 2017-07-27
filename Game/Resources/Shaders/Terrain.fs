precision mediump float;
uniform sampler2D u_tex1;
uniform sampler2D u_tex2;
uniform sampler2D u_tex3;
uniform sampler2D u_tex4;
varying vec2 v_uv;
void main(void)
{
	vec4 BlendMap = texture2D(u_tex1, v_uv);
	vec4 Dirt = texture2D(u_tex2, v_uv * 50.0);
	vec4 Rock = texture2D(u_tex3, v_uv * 50.0);
	vec4 Grass = texture2D(u_tex4, v_uv * 50.0);
    gl_FragColor = (BlendMap.r * Dirt + BlendMap.g * Rock + BlendMap.b * Grass)/(BlendMap.r + BlendMap.g + BlendMap.b);
	gl_FragColor.a = 1.0;
}