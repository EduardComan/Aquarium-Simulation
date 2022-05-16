#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 u_LightProjection;
uniform mat4 u_ModelMatrix;

void main()
{
	gl_Position = u_LightProjection * u_ModelMatrix * vec4(aPos, 1.0f);
}

#shader fragment
#version 330 core

void main()
{
}