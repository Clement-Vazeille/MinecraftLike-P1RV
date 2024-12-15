#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 transformation;
uniform mat4 translation;
uniform mat4 projection;

void main()
{
	gl_Position =  translation * projection * transformation * vec4(aPos, 1.0f);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}