precision mediump float;
uniform sampler2D u_texture;
varying vec2 v_uv;
varying vec4 v_color;
void main()
{
	//gl_FragColor = vec4(0.3, 0.5, 0.7, 1.0);
    //gl_FragColor = v_color;
    gl_FragColor = texture2D(u_texture, v_uv);
}
