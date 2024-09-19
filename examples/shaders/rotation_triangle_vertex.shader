#version 330 core

layout(location = 0) in vec3 inVertexPos;
layout(location = 1) in vec3 inColorPos;

uniform mat4 mvp;

out vec3 outVertexColor;

void main()
{
    gl_Position = mvp * vec4(inVertexPos, 1.0);
    outVertexColor = inColorPos;
}
