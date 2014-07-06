#version 120

uniform vec4 fColor;
uniform sampler2D fTexture0;

varying vec2 fUv;

void main(void)
{
	gl_FragColor = texture2D(fTexture0, fUv) * fColor;
}
