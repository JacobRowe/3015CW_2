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

uniform struct LineInfo {
    float Width;
    vec4 Color;
} Line;

in vec3 GNormal;
in vec3 GPosition;
noperspective in vec3 GEdgeDistance;

layout (location = 0) out vec4 FragColor;

vec3 phongModel(vec3 Position, vec3 Normal)
{
    //ambient
    vec3 ambient = Light.Intensity * Material.Ka;

    //diffuse
    //vec4 eye = vec4(VertexPosition, 1.0f) * ModelViewMatrix;
    vec3 s = normalize(Light.Position.xyz - Position);
    float snDot = max(dot(s,Normal), 0.0);
    vec3 diffuse = Material.Kd * Light.Intensity * snDot;

    //specular
    vec3 spec = vec3(0.0);
    if(snDot > 0.0)
    {
        vec3 v = normalize(-Position.xyz);
        vec3 r = reflect( -s, Normal );

       spec = Material.Ks * pow( max( dot(r,v), 0.0 ), Material.Shine );

    }

    return ambient + diffuse + spec;

}



void main()
{
    vec4 color = vec4( phongModel(GPosition, GNormal), 1.0);

    float d = min(GEdgeDistance.x, GEdgeDistance.y);
    d = min(d, GEdgeDistance.z);

    float mixVal;
    if (d < Line.Width - 1)
    {
        mixVal = 1.0;

    }
    else if (d > Line.Width + 1)
    {
        mixVal = 0.0;
    }
    else
    {
        float x = d - (Line.Width - 1);
        mixVal = exp2(-2.0 * (x*x));
    }

    FragColor = 
    mix(color, Line.Color, mixVal);
}
