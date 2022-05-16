#shader vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 tex_coord;
layout(location = 2) in vec3 normals;

out vec2 v_tex_coord;
out vec3 v_normals;
out vec3 current_position;

uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ModelMatrix;

void main()
{
	//calculating the position of the object
	current_position = vec3(u_ModelMatrix * vec4(position, 1.0f));

	//projection
	gl_Position = u_ProjectionMatrix * u_ViewMatrix * vec4(current_position, 1.0);

	//for texture
	v_tex_coord = tex_coord;

	v_normals = normals;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_tex_coord;
in vec3 v_normals;
in vec3 current_position;

uniform sampler2D u_DepthMap;

float near = 60.1f;
float far = 90.0f;

float linearize(float depth)
{
	return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}

void main()
{
	color = vec4(vec3(linearize(texture(u_DepthMap, v_tex_coord).r) / far), 1.0f);
}