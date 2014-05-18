#version 330
#pragma optimize (off)

// struct for our lightsource
struct DirectionalLight
{
	vec3 color;
	vec3 position;
	float ambientIntensity;
	float diffuseIntensity; 
};

// Values that stay constant for the whole mesh.
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;
uniform DirectionalLight gDirectionalLight;
uniform float materialSpecularIntensity;                                                
uniform float materialSpecularPower;

// Input vertex data, different for all executions of this shader.
layout (location = 0) in vec3 Position;
layout (location = 1) in vec4 Color;
layout (location = 2) in vec3 Normal;

// Output data ; will be interpolated for each fragment.
out vec4 vColor;

void main()
{
	vec4 diffuseColor;
	vec4 specularColor;
	vec4 ambientColor;
	
	// Output position of the vertex, in clip space : MVP * position
	gl_Position = ProjectionMatrix*ViewMatrix*ModelMatrix*vec4(Position, 1.0);
	
	// Normal of the the vertex, in camera space
	vec3 normal = normalize(( ViewMatrix * vec4(Normal,0)).xyz);

	// Calculate lightning colors
	ambientColor = vec4(gDirectionalLight.color, 1.0f) * gDirectionalLight.ambientIntensity;
	diffuseColor  = vec4(0, 0, 0, 0);                                   
	specularColor = vec4(0, 0, 0, 0);

	float diffuseFactor = dot(normalize(normal), -gDirectionalLight.position);
	if (diffuseFactor > 0) {
		diffuseColor = vec4(gDirectionalLight.color, 1.0f) * gDirectionalLight.diffuseIntensity * diffuseFactor;

		vec3 vertexToEye = normalize(vec3(0,0,0) - (ViewMatrix * ModelMatrix * vec4(Position,1)).xyz);
		vec3 lightReflect = normalize(reflect(gDirectionalLight.position, normal));
		float specularFactor = dot(vertexToEye, lightReflect);
		specularFactor = pow(specularFactor, materialSpecularPower);
		if (specularFactor > 0) {
			specularColor = vec4(gDirectionalLight.color, 1.0f) * materialSpecularIntensity * specularFactor;
		}
	}
	
	// the color of the vertex
	vColor = Color * (ambientColor + diffuseColor  + specularColor);
}