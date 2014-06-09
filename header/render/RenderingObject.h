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
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp" /* Provides glm::translate, glm::rotate, glm::scale, glm::perspective */
#include "../glm/gtc/type_ptr.hpp"         /* Vector/matrix handling */

/* local includes */
#include "../Helper.h"
#include "../ShaderProgram.h"
#include "../Texture.h"

#ifndef __RENDERING_OBJECT_H__
#define __RENDERING_OBJECT_H__
class RenderingObject {
	protected:
		GLuint VBO;
		GLuint UV;
		GLuint IBO;
		GLuint NORMALS;
		GLuint TEXTURE;
		
		RenderingObject *parent;

		std::vector<float> VBO_data;
		std::vector<float> NORMALS_data;
		std::vector<float> UV_data;
		std::vector<unsigned short> IBO_data;

		glm::mat4 modelMatrix; // Model matrix
		glm::mat4 renderingModelMatrix; // FINAL Model matrix for rendering
		
		glm::mat4 rotationMatrix;
		glm::mat4 scaleMatrix;
		glm::mat4 translationMatrix;
		
		TextureDataPtr *texture;

		GLint modelUniform;
		GLuint specularIntensityUniform;
		GLuint specularPowerUniform;
		GLuint textureUniform;
		
		GLenum renderingMode;
		float specularIntensity;
		float specularPower;

		void calculateModelMatrix(void);
	public:
		void initUniformAndBuffer(ShaderProgram *shaderProgram);
		void initTexture(const char *textureFile);
		void init(ShaderProgram *shaderProgram);
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
		void calcNormals();
		void setMatSpecularIntensity(float intensity);
		void setMatSpecularPower(float power);
		glm::mat4 getRenderingMatrix(void);
		glm::mat4 getRotationMatrix(void);
		glm::mat4 getScaleMatrix(void);
		glm::mat4 getTranslationMatrix(void);
};
#endif // __RENDERING_OBJECT_H__
 
