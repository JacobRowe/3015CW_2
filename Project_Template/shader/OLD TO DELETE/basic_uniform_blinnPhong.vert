#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

uniform struct LightInfo {
    vec4 Position;//light pos in eye
    vec3 La;//ambient light intensity
    vec3 Ld;//diffuse light thing
    vec3 L;//diffuse + spec light intensity
} lights[3];

uniform struct MaterialInfo {
    vec3 Ka;//ambient reflect
    vec3 Kd;//diffuse reflect
    vec3 Ks;//spec reflect
    float Shine;//spec shine
} Material;

out vec3 Colour;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

void getCamSpaceValues(out vec3 n, out vec4 eye)
{
    n = normalize(NormalMatrix * VertexNormal);
    eye = vec4(VertexPosition, 1.0f) * ModelViewMatrix;

}

vec3 blinnPhongModel(int light, vec3 Position, vec3 n)
{
    //ambient
    vec3 ambient = lights[light].La * Material.Ka;

    //diffuse
    //vec4 eye = vec4(VertexPosition, 1.0f) * ModelViewMatrix;
    vec3 s = normalize(lights[light].Position.xyz - Position);
    float snDot = max(dot(s,n), 0.0);
    vec3 diffuse = Material.Kd * lights[light].Ld * snDot;

    //specular
    vec3 spec = vec3(0.0);
    if(snDot > 0.0)
    {
        vec3 v = normalize(-Position.xyz);
        //vec3 r = reflect( -s, n );
        vec3 h = normalize(v + s);
        spec = Material.Ks * pow( max( dot(h,n), 0.0 ), Material.Shine );

    }

    return ambient + lights[light].L * (diffuse + spec);

}

void main()
{
    
    vec3 n = normalize(NormalMatrix * VertexNormal);
    vec4 eye = vec4(VertexPosition, 1.0f) * ModelViewMatrix;
    
    //Colour = vec3(0.0f);
    for(int i = 0; i < 3; i++)
    {
        Colour += blinnPhongModel(i, eye.xyz, n);
    }
    
   
    
    gl_Position = MVP * vec4(VertexPosition,1.0);
}
