#version 430 core

in vec2 mousePos;

out vec4 FragColor;

void main() {
    FragColor = vec4(mousePos.xy, 1.0f, 1.0f);
}
