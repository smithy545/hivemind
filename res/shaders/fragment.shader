#version 430 core

in vec2 uv;

out vec4 fragColor;

layout(binding=0) uniform sampler2D tex;

void main() {
    fragColor = texture(tex, uv).rgba;
}
