#version 330 core
out vec4 FragColor;

in vec2 texCord;

uniform sampler2D textureSample;

void main()
{

    // vec3 result = (ambient + diffuse) * vec3(texture(textureSample, texCord));

    FragColor = texture(textureSample, texCord);
}