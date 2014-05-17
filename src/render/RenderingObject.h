/* OpenGL includes */
/* Standard includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

/* OpenGL includes */
#include <GL/glew.h>
#include <GL/freeglut.h>

#define GLM_FORCE_RADIANS  /* Use radians in all GLM functions */
/* GLM includes - adjust path as required for local installation */
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" /* Provides glm::translate, glm::rotate, glm::scale, glm::perspective */
#include "glm/gtc/type_ptr.hpp"         /* Vector/matrix handling */

/* local includes */
#include "../Helper.h"
#include "../ShaderProgram.h"

#ifndef __RENDERING_OBJECT_H__
#define __RENDERING_OBJECT_H__
class RenderingObject {
	protected:
		GLuint VBO;
		GLuint CBO;
		GLuint IBO;
		
		RenderingObject *parent;

		std::vector<glm::vec3> VBO_data;
		std::vector<glm::vec3> CBO_data;
		std::vector<Helper::vec3s> IBO_data;

		glm::mat4 modelMatrix; // Model matrix
		glm::mat4 renderingModelMatrix; // FINAL Model matrix for rendering
		
		glm::mat4 rotationMatrix;
		glm::mat4 scaleMatrix;
		glm::mat4 translationMatrix;

		GLint modelUniform;
		GLenum renderingMode;

		void calculateModelMatrix(void);
	public:
		void init(ShaderProgram *shaderProgramm);
		void setParent(RenderingObject *parent);
		RenderingObject *getParent(void);
		void render(void);
		void scale(float scale);
		void rotateX(float angle);
		void rotateY(float angle);
		void rotateZ(float angle);
		void rotate(float angle, glm::vec3 axes);
		void translateX(float x);
		void translateY(float y);
		void translateZ(float z);
		void translate(float x, float y, float z);
		glm::mat4 getRenderingMatrix(void);
		glm::mat4 getRotationMatrix(void);
		glm::mat4 getScaleMatrix(void);
		glm::mat4 getTranslationMatrix(void);
};
#endif // __RENDERING_OBJECT_H__
 
