#version 430
in vec3 Position;
in vec3 Normal;
in vec2 TexChoord;

layout( location = 0 ) out vec4 FragColor; 
//layout(binding=0) uniform sampler2D Tex1;



uniform struct LightInfo {
    vec4 Position;//light pos in eye
    vec3 La;//ambient light intensity
    vec3 Ld;//diffuse light thing
    vec3 L;//spec light intensity
} Light;

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
    n = normalize(NormalMatrix * Normal);
    eye = vec4(Position, 1.0f) * ModelViewMatrix;

}

vec3 blinnPhongModel(int light, vec3 Position, vec3 n)
{
   
    

    //ambient
    vec3 ambient = Light.La * Material.Ka;

    //diffuse
    //vec4 eye = vec4(VertexPosition, 1.0f) * ModelViewMatrix;
    vec3 s = normalize(Light.Position.xyz - Position);
    float snDot = max(dot(s,n), 0.0);
    vec3 diffuse = Material.Kd * Light.Ld * snDot;

    //specular
    vec3 spec = vec3(0.0);
    if(snDot > 0.0)
    {
        vec3 v = normalize(-Position.xyz);
        vec3 r = reflect( -s, n );

       spec = Material.Ks * pow( max( dot(r,v), 0.0 ), Material.Shine );

    }

    return ambient + Light.L * (diffuse + spec);

}

void main()
{
    
    vec3 n = normalize(NormalMatrix * Normal);
    vec4 eye = vec4(Position, 1.0f) * ModelViewMatrix;
    
    //Colour = vec3(0.0f);
    
    
    for(int i = 0; i < 3; i++)
    {
        Colour += blinnPhongModel(i, Position, Normal);
    }
    
   
    
    //gl_Position = MVP * vec4(VertexPosition,1.0);
}