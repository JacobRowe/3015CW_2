#version 430


layout( location = 0 ) out vec4 FragColor; 
layout( location = 1 ) in vec3 Position; 
layout( location = 2 ) in vec3 Normal; 

layout( binding=0 ) uniform sampler2D RenderTex;

uniform struct LightInfo {
    vec4 Position;//light pos in eye
    vec3 La;//ambient light intensity
    vec3 L;//diffuse + spec light intensity
} Light;


uniform struct MaterialInfo {
    vec3 Ka;//ambient reflect
    vec3 Kd;//diffuse reflect
    vec3 Ks;//spec reflect
    float Shine;//spec shine
} Material;

uniform float EdgeThreshold;
uniform int Pass;
const vec3 lum = vec3(0.2126, 0.7152, 0.0722);

const int levels = 4;
const float scale = 4.0f/levels;

vec3 blinnPhongModel(vec3 Position, vec3 Normal)
{
    
    //ambient
    vec3 ambient = Light.La * Material.Ka;
    
    //diffuse
    vec3 s = normalize(Light.Position.xyz - Position);
    float snDot = max(dot(s,Normal), 0.0);
    vec3 diffuse = Material.Kd * Light.L * snDot;

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

vec3 toonShade(vec3 Position, vec3 Normal)
{
    
    //ambient
    vec3 ambient = Light.La * Material.Ka;

    //diffuse
    //vec4 eye = vec4(VertexPosition, 1.0f) * ModelViewMatrix;
    vec3 s = normalize(Light.Position.xyz - Position);
    float snDot = max(dot(s,Normal), 0.0);
    vec3 diffuse = Material.Kd * floor(snDot * levels) * scale;

    //specular
    vec3 spec = vec3(0.0);
    if(snDot > 0)
    {
        vec3 v = normalize(-Position.xyz);
        vec3 r = reflect( -s, Normal );

       spec = Material.Ks * pow( max( dot(r,v), 0.0 ), Material.Shine );

    }

    return (diffuse + spec);

}

float luminance( vec3 color )
{
 return dot(lum,color);
}

vec4 pass1()
{
    return vec4(blinnPhongModel( Position, normalize(Normal) ),1.0);
}

vec4 pass2()
{
    return vec4(toonShade( Position, normalize(Normal) ),1.0);
}


vec4 pass3()
{
 ivec2 pix = ivec2(gl_FragCoord.xy); //we grab a pixel to check if edge
//pick neighboutring pixels for convolution filter
//check lecture slides
//thicker lines somehow
 float s00 = luminance(texelFetchOffset(RenderTex, pix, 0, ivec2(-5,5)).rgb);
 float s10 = luminance(texelFetchOffset(RenderTex, pix, 0, ivec2(-5,0)).rgb);
 float s20 = luminance(texelFetchOffset(RenderTex, pix, 0, ivec2(-5,-5)).rgb);
 float s01 = luminance(texelFetchOffset(RenderTex, pix, 0, ivec2(0,5)).rgb);
 float s21 = luminance(texelFetchOffset(RenderTex, pix, 0, ivec2(0,-5)).rgb);
 float s02 = luminance(texelFetchOffset(RenderTex, pix, 0, ivec2(5,5)).rgb);
 float s12 = luminance(texelFetchOffset(RenderTex, pix, 0, ivec2(5,0)).rgb);
 float s22 = luminance(texelFetchOffset(RenderTex, pix, 0, ivec2(5,-5)).rgb);
 float sx = s00 + 2 * s10 + s20 - (s02 + 2 * s12 + s22);
 float sy = s00 + 2 * s01 + s02 - (s20 + 2 * s21 + s22);
 float g = sx * sx + sy * sy;
 if( g > EdgeThreshold )
 {
    return vec4(1.0,0.0,0.0,1.0); // edge
 }
 else
 {
    return vec4(0.0,0.0,0.0,1.0); // no edge
 }
}


void main()
{
    
    if( Pass == 1 ) FragColor = pass1();
    if( Pass == 2 ) FragColor = pass2();
    if( Pass == 3 ) FragColor = pass3();  
    
}




