/* Standard includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* OpenGL includes */
#include <GL/glew.h>
#include <GL/freeglut.h>

#define GLM_FORCE_RADIANS  /* Use radians in all GLM functions */
/* GLM includes - adjust path as required for local installation */
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" /* Provides glm::translate, glm::rotate, glm::scale, glm::perspective */
#include "glm/gtc/type_ptr.hpp"         /* Vector/matrix handling */

/* local includes */
#include "Helper.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Lightsource.h"
#include "render/LineRenderingObject.h"
#include "render/BillboardRenderingObject.h"
#include "render/OBJRenderingObject.h"

#ifndef __GLUT_PROGRAM_H__
#define __GLUT_PROGRAM_H__
class GlutProgram {
	private:
		static GlutProgram *instance;
		
		int width;
		int height;
		int posX;
		int posY;
		int glutWindowId;
		bool rotateMobile;
		bool useGouraud;
		const char *title;
		ShaderProgram shaderProgram;
		Camera camera;
		LineRenderingObject line[7]; // lines for connecting all other elements
		BillboardRenderingObject billboard[1]; // billboard
		OBJRenderingObject wall[3]; // background walls
		// scene rendering objects =)
		OBJRenderingObject cube[2];
		OBJRenderingObject pyramid[1];
		OBJRenderingObject ball[1];
		OBJRenderingObject teapot[1];
		
		//light sources
		Lightsource lightSources[2];
		
		// light types for the light source
		DirectionalLight directionalLights[2];

		// GLUT needs those static functions...
		static void onDisplayWrapper(void){
			instance->onDisplay();
		}
		static void onIdleWrapper(void) {
			instance->onIdle();
		}
		static void onResizeWrapper(int width, int height) {
			instance->onResize(width, height);
		}
		static void onKeyboardInputWrapper(unsigned char key, int x, int y) {
			instance->onKeyboardInput(key, x, y);
		}
		static void onSpecialInputWrapper(int key, int x, int y) {
			instance->onSpecialInput(key, x, y);
		}
		static void onMouseInputWrapper(int button, int state, int x, int y) {
			instance->onMouseInput(button, state, x, y);
		}
		
		void onDisplay(void);
		void onIdle(void);
		void onResize(int width, int height);
		void onKeyboardInput(unsigned char key, int x, int y);
		void onSpecialInput(int key, int x, int y);
		void onMouseInput(int button, int state, int x, int y);
		void reInitUniforms(void);
		void printHelp();
		
		void initScene(void);
		
	public:
		static void setInstance(GlutProgram * glutProgram);
		
		void setDimensions(int width, int height);
		void setPosition(int x, int y);
		void setTitle(const char *title);
		void init(int *argc, char **argv);
		void run(void);
};
#endif // __SHADER_PROGRAM_H__
