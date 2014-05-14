#include "GlutProgram.h"

GlutProgram *GlutProgram::instance = 0;
void GlutProgram::setInstance(GlutProgram *glutProgram) {
	instance = glutProgram;
}

void GlutProgram::setDimensions(int width, int height){
	this->width = width;
	this->height = height;
}

void GlutProgram::setPosition(int x, int y){
	this->posX = x;
	this->posY = y;
}

void GlutProgram::setTitle(const char *title){
	this->title = title;
}

void GlutProgram::init(int *argc, char **argv) {
	glutInit(argc, argv);
	// Define a opengl context...
	//glutInitContextVersion(3,3);
	//glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glutInitWindowSize(this->width, this->height);
	glutInitWindowPosition(this->posX, this->posY);
	glutCreateWindow(this->title);
	
	// specifiy glut callbacks
	glutIdleFunc(GlutProgram::onIdleWrapper);
	glutDisplayFunc(GlutProgram::onDisplayWrapper);
	glutKeyboardFunc(GlutProgram::onKeyboardInputWrapper);
	glutSpecialFunc(GlutProgram::onSpecialInputWrapper);
	glutMouseFunc(GlutProgram::onMouseInputWrapper);
	glutReshapeFunc(GlutProgram::onResizeWrapper);
	
	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		exit(1);
	}
	
	printf("Initialized, OpenGL version: %s\n", glGetString(GL_VERSION));
	printf("Supported GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f); // grey background
	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	this->shaderProgram.setVertexShader("shaders/vertexshader.330.vs");
	this->shaderProgram.setFragmentShader("shaders/fragmentshader.330.fs");
	
	this->shaderProgram.create();
	
	// init the scene
	this->initScene();
}

void GlutProgram::initScene(void) {
	// init camera
	this->camera.init(&this->shaderProgram);
	this->camera.zoom(0.5f);
	this->camera.rotateY(-45);
	
	// init lightsource
	this->lightSource.init(&this->shaderProgram);
	this->directionalLight.color = Vector3f(1.0f, 1.0f, 1.0f);
    this->directionalLight.ambientIntensity = 0.5f;
	this->lightSource.setDirectionalLight(this->directionalLight);
	
	// init rendering cubes
	// left cube
	this->cube[0].initVertices(Vector3f(1.0f,0.0f,0.0f));
	this->cube[0].init(&this->shaderProgram);
	this->cube[0].scale(1);
	this->cube[0].translate(0.0f, 2.0f, 0.0f);
	this->cube[0].setParent(&this->line[2]);
	// right cube
	this->cube[1].initVertices(Vector3f(0.0f,1.0f,0.0f));
	this->cube[1].init(&this->shaderProgram);
	this->cube[1].rotate(45, Vector3f(1.0,0.0,0.0));
	this->cube[1].translate(0.0f, 1.0f, 0.0f);
	this->cube[1].scale(0.6f);
	this->cube[1].setParent(&this->line[3]);
	
	// init rendering triangles
	// left triangle
	this->triangle[0].initVertices();
	this->triangle[0].init(&this->shaderProgram);
	this->triangle[0].translate(-0.25f, 1.0f, 0.0f);
	this->triangle[0].rotateZ(-90);
	this->triangle[0].setParent(&this->line[5]);
	// right triangle
	this->triangle[1].initVertices();
	this->triangle[1].init(&this->shaderProgram);
	this->triangle[1].translate(-0.25f, 0.0f, 0.0f);
	this->triangle[1].rotateZ(-90);
	this->triangle[1].setParent(&this->line[5]);
	
	// init rendering obj-objects
	this->obj[0].initVertices("models/teapot.obj", Vector3f(0.7f,0.7f,0.7f)); // grey teapot
	this->obj[0].init(&this->shaderProgram);
	this->obj[0].translate(0.0f, -0.75f, 0.0f);
	this->obj[0].scale(0.5f);
	this->obj[0].setParent(&this->line[6]);
	
	// background grids
	this->grid[0].initVertices(10,10, Vector3f(1.0,0.0,0.0));
	this->grid[0].init(&this->shaderProgram);
	this->grid[0].rotateX(90);
	this->grid[0].scale(10);
	this->grid[0].translate(-5,-5,-5);
	this->grid[1].initVertices(10,10, Vector3f(0.0,1.0,0.0));
	this->grid[1].init(&this->shaderProgram);
	this->grid[1].rotateY(-90);
	this->grid[1].scale(10);
	this->grid[1].translate(-5,-5,-5);
	this->grid[2].initVertices(10,10, Vector3f(0.0,0.0,1.0));
	this->grid[2].init(&this->shaderProgram);
	this->grid[2].scale(10);
	this->grid[2].translate(-5,-5,-5);
	
	// lines
	// top centered vertical line
	this->line[0].initVertices(Vector3f(1.0,1.0,1.0));
	this->line[0].init(&this->shaderProgram);
	this->line[0].scale(1);
	this->line[0].translate(0.0f,4.0f,-1.0f);
	// top horizontal line
	this->line[1].initVertices(Vector3f(1.0,1.0,1.0)); 
	this->line[1].init(&this->shaderProgram);
	this->line[1].rotateZ(-90);
	this->line[1].scale(4);
	this->line[1].translate(-2.0f,0.0f,0.0f);
	this->line[1].setParent(&this->line[0]);
	// top left vertical line
	this->line[2].initVertices(Vector3f(1.0,1.0,1.0)); 
	this->line[2].init(&this->shaderProgram);
	this->line[2].scale(1);
	this->line[2].rotateZ(-90);
	this->line[2].setParent(&this->line[1]);
	// top right vertical line
	this->line[3].initVertices(Vector3f(1.0,1.0,1.0)); 
	this->line[3].init(&this->shaderProgram);
	this->line[3].scale(1);
	this->line[3].rotateZ(-90);
	this->line[3].translate(0.0f,1.0f,0.0f);
	this->line[3].setParent(&this->line[1]);
	// bottom centered vertical line
	this->line[4].initVertices(Vector3f(1.0,1.0,1.0));
	this->line[4].init(&this->shaderProgram);
	this->line[4].scale(2);
	this->line[4].translate(0.0f,0.0f,0.0f);
	this->line[4].setParent(&this->cube[0]);
	// bottom horizontal line
	this->line[5].initVertices(Vector3f(1.0,1.0,1.0));
	this->line[5].init(&this->shaderProgram);
	this->line[5].scale(4);
	this->line[5].rotateZ(-90);
	this->line[5].translate(-1.0f,1.0f,0.0f);
	this->line[5].setParent(&this->line[4]);
	// lowest vertical line
	this->line[6].initVertices(Vector3f(1.0,1.0,1.0));
	this->line[6].init(&this->shaderProgram);
	this->line[6].scale(1);
	this->line[6].translate(0.0f,-2.0f,0.0f);
	this->line[6].setParent(&this->triangle[1]);
}

void GlutProgram::run(void) {
	glutMainLoop();
}

void GlutProgram::onDisplay(void) {
	/* Clear window; color specified in 'Initialize()' */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->camera.render();
	this->lightSource.setDirectionalLight(this->directionalLight);

	// rendering hirarchie
	this->line[0].render();
		this->line[1].render();
			this->line[2].render();
				this->cube[0].render();
			this->line[3].render();
				this->cube[1].render();
					this->line[4].render();
						this->line[5].render();
							this->triangle[0].render();
							this->triangle[1].render();
								this->line[6].render();
									this->obj[0].render();
	
	int i;
	for(i = 0; i < 3; i++) {
		this->grid[i].render();
	}

	/* Swap between front and back buffer */ 
	glutSwapBuffers();
}

void GlutProgram::onIdle(void) {

	this->camera.update();
	
	this->line[0].rotateY(0.1f);
	
	this->cube[0].rotateY(0.5f);
	this->cube[1].rotateY(0.2f);
		
	this->triangle[0].rotateX(0.2f);
	this->triangle[1].rotateX(0.5f);
	
	this->obj[0].rotateY(1.0f);
	
	glutPostRedisplay();
}

void GlutProgram::onResize(int width, int height) {
	glutPostRedisplay();
}

void GlutProgram::onKeyboardInput(unsigned char key, int x, int y) {

#ifdef DEBUG
	printf("Input event received: %c\n", key);
	fflush(stdout);
#endif
	
	switch (key) {
		case 27:
		case 'q':
			exit(0);
			break;
		case 'r':
			this->camera.toggleAutoRotate();
			break;
		case 'm':
			this->directionalLight.ambientIntensity += 0.05f;
			break;
		case 'n':
			this->directionalLight.ambientIntensity -= 0.05f;
			break;
		default:
			break;
	}
}

void GlutProgram::onSpecialInput(int key, int x, int y) {
#ifdef DEBUG
	printf("Specialinput event received: %c\n", key);
	fflush(stdout);
#endif
	
	switch (key) {
		case GLUT_KEY_UP:
			this->camera.rotateX(1.0f);
			break;
		case GLUT_KEY_DOWN:
			this->camera.rotateX(-1.0f);
			break;
		case GLUT_KEY_LEFT:
			this->camera.rotateY(1.0f);
			break;
		case GLUT_KEY_RIGHT:
			this->camera.rotateY(-1.0f);
			break;
		default:
			break;
	}
}

void GlutProgram::onMouseInput(int button, int state, int x, int y) {
}
