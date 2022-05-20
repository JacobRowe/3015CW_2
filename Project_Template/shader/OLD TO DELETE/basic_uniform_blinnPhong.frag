#version 430
in vec3 Colour;
in vec3 LightIntensity;

layout (location = 0) out vec4 FragColor;

void main() {
    FragColor = vec4(Colour, 1.0f);
}
