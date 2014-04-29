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

/* local includes */
#include "GlHelper.h"
#include "ShaderProgram.h"
#include "Matrix.h"


class Camera {
	private:
		Matrix4f projectionMatrix; /* Perspective projection matrix */
		Matrix4f viewMatrix; /* Camera view matrix */ 
		
		Matrix4f rotationMatrix;
		Matrix4f scaleMatrix;
		Matrix4f translationMatrix;
		
		GLint viewUniform;
		GLint projectionUniform;
		
		bool autoRotate;
    
		void calculateViewMatrix(void);
	public:
		void init(ShaderProgram *shaderProgramm);
		void zoom(float scale);
		void rotateX(float angle);
		void rotateY(float angle);
		void rotateZ(float angle);
		void rotate(float angle, Vector3f axes);
		void translateX(float x);
		void translateY(float y);
		void translateZ(float z);
		void translate(float x, float y, float z);
		void render(void);
		void update(void);
		void setAutoRotate(bool autoRotate);
		bool getAutoRotate(void);
		void toggleAutoRotate(void);
};

#endif	// __CAMERA_H__

