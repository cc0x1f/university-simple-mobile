#version 330
#pragma optimize (off)

// Values that stay constant for the whole mesh.
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

// Input vertex data, different for all executions of this shader.
layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 UV;
layout (location = 2) in vec3 Normal;

// Output data ; will be interpolated for each fragment.
out vec2 UVcoords;
out vec3 vnDirection;
out vec4 vPosition;

void main()
{
	vPosition = ModelMatrix * vec4(Position, 1.0);
	
	gl_Position = ProjectionMatrix * ViewMatrix * vPosition;
	
	vnDirection = normalize(vec3(ModelMatrix * vec4(Normal, 0.0)));
	
	UVcoords = UV;
}