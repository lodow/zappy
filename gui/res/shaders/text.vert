#version 120

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform sampler2D fTexture0;

attribute vec4 vPosition;
attribute vec2 vTexCoord;

varying vec2 fUv;

void main(void)
{
    fUv = vTexCoord;
    
    gl_Position = projection * view * model * vPosition;
}
