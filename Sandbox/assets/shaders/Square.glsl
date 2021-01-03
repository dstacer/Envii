#shader vertex
#version 330 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_TexCoord;
out vec3 v_pos;
out vec2 v_TexCoord;
uniform mat4 u_VP;
uniform mat4 u_Transform;

void main()
{
	gl_Position = u_VP * u_Transform * vec4(a_Pos, 1.0);
	v_pos = a_Pos;
	v_TexCoord = a_TexCoord;
}

#shader fragment		
#version 330 core

layout (location = 0) out vec4 color;
in vec3 v_pos;
in vec2 v_TexCoord;
uniform sampler2D u_TexSlot;

void main()
{
	color = texture(u_TexSlot, v_TexCoord);//vec4(v_pos * 0.5 + 0.5, 1.0);
}
