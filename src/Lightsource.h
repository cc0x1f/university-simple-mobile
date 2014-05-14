#ifndef __LIGHTSOURCE_H__
#define	__LIGHTSOURCE_H__

/* OpenGL includes */
/* Standard includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* OpenGL includes */
#include <GL/glew.h>
#include <GL/freeglut.h>

/* local includes */
#include "GlHelper.h"
#include "ShaderProgram.h"
#include "Matrix.h"

struct DirectionalLight
{
    Vector3f color;
    float ambientIntensity;
};

class Lightsource {
	private:
		GLint directionalLightColorUniform;
		GLint directionalLightAmbientIntensityUniform;
	public:
		void init(ShaderProgram *shaderProgramm);
		void setDirectionalLight(const DirectionalLight& light);
};

#endif	// __LIGHTSOURCE_H__

 
