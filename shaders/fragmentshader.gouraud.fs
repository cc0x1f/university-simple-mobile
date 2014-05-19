#version 330
#pragma optimize (off)
// Input data from our vertex shader
in vec4 vColor;

// Output data 
out vec4 FragColor;

void main()
{
	FragColor = vColor;
}