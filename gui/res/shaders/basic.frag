#version 120

uniform sampler2D fTexture0;

varying vec4 fColor;
varying vec3 fNormal;
varying vec2 fUv;

void main(void)
{
	gl_FragColor = texture2D(fTexture0, fUv);
}
