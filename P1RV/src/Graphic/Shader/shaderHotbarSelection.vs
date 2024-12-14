#version 330 core
layout (location = 0) in vec2 aPos;

uniform mat4 translation;

void main()
{
	gl_Position =  translation * vec4(aPos.x,aPos.y,-0.01f,1.0f);
}