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
uniform sampler2D TextureSampler;
uniform DirectionalLight gDirectionalLight[LIGHTS];
uniform float materialSpecularIntensity;                                                
uniform float materialSpecularPower;

// Input data from our vertex shader
in vec2 UVcoords;
in vec3 vnDirection;
in vec4 vPosition;

// Output data 
out vec4 FragColor;

void main()
{
	float cosAngIncidence;
	float phongTerm;
	
	vec4 diffuseColor;
	vec4 specularColor;
	vec4 ambientColor;
	vec4 completeColor = vec4(0, 0, 0, 0);
	
	for (int light= 0; light < LIGHTS; light++) {
		// Calculate lightning colors
		ambientColor = vec4(gDirectionalLight[light].color, 1.0f) * gDirectionalLight[light].ambientIntensity;
		diffuseColor  = vec4(0, 0, 0, 0);                                   
		specularColor = vec4(0, 0, 0, 0);

		vec3 viewDirection = normalize(vec3(0,0,0) - (ViewMatrix * vPosition).xyz);
		vec3 lightDirection = normalize(gDirectionalLight[light].position - vec3(vPosition));
		vec3 reflectDirection = reflect(-lightDirection, normalize(vnDirection));
		
		cosAngIncidence = dot(normalize(vnDirection), lightDirection);
		cosAngIncidence = clamp(cosAngIncidence, 0, 1);

		diffuseColor = vec4(gDirectionalLight[light].color, 1.0f) * gDirectionalLight[light].diffuseIntensity * cosAngIncidence;

		phongTerm = dot(viewDirection, reflectDirection);
		phongTerm = clamp(phongTerm, 0, 1);

		// No specular highlight if the light is on the wrong side
		phongTerm = cosAngIncidence != 0.0 ? phongTerm : 0.0;

		phongTerm = pow(phongTerm, materialSpecularPower);

		specularColor = vec4(gDirectionalLight[light].color, 1.0f) * materialSpecularIntensity * phongTerm;
		
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

	FragColor = texture2D(TextureSampler, UVcoords) * completeColor;
}
