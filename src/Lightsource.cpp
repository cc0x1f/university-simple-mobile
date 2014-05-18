 
#include "Lightsource.h" 

void Lightsource::init(ShaderProgram *shaderProgramm) {
	// init uniform variables
	this->directionalLightColorUniform = shaderProgramm->getUniformLocation("gDirectionalLight.color");
	this->directionalLightPositionUniform = shaderProgramm->getUniformLocation("gDirectionalLight.position");
	this->directionalLightAmbientIntensityUniform = shaderProgramm->getUniformLocation("gDirectionalLight.ambientIntensity");
	this->directionalLightDiffuseIntensityUniform = shaderProgramm->getUniformLocation("gDirectionalLight.diffuseIntensity");
	this->directionalLightUseAmbientUniform = shaderProgramm->getUniformLocation("gDirectionalLight.useAmbient");
	this->directionalLightUseDiffuseUniform = shaderProgramm->getUniformLocation("gDirectionalLight.useDiffuse");
	this->directionalLightUseSpecularUniform = shaderProgramm->getUniformLocation("gDirectionalLight.useSpecular");
}

void Lightsource::setDirectionalLight(const DirectionalLight& light) {
	glUniform3f(this->directionalLightPositionUniform, light.position.x, light.position.y, light.position.z);
	glUniform3f(this->directionalLightColorUniform, light.color.x, light.color.y, light.color.z);
	glUniform1f(this->directionalLightAmbientIntensityUniform, light.ambientIntensity);
	glUniform1f(this->directionalLightDiffuseIntensityUniform, light.diffuseIntensity);
	
	glUniform1f(this->directionalLightUseAmbientUniform, light.useAmbient);
	glUniform1f(this->directionalLightUseDiffuseUniform, light.useDiffuse);
	glUniform1f(this->directionalLightUseSpecularUniform, light.useSpecular);
}