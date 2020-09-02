#version 330 core
out vec4 FragColor;

in vec2 texCord;
uniform sampler2D textureSample;

void main()
{
    FragColor = texture(textureSample, texCord);
}