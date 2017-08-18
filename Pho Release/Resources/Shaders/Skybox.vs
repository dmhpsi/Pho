attribute vec4 a_CubeVertexPos;
uniform mat4 u_WVP;
varying vec4 v_pos;
void main(void)
{
	gl_Position = u_WVP * a_CubeVertexPos;
	//gl_Position = a_CubeVertexPos;
	v_pos = a_CubeVertexPos;
}