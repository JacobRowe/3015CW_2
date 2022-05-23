#version 430

uniform struct LightInfo {
	vec4 Position;
	vec3 Intensity;
} Light;

uniform struct MaterialInfo {
    vec3 Ka;//ambient reflect
    vec3 Kd;//diffuse reflect
    vec3 Ks;//spec reflect
    float Shine;//spec shine
} Material;

uniform vec4 lineColor;

in vec3 GNormal;
in vec3 GPosition;
in vec2 TexCoord;

flat in int GIsEdge;

layout (location = 0) out vec4 FragColor;

layout( binding = 0 ) uniform sampler2D Tex1;
vec3 tex;


//toon 
const int levels = 4;
const float scaleFactor = 1.0f /levels;


vec3 toonShade()
{

    vec3 s = normalize(Light.Position.xyz - GPosition.xyz);
    vec3 ambient = Material.Ka;
    float cosine = dot(s, GNormal);
    vec3 diffuse = Material.Kd * ceil(cosine * levels)  * scaleFactor;

    

    return  Light.Intensity * (diffuse + ambient);
    
 
}

vec3 phongModel()
{
    //ambient
    vec3 ambient = Light.Intensity * Material.Ka * tex;

    //diffuse
    vec3 s = normalize(Light.Position.xyz - GPosition);
    float snDot = max(dot(s,GNormal), 0.0);
    vec3 diffuse = Material.Kd * (floor(snDot * levels) * scaleFactor) * tex * Light.Intensity;

    return ambient + diffuse;

}



void main()
{
//can do more with this descion making, diff shader
    if (GIsEdge == 1)
    {
        FragColor = lineColor;
    }
    else
    {
        tex = texture(Tex1, TexCoord).rgb;
        FragColor = vec4(toonShade(), 1.0);
    }
}