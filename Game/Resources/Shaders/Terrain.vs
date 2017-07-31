attribute vec4 a_posL;
attribute vec2 a_uv;
uniform mat4 u_WVP;
varying vec2 v_uv;
attribute vec4 a_color;
varying vec4 v_color;

void main()
{
	gl_Position = u_WVP*a_posL;
	//gl_Position.y = 0.0;
	v_uv = a_uv;
	v_color = a_color;
}
   