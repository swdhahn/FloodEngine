#version 450 core

layout(location = 0) in vec2 textureCoords;

layout(location = 0) out vec4 out_color;

uniform sampler2D tex;

void main() {

    out_color = vec4(texture(tex, textureCoords).rgb, 1.0);//vec3(textureCoords, 1.0) / 2.0, 1.0);

}