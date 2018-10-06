#version 330 core

in vec3 vertColor;
in vec2 texCord;

out vec4 color;

uniform sampler2D texture2D_1;
uniform sampler2D texture2D_2;
uniform float time;
uniform float mixThreshold;

void main(){
	color = mix(texture(texture2D_1 , texCord), texture(texture2D_2 , texCord) , 0.5f);
}