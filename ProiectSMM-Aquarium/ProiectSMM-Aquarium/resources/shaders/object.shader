#shader vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 tex_coord;
layout(location = 2) in vec3 normals;

out vec3 current_position;
out vec3 v_normals;
out vec2 v_tex_coord;
out vec4 current_positionLightSpace;

uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ModelMatrix;
uniform mat4 u_LightProjection;
uniform vec4 u_ClipPlane;//defining clip plane

void main()
{
    current_position = vec3(u_ModelMatrix * vec4(position, 1.0));
    v_normals = transpose(inverse(mat3(u_ModelMatrix))) * normals;
    v_tex_coord = tex_coord;
    current_positionLightSpace = u_LightProjection * vec4(current_position, 1.0);
    gl_Position = u_ProjectionMatrix * u_ViewMatrix * vec4(current_position, 1.0);
    gl_ClipDistance[0] = dot(vec4(current_position, 1.0f), u_ClipPlane);
}


#shader fragment
#version 330 core
layout(location = 0) out vec4 color;

in vec3 current_position;
in vec3 v_normals;
in vec2 v_tex_coord;
in vec4 current_positionLightSpace;

uniform sampler2D u_Texture;
uniform sampler2D shadowMap;

uniform vec3 u_LightPosition;
uniform vec3 u_CamPosition;

float ShadowCalculation(vec4 current_positionLightSpace)
{
    // perform perspective divide
    vec3 projCoords = current_positionLightSpace.xyz / current_positionLightSpace.w;

    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;

    // get closest depth value from light's perspective (using [0,1] range current_positionLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r;

    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;

    // calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(v_normals);

    vec3 lightDir = normalize(u_LightPosition - current_position);

    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    //float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    
    float shadow = 0.0;
    vec2 texelSize = 1.2 / textureSize(shadowMap, 0);
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;
    

    if (projCoords.z > 1.0)
        shadow = 0.0;

    return shadow;
}

void main()
{
    vec4 lightColor = vec4(1.0f);

    //ambiental light
    float ambient = 0.2f;

    //diffuse light
    vec3 normal = normalize(v_normals);
    vec3 light_direction = normalize(u_LightPosition - current_position);
    float diffuse = max(dot(normal, light_direction), 0.0f);

    //specular light
    float specular_light = 0.5f;
    vec3 view_direction = normalize(u_CamPosition - current_position);
    vec3 reflection_direction = reflect(-light_direction, normal);
    float spec_amount = pow(max(dot(view_direction, reflection_direction), 0.0f), 32);
    float specular = spec_amount * specular_light;

    //texture
    vec4 tex_color = texture(u_Texture, v_tex_coord);

    // calculate shadow
    float shadow = ShadowCalculation(current_positionLightSpace);

    color = tex_color * lightColor * (ambient + (1.0f - shadow) * (diffuse + specular));
    color.a = 1.0f;
}