precision mediump float;
uniform samplerCube u_samplerCubeMap;
varying vec4 v_pos;
void main(void)
{
    gl_FragColor = textureCube(u_samplerCubeMap, v_pos.xyz);
}