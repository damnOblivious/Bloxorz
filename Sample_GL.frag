#version 330 core

// Interpolated values from the vertex shaders
in vec3 fragColor;
in vec2 finalTexCoords;

// output data
out vec4 color;

uniform sampler2D texture_diffuse1;

void main()
{
    // Output color = color specified in the vertex shader,
    // interpolated between all 3 surrounding vertices of the triangle
    color = vec4(texture(texture_diffuse1, finalTexCoords));
}
