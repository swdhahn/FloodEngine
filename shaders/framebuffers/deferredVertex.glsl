#version 450 core

layout(location = 0) in vec3 positions;
layout(location = 1) in vec3 textureCoords;

layout(location = 0) out vec2 ftextureCoords;

void main() {

    ftextureCoords = textureCoords.xy;
    gl_Position = vec4(positions.xy, 0.0, 1.0);

}