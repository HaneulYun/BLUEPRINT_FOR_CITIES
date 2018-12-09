#version 330 core

out vec3 color;

in vec3 COLOR_FS;

void main(){
	color = COLOR_FS;
}