#version 430
in vec3 Vec;


layout( location = 0 ) out vec4 FragColor; 

layout( binding=2 ) uniform samplerCube SkyTex;

void main()
{
    vec3 sky = texture(SkyTex, normalize(Vec)).rgb;
    FragColor = vec4(sky, 1.0f);
    

    

    
    
   
    
    //gl_Position = MVP * vec4(VertexPosition,1.0);
}
