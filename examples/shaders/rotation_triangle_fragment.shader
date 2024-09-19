#version 330 core

in vec3 outVertexColor;
out vec4 FragColor;

void main() {
    FragColor = vec4(outVertexColor, 1.0f);
}
