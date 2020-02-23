#version 430 core

layout (location = 0) in vec2 aPos;

uniform float width;
uniform float height;
uniform double mouseX;
uniform double mouseY;

out vec2 mousePos;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
    mousePos = vec2(mouseX/800.0, mouseY/600.0);
}
