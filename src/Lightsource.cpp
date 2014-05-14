 
#include "Lightsource.h" 

void Lightsource::init(ShaderProgram *shaderProgramm) {
	// init uniform variables
	this->directionalLightColorUniform = shaderProgramm->getUniformLocation("gDirectionalLight.color");
	this->directionalLightAmbientIntensityUniform = shaderProgramm->getUniformLocation("gDirectionalLight.ambientIntensity");
	
#ifdef DEBUG
	printf("Lightsource initialized!\n");
	fflush(stdout);
#endif
}

void Lightsource::setDirectionalLight(const DirectionalLight& light) {
    glUniform3f(this->directionalLightColorUniform, light.color.x, light.color.y, light.color.z);
    glUniform1f(this->directionalLightAmbientIntensityUniform, light.ambientIntensity);
}
