 
#include "Lightsource.h" 
#include <sstream>

void Lightsource::init(ShaderProgram *shaderProgramm, int id) {
	this->id = id;

	std::stringstream s;
	s << "gDirectionalLight[" << this->id << "].";
	std::string base = s.str();

	// init uniform variables
	this->directionalLightColorUniform = shaderProgramm->getUniformLocation((base + "color").c_str());
	this->directionalLightPositionUniform = shaderProgramm->getUniformLocation((base + "position").c_str());
	this->directionalLightAmbientIntensityUniform = shaderProgramm->getUniformLocation((base + "ambientIntensity").c_str());
	this->directionalLightDiffuseIntensityUniform = shaderProgramm->getUniformLocation((base + "diffuseIntensity").c_str());
	this->directionalLightUseAmbientUniform = shaderProgramm->getUniformLocation((base + "useAmbient").c_str());
	this->directionalLightUseDiffuseUniform = shaderProgramm->getUniformLocation((base + "useDiffuse").c_str());
	this->directionalLightUseSpecularUniform = shaderProgramm->getUniformLocation((base + "useSpecular").c_str());
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
