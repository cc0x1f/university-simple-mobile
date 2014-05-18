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

// Input data from our vertex shader
in vec4 vColor;
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
	
	// Calculate lightning colors
	ambientColor = vec4(gDirectionalLight.color, 1.0f) * gDirectionalLight.ambientIntensity;
	diffuseColor  = vec4(0, 0, 0, 0);                                   
	specularColor = vec4(0, 0, 0, 0);

	vec3 viewDirection = normalize(vec3(0,0,0) - (ViewMatrix * vPosition).xyz);
	vec3 lightDirection = normalize(gDirectionalLight.position - vec3(vPosition));
	vec3 reflectDirection = normalize(reflect(-lightDirection, vnDirection));
	
	cosAngIncidence = dot(normalize(vnDirection), lightDirection);
	cosAngIncidence = clamp(cosAngIncidence, 0, 1);

	diffuseColor = vec4(gDirectionalLight.color, 1.0f) * gDirectionalLight.diffuseIntensity * cosAngIncidence;

	phongTerm = dot(viewDirection, reflectDirection);
	phongTerm = clamp(phongTerm, 0, 1);

	// No specular highlight if the light is on the wrong side
	phongTerm = cosAngIncidence != 0.0 ? phongTerm : 0.0;

	phongTerm = pow(phongTerm, materialSpecularPower);

	specularColor = vec4(gDirectionalLight.color, 1.0f) * materialSpecularIntensity * phongTerm;

	FragColor = vColor * (ambientColor + diffuseColor  + specularColor);
}