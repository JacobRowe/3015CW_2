#version 430
in vec3 LightDir;
in vec2 TexCoord;
in vec3 ViewDir;


layout( location = 0 ) out vec4 FragColor; 
//layout(binding=0) uniform sampler2D Tex1;

layout(binding=0) uniform sampler2D ColorTex;
layout(binding=1) uniform sampler2D NormalMapTex;

uniform struct LightInfo {
    vec4 Position;//light pos in eye
    vec3 La;//ambient light intensity
    vec3 Ld;//diffuse light thing
    vec3 L;//diffuse + spec light intensity
} Light;


uniform struct MaterialInfo {
    vec3 Ka;//ambient reflect
    vec3 Kd;//diffuse reflect
    vec3 Ks;//spec reflect
    float Shine;//spec shine
} Material;



out vec3 FragColour;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

void getCamSpaceValues(out vec3 n, out vec4 eye)
{
    //n = normalize(NormalMatrix * Normal);
    //eye = vec4(Position, 1.0f) * ModelViewMatrix;

}

vec3 blinnPhongModel(int light, vec3 Position, vec3 n)
{
    vec3 texColor = texture(ColorTex, TexCoord).rgb;
    //ambient
    vec3 ambient = Light.La * texColor;

    //diffuse
    //vec4 eye = vec4(VertexPosition, 1.0f) * ModelViewMatrix;
    vec3 s = normalize(LightDir);
    float snDot = max(dot(s,n), 0.0);
    vec3 diffuse = texColor * Light.Ld * snDot;

    //specular
    vec3 spec = vec3(0.0);
    if(snDot > 0.0)
    {
        vec3 v = ViewDir;
        vec3 r = reflect( -s, n );

       spec = Material.Ks * pow( max( dot(r,v), 0.0 ), Material.Shine );

    }

    return ambient + Light.L * (diffuse + spec);

}

void main()
{
    //Colour = vec3(0.0f);
    vec3 norm = texture(NormalMapTex, TexCoord).xyz;
    norm.xy = 2.0f * norm.xy - 1.0;
    FragColor = vec4(blinnPhongModel(1, vec3(Light.Position), norm), 0);
    
    
   
    
    //gl_Position = MVP * vec4(VertexPosition,1.0);
}
