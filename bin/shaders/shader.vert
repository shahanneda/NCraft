#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCord;
layout (location = 2) in vec3 aNormal;

out vec2 texCord;
out vec3 normal;
out vec3 vertexWorldPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    texCord = aTexCord;
    normal = aNormal;
    vertexWorldPos = vec3(model * vec4(aPos, 1.0));
}