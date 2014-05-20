#ifndef __LIGHTSOURCE_H__
#define	__LIGHTSOURCE_H__

/* OpenGL includes */
/* Standard includes */
#include <stdio.h>
#include <stdlib.h>
#include <string>

/* OpenGL includes */
#include <GL/glew.h>
#include <GL/freeglut.h>

#define GLM_FORCE_RADIANS  /* Use radians in all GLM functions */
/* GLM includes - adjust path as required for local installation */
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" /* Provides glm::translate, glm::rotate, glm::scale, glm::perspective */
#include "glm/gtc/type_ptr.hpp"         /* Vector/matrix handling */

/* local includes */
#include "ShaderProgram.h"

struct DirectionalLight
{
	glm::vec3 color;
	glm::vec3 position;
	float ambientIntensity;
	float diffuseIntensity;
	float useAmbient;
	float useDiffuse;
	float useSpecular;
};

class Lightsource {
	private:
		GLint directionalLightColorUniform;
		GLint directionalLightPositionUniform;
		GLint directionalLightAmbientIntensityUniform;
		GLint directionalLightDiffuseIntensityUniform;
		GLint directionalLightUseAmbientUniform;
		GLint directionalLightUseDiffuseUniform;
		GLint directionalLightUseSpecularUniform;
		
		int id;
	public:
		void init(ShaderProgram *shaderProgram, int id);
		void setDirectionalLight(const DirectionalLight& light);
};

#endif	// __LIGHTSOURCE_H__

 
