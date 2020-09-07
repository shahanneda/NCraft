#version 330 core
out vec4 FragColor;

in vec2 texCord;
in vec3 normal; 
in vec3 vertexWorldPos;

uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform sampler2D textureSample;

void main()
{
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(normal);
    vec3 lightDirection = normalize(lightPosition - vertexWorldPos); // direction to the light
    float diffuse = max(dot(norm, lightDirection), 0.0); // use dot product to get angle between norm and lighDir, and amke sure its bigger than zero since we dont want negative lighting

    vec3 result = (ambient + diffuse) * vec3(texture(textureSample, texCord));

    FragColor = vec4(result, 1.0) ;
}