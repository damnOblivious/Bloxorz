#version 330 core

// input data : sent from main program
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 texCoords;

uniform mat4 MVP;

// output data : used by fragment shader
out vec3 fragColor;
out vec2 finalTexCoords;

void main ()
{
    vec4 v = vec4(vertexPosition, 1); // Transform an homogeneous 4D vector
    fragColor = vertexColor;
    gl_Position = MVP * v;
    finalTexCoords = texCoords;
}
