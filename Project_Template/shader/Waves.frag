#version 430
in vec4 Position;
in vec3 Normal;
in vec2 TexCoord;

layout( location = 0 ) out vec4 FragColor; 

uniform struct LightInfo {
    vec4 Position;//light pos in eye
    vec3 La; //ambient light Intensity
    vec3 L; //diffuse and spec light Intensity
} Light;

uniform struct MaterialInfo {
    vec3 Ka;//ambient reflect
    vec3 Kd;//diffuse reflect
    vec3 Ks;//spec reflect
    float Shine;//spec shine
} Material;


uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

layout( binding=1 ) uniform sampler2D waterTex;
vec3 curTex;


vec3 phongModel()
{
    //ambient
    vec3 ambient = curTex * Light.La * Material.Ka ;

    //diffuse
    //vec4 eye = vec4(VertexPosition, 1.0f) * ModelViewMatrix;
    vec3 s = normalize(Light.Position.xyz - vec3(Position));
    float snDot = max(dot(s,Normal), 0.0);
    vec3 diffuse = Material.Kd * Light.L * snDot;

    //specular
    vec3 spec = vec3(0.0);
    
    vec3 v = normalize(-Position.xyz);
    vec3 r = reflect( -s, Normal );

    spec = Material.Ks * pow( max( dot(r,v), 0.0 ), Material.Shine );

    

    
    return Light.L + ambient + diffuse;// + curTex;

}

void main()
{
    

    

    curTex = texture(waterTex, TexCoord).rgb;
    FragColor = vec4(phongModel(), 1.0f);
    
   
    
    //gl_Position = MVP * vec4(VertexPosition,1.0);
}
