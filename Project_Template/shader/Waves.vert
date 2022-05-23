#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertextTexCoord;



out vec4 Position;
out vec3 Normal;
out vec2 TexCoord;

uniform float Time; //anim timer

//wave
uniform float Freq = 0.5;
uniform float Velocity = 3.3;
uniform float Amp = 0.35;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

void main()
{
    vec4 pos = vec4(VertexPosition, 1.0);

    //trans verts on y
    float u = Freq * pos.x - Velocity * Time;
    pos.y = Amp * sin(u);
    //poss x too? Break it?
    

    //normal
    vec3 n = vec3(0.0);
    //x?
    n.xy = normalize(vec2(cos(u), 1.0));

    
    

    


    Position = ModelViewMatrix * pos;
    Normal = NormalMatrix * n;
    TexCoord = VertextTexCoord;

    gl_Position = MVP * pos;
}
