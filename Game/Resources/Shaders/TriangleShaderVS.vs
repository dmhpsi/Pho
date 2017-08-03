attribute vec4 a_posL;
attribute vec2 a_uv;
uniform mat4 u_WVP;
varying vec2 v_uv;
attribute vec4 a_color;

void main()
{
	gl_Position = u_WVP*a_posL;
	v_uv = a_uv;

}
   