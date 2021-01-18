#shader vertex
#version 330 core

layout (location = 0) in vec4 a_Pos;
layout (location = 1) in vec4 a_Color;

out vec4 v_Color;

uniform mat4 u_VP;
uniform mat4 u_Transform;

void main()
{
    gl_Position = u_VP * u_Transform * a_Pos;
    v_Color = a_Color;
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 color;
in vec4 v_Color;
uniform vec4 u_Color;

void main()
{
    color = v_Color * u_Color;
}