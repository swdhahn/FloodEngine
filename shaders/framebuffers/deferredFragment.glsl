#version 450 core

layout(location = 0) in vec2 textureCoords;

layout(location = 0) out vec4 out_color;

// Albedo Texture
uniform sampler2D texture0;
// Normal Texture
uniform sampler2D texture1;
// Position Texture
uniform sampler2D texture2;

layout (std140, binding = 1) uniform CameraData {
    mat4 projectionMatrix;
    mat4 viewMatrix;
    mat4 projectionViewMatrix;
    vec4 cameraLocation;
};

const int MaxLightsForEachEntity = 1024;
const float specularStrength = 0.85;

layout (std140, binding = 2) uniform LightData {
    vec4 lightPosition[MaxLightsForEachEntity];
    vec4 lightColor[MaxLightsForEachEntity];
    vec4 attenuation[MaxLightsForEachEntity];
    vec4 lightCount;
};

void main() {


    vec4 Albedo = texture(texture0, textureCoords);
    vec4 Normal = texture(texture1, textureCoords);
    vec4 FragPos = texture(texture2, textureCoords);
    float Specular = Albedo.a;

    vec3 unitNormal = normalize(Normal.xyz);
    float reflectivity = Normal.w;
    float shineDamper = FragPos.w;

    vec3 viewDir = normalize(cameraLocation.xyz - FragPos.xyz);

    vec3 totalDiffuse = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);

    for(int i = 0; i < lightCount.x; i++) {
        vec3 toLightVector = normalize(-lightPosition[i].xyz);
        float nDot1 = max(dot(unitNormal, toLightVector), 0.0);
        totalDiffuse += (nDot1 * lightColor[i].xyz);

        vec3 reflectDir = reflect(-toLightVector, Normal.xyz);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        totalSpecular += specularStrength * spec * lightColor[i].xyz;

    }

    totalDiffuse = max(totalDiffuse, 0.2);

    vec4 finalColor = vec4((totalDiffuse + totalSpecular) * Albedo.xyz, 1.0);

    out_color = finalColor;

}