#version 330 core
layout (location = 0) in vec2 aPos;

uniform mat4 transformation;
uniform mat4 projection;

void main()
{
	gl_Position =  projection  * transformation * vec4(aPos.x,aPos.y,0,1.0f);
}