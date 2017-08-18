precision mediump float;
uniform sampler2D u_texture;
uniform float u_fadeRatio;
varying vec2 v_uv;
void main()
{
	//gl_FragColor = vec4(0.3, 0.5, 0.7, 1.0);
    //gl_FragColor = v_color;
    gl_FragColor = texture2D(u_texture, v_uv);
	//gl_FragColor.w *= 1.0 - u_fadeRatio;
	if (gl_FragColor.w > 0.0)
	{
		vec4 color = vec4(0.0, 0.0, 0.0, 1.0);
		gl_FragColor = mix(gl_FragColor, color, u_fadeRatio);
	}
}
