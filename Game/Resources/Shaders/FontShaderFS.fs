precision mediump float;
uniform vec4 u_color;
varying vec2 v_uv;
uniform sampler2D u_s_texture;
void main()
{
	gl_FragColor = vec4(u_color.r, u_color.g, u_color.b, texture2D(u_s_texture, v_uv).a * u_color.a);
	//gl_FragColor = vec4(1,0,0,1);
}
