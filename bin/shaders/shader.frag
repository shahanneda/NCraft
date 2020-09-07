#version 330 core
out vec4 FragColor;

in vec2 texCord;
uniform vec3 lightColor;
uniform sampler2D textureSample;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    vec3 result = ambient * vec3(texture(textureSample, texCord));

    FragColor = vec4(result, 1.0) ;
}