#version 460 core

layout(location = 0) in vec3 in_Positions;
layout(location = 1) in vec3 in_Normals;
layout(location = 2) in vec3 in_TextureCoords;

layout(location = 0) out vec3 frag_Normal;
layout(location = 1) out vec2 frag_TextureCoords;
layout(location = 2) out vec3 frag_Position;
layout(location = 3) out vec3 frag_WorldPos;

uniform mat4 projectionMatrix;
uniform mat4 transformationMatrix;
uniform mat4 cameraMatrix;

void main() {

    vec4 worldPos = transformationMatrix * vec4(in_Positions, 1.0);
    vec4 worldCameraPosition = cameraMatrix * worldPos;

    gl_Position = projectionMatrix * worldCameraPosition;
    frag_Normal = in_Normals;
    frag_TextureCoords = in_TextureCoords.xy;
    frag_Position = worldCameraPosition.xyz;
    frag_WorldPos = worldPos.xyz;
}