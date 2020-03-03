#version 430 core

in vec2 uv;

out vec3 color;

layout(binding=0) uniform sampler2D tex;

void main() {
    color = texture(tex, uv).rgb;
}
