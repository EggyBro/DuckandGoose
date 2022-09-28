#shader vertex
#version 450 core

layout(location = 0) in vec3 position;

uniform mat4 u_Mvp;

void main()
{
	gl_Position = u_Mvp * vec4(position, 1.0);
};

#shader fragment
#version 450 core

layout(location = 0) out vec4 color;


void main()
{
	color = vec4(0.5, 0.5, 0.5, 1.0);
};