#version 330
#pragma optimize (off)

#define LIGHTS 2

// struct for our lightsource
struct DirectionalLight
{
	vec3 color;
	vec3 position;
	float ambientIntensity;
	float diffuseIntensity;
	float useAmbient;
	float useDiffuse;
	float useSpecular;
};

// Values that stay constant for the whole mesh.
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;
uniform DirectionalLight gDirectionalLight[LIGHTS];
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
	vec4 completeColor = vec4(0, 0, 0, 0);
	
	vec4 vertexPosition = ModelMatrix * vec4(Position, 1.0);
	
	// Output position of the vertex, in clip space : MVP * position
	gl_Position = ProjectionMatrix * ViewMatrix * vertexPosition;
	
	// Normal of the the vertex, in camera space
	vec3 normalDirection = normalize((ModelMatrix * vec4(Normal, 0.0)).xyz);
	vec3 viewDirection = normalize(vec3(0,0,0) - (ViewMatrix * vertexPosition).xyz);
	

	for (int light= 0; light < LIGHTS; light++) {
		vec3 lightDirection = normalize(gDirectionalLight[light].position - vec3(vertexPosition));
		vec3 reflectDirection = normalize(reflect(-lightDirection, normalDirection));
	
		// Calculate lightning colors
		ambientColor = vec4(gDirectionalLight[light].color, 1.0f) * gDirectionalLight[light].ambientIntensity;
		diffuseColor  = vec4(0, 0, 0, 0);                                   
		specularColor = vec4(0, 0, 0, 0);

		float diffuseFactor = dot(normalDirection, lightDirection);
		if (diffuseFactor > 0) {
			diffuseColor = vec4(gDirectionalLight[light].color, 1.0f) * gDirectionalLight[light].diffuseIntensity * diffuseFactor;

			float specularFactor = dot(viewDirection, reflectDirection);
			specularFactor = pow(specularFactor, materialSpecularPower);
			if (specularFactor > 0) {
				specularColor = vec4(gDirectionalLight[light].color, 1.0f) * materialSpecularIntensity * specularFactor;
			}
		}
		
		if (gDirectionalLight[light].useDiffuse < 0.5) {
			diffuseColor  = vec4(0, 0, 0, 0);
		}
		
		if (gDirectionalLight[light].useAmbient < 0.5) {
			ambientColor  = vec4(0, 0, 0, 0);
		}
		
		if (gDirectionalLight[light].useSpecular < 0.5) {
			specularColor  = vec4(0, 0, 0, 0);
		}
		
		completeColor = completeColor + (ambientColor + diffuseColor  + specularColor);
	}
	
	// the color of the vertex
	vColor = Color * completeColor;
}