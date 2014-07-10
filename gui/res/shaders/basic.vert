#version 120

uniform	mat4 projection;
uniform	mat4 view;
uniform	mat4 model;
uniform	mat3 modelNormal;

attribute vec4 vPosition;
attribute vec4 vColor;
attribute vec3 vNormal;
attribute vec2 vTexCoord;

varying vec4 fColor;
varying vec3 fNormal;
varying vec2 fUv;

void main(void)
{
  fColor = vColor;
  fNormal = modelNormal * vNormal;
  fUv = vTexCoord;
  gl_Position = projection * view * model * vPosition;
}