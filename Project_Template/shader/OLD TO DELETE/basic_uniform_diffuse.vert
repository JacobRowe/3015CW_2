#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 LightIntensity;

uniform mat4 RotationMatrix;
uniform vec4 LightPosition;

uniform vec3 Kd;
uniform vec3 Ld;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

void main()
{
    vec3 n = normalize(NormalMatrix * VertexNormal);
    vec4 eye = vec4(VertexPosition, 1.0f) * ModelViewMatrix;

    vec3 s = normalize(vec3(LightPosition - eye));

    float snDot = max(dot(s,n), 0.0);
    vec3 diffuse = Kd * Ld * snDot;

    LightIntensity = diffuse;
    
    gl_Position = MVP * vec4(VertexPosition,1.0);
}