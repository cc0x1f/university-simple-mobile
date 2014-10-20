#version 330
#pragma optimize (off)
// Input data from our vertex shader
in vec4 vColor;
in vec2 UVcoords;

uniform sampler2D TextureSampler;

// Output data 
out vec4 FragColor;

void main()
{
	FragColor = texture2D(TextureSampler, UVcoords) * vColor;
}