#version 330 core

in vec2 position;

uniform vec2 scale;

void main()
{
	gl_Position = vec4(position.x * scale.x, position.y * scale.y, 0.0, 1.0);
}