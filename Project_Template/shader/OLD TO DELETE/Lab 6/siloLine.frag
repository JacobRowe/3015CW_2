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

flat in int GIsEdge;

layout (location = 0) out vec4 FragColor;

//toon 
const int levels = 3;
const float scaleFactor = 1.0f /levels;

//replace with a pbr combo meal
vec3 toonShade()
{
    vec3 s = normalize(Light.Position.xyz - GPosition.xyz);
    vec3 ambient = Light.Intensity * Material.Ka;
    float cosine = dot(s, GNormal);
    vec3 diffuse = Material.Kd * ceil(cosine * levels) * scaleFactor;

    return Light.Intensity * (ambient + diffuse);

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
        FragColor = vec4(toonShade(), 1.0);
    }
}
