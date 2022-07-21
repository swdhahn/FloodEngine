#version 460 core

layout(location = 0) in vec3 frag_Normal;
layout(location = 1) in vec2 frag_TextureCoords;
layout(location = 2) in vec3 frag_Position;
layout(location = 3) in vec3 frag_WorldPos;

layout(location = 0) out vec4 out_Albedo;
layout(location = 1) out vec4 out_Normal;
layout(location = 2) out vec4 out_Position;

uniform sampler2D m_albedoTexture;

void main() {

    vec3 xTangent = dFdx(frag_WorldPos);
    vec3 yTangent = dFdy(frag_WorldPos);
    vec3 faceNormal = normalize( cross( xTangent, yTangent ) );

    out_Albedo = texture(m_albedoTexture, frag_TextureCoords);
    out_Normal = vec4(faceNormal, 1.0);
    out_Position = vec4(frag_Position, 1.0);

}
