#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 MVP;
uniform vec3 COLOR_VS;

out vec3 COLOR_FS;

void main(){
	gl_Position = MVP * vec4(vertexPosition_modelspace,1);
	COLOR_FS = COLOR_VS;
}
