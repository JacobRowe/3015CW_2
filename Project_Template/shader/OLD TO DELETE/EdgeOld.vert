#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

layout( location = 1 ) out vec3 Position;
layout( location = 2 ) out vec3 Normal;


uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;



void main() {
	Normal = normalize( NormalMatrix * VertexNormal);
	Position = vec3(ModelViewMatrix * vec4(VertexPosition,1.0f));
	
	gl_Position = MVP * vec4(VertexPosition,1.0);
}

