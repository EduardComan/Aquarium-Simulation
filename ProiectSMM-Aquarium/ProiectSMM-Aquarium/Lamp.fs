#version 330 core
out vec4 FragColor;

uniform sampler2D texture_diffuse1;
in vec2 texCoords;

void main()
{ 
    FragColor = texture(texture_diffuse1, texCoords);
}