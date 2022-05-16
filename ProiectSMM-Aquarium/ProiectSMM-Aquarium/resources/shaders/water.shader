#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 tex_coord;
layout(location = 2) in vec3 normals;

out vec4 clip_space;
out vec2 v_tex_coord;
out vec3 v_normals;
out vec3 current_position;

uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ModelMatrix;
uniform vec4 u_ClipPlane;//defining clip plane

const float tiling = 5.0f;

void main()
{
	//calculating the position of the object
	current_position = vec3(u_ModelMatrix * vec4(position, 1.0f));

	//needed for water reflection and refraction
	gl_ClipDistance[0] = dot(vec4(current_position, 1.0f), u_ClipPlane);

	//projection
	clip_space = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(position, 1.0);
	gl_Position = clip_space;

	//for texture
	v_tex_coord = tex_coord * tiling;

	v_normals = normals;
};



#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 clip_space;
in vec2 v_tex_coord;
in vec3 v_normals;
in vec3 current_position;

uniform vec4 u_LightColor;
uniform vec3 u_LightPosition;
uniform vec3 u_CamPosition;

uniform sampler2D u_ReflectionTexture;
uniform sampler2D u_RefractionTexture;
uniform sampler2D u_DuDvMap;
uniform sampler2D u_NormalMap;
uniform sampler2D u_DepthMap;
uniform float u_WaveMoveFactor;
uniform float u_ZNear;
uniform float u_ZFar;
uniform int u_isSurface;

const float wave_strenght = 0.01;

void main()
{
	if (u_isSurface == 1)
	{
		//for realistic water reflection
		vec2 normalized_device_space = (clip_space.xy / clip_space.w) / 2.0f + 0.5f;
		vec2 refraction_tex_coords = vec2(normalized_device_space.x, normalized_device_space.y);
		vec2 reflection_tex_coords = vec2(normalized_device_space.x, -normalized_device_space.y);

		//depth effect
		float depth = texture(u_DepthMap, refraction_tex_coords).r;//getting depth value from refraction depth buffer
		float floor_distance_from_camera = 2.0f * u_ZNear * u_ZFar / (u_ZFar + u_ZNear - (2.0f * depth - 1.0f) * (u_ZFar - u_ZNear));

		depth = gl_FragCoord.z;
		float water_distance_from_camera = 2.0f * u_ZNear * u_ZFar / (u_ZFar + u_ZNear - (2.0f * depth - 1.0f) * (u_ZFar - u_ZNear));

		float water_depth = floor_distance_from_camera - water_distance_from_camera;

		//waves using dudv map
		vec2 distorted_tex_coords = texture(u_DuDvMap, vec2(v_tex_coord.x + u_WaveMoveFactor, v_tex_coord.y)).rg * 0.1f;
		distorted_tex_coords = v_tex_coord + vec2(distorted_tex_coords.x, distorted_tex_coords.y + u_WaveMoveFactor);
		vec2 total_distortion = (texture(u_DuDvMap, distorted_tex_coords).rg * 2.0f - 1.0f) * wave_strenght;

		refraction_tex_coords += total_distortion;
		refraction_tex_coords = clamp(refraction_tex_coords, 0.001, 0.999);

		reflection_tex_coords += total_distortion;
		reflection_tex_coords.x = clamp(reflection_tex_coords.x, 0.001, 0.999);
		reflection_tex_coords.y = clamp(reflection_tex_coords.y, -0.999, -0.001);

		//texture
		vec4 reflection_color = texture(u_ReflectionTexture, reflection_tex_coords);
		vec4 refraction_color = texture(u_RefractionTexture, refraction_tex_coords);

		//normal mapping
		vec4 normal_map_color = texture(u_NormalMap, distorted_tex_coords);
		vec3 normal = vec3(normal_map_color.r * 2.0f - 1.0f, normal_map_color.b * 4.0f, normal_map_color.g * 2.0f - 1.0f);
		normal = normalize(normal);

		//Fresnel effect
		vec3 to_camera_vec = u_CamPosition - current_position;
		float refractive_factor = dot(normalize(to_camera_vec), normal);
		refractive_factor = pow(refractive_factor, 2.0);//determining how reflective the water surface is

		//ambiental light
		float ambient = 0.7f;

		//diffuse light
		vec3 light_direction = normalize(u_LightPosition - current_position);
		float diffuse = max(dot(normal, light_direction), 0.0f);

		//specular light
		float specular_light = 0.5f;
		vec3 view_direction = normalize(u_CamPosition - current_position);
		vec3 reflection_direction = reflect(-light_direction, normal);
		float spec_amount = pow(max(dot(view_direction, reflection_direction), 0.0f), 32);
		float specular = spec_amount * specular_light;

		color = mix(reflection_color, refraction_color, refractive_factor);//texturing the water using the reflection and refraction textures
		color = mix(color, vec4(0.0f, 0.3f, 0.5f, 1.0f), 0.2f);//giving a blueish color to the water
		color = color * u_LightColor * (ambient + diffuse + specular);
		color.a = clamp(water_depth / 5.0f, 0.0f, 1.0f);
	}
	else
	{
		color = vec4(0.0f, 0.3f, 0.5f, 0.5f);
	}
};