#shader vertex
#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_Mvp;
out vec2 v_TexCoord;

void main()
{
	v_TexCoord = a_TexCoord;
	gl_Position = u_Mvp * vec4(position, 1.0);
};

#shader fragment
#version 450 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
	color = texture(u_Texture, v_TexCoord);
};