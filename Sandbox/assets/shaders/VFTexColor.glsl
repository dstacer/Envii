#shader vertex
#version 330 core

layout (location = 0) in vec4 a_Pos;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexCoord;
layout (location = 3) in float a_TexSlot;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexSlot;

uniform mat4 u_VP;
uniform mat4 u_Transform;

void main()
{
	gl_Position = u_VP * u_Transform * a_Pos;
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexSlot = a_TexSlot;
}
		
#shader fragment
#version 330 core

layout (location = 0) out vec4 color;
in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexSlot;

uniform sampler2D u_TexSlot[32];
uniform float u_TexCoordScale;

void main()
{
	vec4 texColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	int texSlot = int(v_TexSlot);
	switch (texSlot)
	{
	case 0:
		texColor = texture(u_TexSlot[0], v_TexCoord * u_TexCoordScale);
		break;
	case 1:
		texColor = texture(u_TexSlot[1], v_TexCoord * u_TexCoordScale);
		break;
	case 2:
		texColor = texture(u_TexSlot[2], v_TexCoord * u_TexCoordScale);
		break;
	case 3:
		texColor = texture(u_TexSlot[3], v_TexCoord * u_TexCoordScale);
		break;
	case 4:
		texColor = texture(u_TexSlot[4], v_TexCoord * u_TexCoordScale);
		break;
	case 5:
		texColor = texture(u_TexSlot[5], v_TexCoord * u_TexCoordScale);
		break;
	case 6:
		texColor = texture(u_TexSlot[6], v_TexCoord * u_TexCoordScale);
		break;
	case 7:
		texColor = texture(u_TexSlot[7], v_TexCoord * u_TexCoordScale);
		break;
	case 8:
		texColor = texture(u_TexSlot[8], v_TexCoord * u_TexCoordScale);
		break;
	case 9:
		texColor = texture(u_TexSlot[9], v_TexCoord * u_TexCoordScale);
		break;
	case 10:
		texColor = texture(u_TexSlot[10], v_TexCoord * u_TexCoordScale);
		break;
	case 11:
		texColor = texture(u_TexSlot[11], v_TexCoord * u_TexCoordScale);
		break;
	case 12:
		texColor = texture(u_TexSlot[12], v_TexCoord * u_TexCoordScale);
		break;
	case 13:
		texColor = texture(u_TexSlot[13], v_TexCoord * u_TexCoordScale);
		break;
	case 14:
		texColor = texture(u_TexSlot[14], v_TexCoord * u_TexCoordScale);
		break;
	case 15:
		texColor = texture(u_TexSlot[15], v_TexCoord * u_TexCoordScale);
		break;
	case 16:
		texColor = texture(u_TexSlot[16], v_TexCoord * u_TexCoordScale);
		break;
	case 17:
		texColor = texture(u_TexSlot[17], v_TexCoord * u_TexCoordScale);
		break;
	case 18:
		texColor = texture(u_TexSlot[18], v_TexCoord * u_TexCoordScale);
		break;
	case 19:
		texColor = texture(u_TexSlot[19], v_TexCoord * u_TexCoordScale);
		break;
	case 20:
		texColor = texture(u_TexSlot[20], v_TexCoord * u_TexCoordScale);
		break;
	case 21:
		texColor = texture(u_TexSlot[21], v_TexCoord * u_TexCoordScale);
		break;
	case 22:
		texColor = texture(u_TexSlot[22], v_TexCoord * u_TexCoordScale);
		break;
	case 23:
		texColor = texture(u_TexSlot[23], v_TexCoord * u_TexCoordScale);
		break;
	case 24:
		texColor = texture(u_TexSlot[24], v_TexCoord * u_TexCoordScale);
		break;
	case 25:
		texColor = texture(u_TexSlot[25], v_TexCoord * u_TexCoordScale);
		break;
	case 26:
		texColor = texture(u_TexSlot[26], v_TexCoord * u_TexCoordScale);
		break;
	case 27:
		texColor = texture(u_TexSlot[27], v_TexCoord * u_TexCoordScale);
		break;
	case 28:
		texColor = texture(u_TexSlot[28], v_TexCoord * u_TexCoordScale);
		break;
	case 29:
		texColor = texture(u_TexSlot[29], v_TexCoord * u_TexCoordScale);
		break;
	case 30:
		texColor = texture(u_TexSlot[30], v_TexCoord * u_TexCoordScale);
		break;
	case 31:
		texColor = texture(u_TexSlot[31], v_TexCoord * u_TexCoordScale);
		break;
	}
	color = texColor * v_Color;
}
