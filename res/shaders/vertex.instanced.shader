#version 430 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 texUv;
layout (location = 2) in vec4 inColor;
layout(location = 3) in mat4 instanceMatrix;

out vec2 uv;
out vec4 color;

uniform mat4 VP;

void main() {
    gl_Position = VP * instanceMatrix * vec4(inPos, 1);
    uv = vec2(texUv.x, texUv.y);
    color = inColor;
}
