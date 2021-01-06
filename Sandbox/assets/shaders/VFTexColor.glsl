#shader vertex
#version 330 core

layout (location = 0) in vec4 a_Pos;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexCoord;

out vec4 v_Color;
out vec2 v_TexCoord;
uniform mat4 u_VP;
uniform mat4 u_Transform;

void main()
{
	gl_Position = u_VP * u_Transform * a_Pos;
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
}
		
#shader fragment
#version 330 core

layout (location = 0) out vec4 color;
in vec4 v_Color;
in vec2 v_TexCoord;
uniform sampler2D u_TexSlot;
uniform vec4 u_Color;

void main()
{
	color = texture(u_TexSlot, v_TexCoord) * v_Color * u_Color;
}
