#ifndef __CAMERA_H__
#define	__CAMERA_H__

/* OpenGL includes */
/* Standard includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

class Camera {
	private:
		glm::mat4 projectionMatrix; /* Perspective projection matrix */
		glm::mat4 viewMatrix; /* Camera view matrix */
		
		/* Transformation matrices for model positioning */
		glm::mat4 translationMatrix;
		glm::mat4 scaleMatrix;
		glm::mat4 rotationMatrix;
		
		GLint viewUniform;
		GLint projectionUniform;
		
		bool autoRotate;
		float autoRotated;
    
		void calculateViewMatrix(void);
	public:
		void init(ShaderProgram *shaderProgramm);
		void zoom(float scale);
		void rotateX(float angle);
		void rotateY(float angle);
		void rotateZ(float angle);
		void rotate(float angle, glm::vec3 axes);
		void translateX(float x);
		void translateY(float y);
		void translateZ(float z);
		void translate(float x, float y, float z);
		void render(void);
		void update(void);
		void setAutoRotate(bool autoRotate);
		bool getAutoRotate(void);
		void toggleAutoRotate(void);
		glm::mat4 getProjectionMatrix(void);
		glm::mat4 getViewMatrix(void);
		glm::mat4 getRotationMatrix(void);
		glm::mat4 getScaleMatrix(void);
		glm::mat4 getTranslationMatrix(void);
};

#endif	// __CAMERA_H__

