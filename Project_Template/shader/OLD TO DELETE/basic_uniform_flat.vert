#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

flat out vec3 LightIntensity;

uniform mat4 RotationMatrix;
uniform vec4 LightPosition;


uniform vec3 Kd;
uniform vec3 Ld;

uniform vec3 Ks;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

void getCamSpaceValues(out vec3 n, out vec4 eye)
{
    n = normalize(NormalMatrix * VertexNormal);
    eye = vec4(VertexPosition, 1.0f) * ModelViewMatrix;

}



void main()
{
    vec3 camN;
    vec4 camEye;

    getCamSpaceValues(camN, camEye);

    vec3 n = normalize(NormalMatrix * VertexNormal);
    vec4 eye = vec4(VertexPosition, 1.0f) * ModelViewMatrix;
    vec3 s = normalize(vec3(LightPosition - eye));
    

    float snDot = max(dot(s,camN), 0.0);
    

    
    vec3 specular = vec3(0.0);

    if(snDot > 0.0)
    {
        vec3 r = -s + (2*snDot) * camN;
        float rvDot = pow(max(dot(r, vec3(-camEye)), 0.0), 10.0f);
        specular = Ks * Ld * rvDot;
    }

    vec3 ambient = Kd * Ld;
    vec3 diffuse = Kd * Ld * snDot;
    LightIntensity = ambient + diffuse + specular;
    
    gl_Position = MVP * vec4(VertexPosition,1.0);
}
