/* OpenGL includes */
/* Standard includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* OpenGL includes */
#include <GL/glew.h>
#include <GL/freeglut.h>

/* local includes */
#include "../GlHelper.h"
#include "../ShaderProgram.h"
#include "../Matrix.h"

#ifndef __RENDERING_OBJECT_H__
#define __RENDERING_OBJECT_H__
class RenderingObject {
	protected:
		GLuint VBO;
		GLuint CBO;
		GLuint IBO;
		
		RenderingObject *parent;

		Vector3f *VBO_data;
		Vector3f *CBO_data;
		Vector3s *IBO_data;

		int VBO_size;
		int CBO_size;
		int IBO_size;

		Matrix4f modelMatrix; // Model matrix
		Matrix4f renderingModelMatrix; // FINAL Model matrix for rendering
		
		Matrix4f rotationMatrix;
		Matrix4f scaleMatrix;
		Matrix4f translationMatrix;

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
		void rotate(float angle, Vector3f axes);
		void translateX(float x);
		void translateY(float y);
		void translateZ(float z);
		void translate(float x, float y, float z);
		Matrix4f getRenderingMatrix(void);
		Matrix4f getRotationMatrix(void);
		Matrix4f getScaleMatrix(void);
		Matrix4f getTranslationMatrix(void);
};
#endif // __RENDERING_OBJECT_H__
 
