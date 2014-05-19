#include "GlutProgram.h"
#include <sstream>
#include <iostream>

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
	// glutInitContextVersion(3,3);
	// glutInitContextProfile(GLUT_CORE_PROFILE);
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
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f); // dark background
	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	this->useGouraud = true;
	
	if(*argc > 1) {
		if(strncmp(argv[1], "-g", 2) == 0){
			this->useGouraud = true;
		} else if (strncmp(argv[1], "-p", 2) == 0) {
			this->useGouraud = false;
		} else if( strncmp(argv[1], "-h", 2 ) == 0 ){
			printHelp();
			exit(0);
		}
		else {
			printf("Incorrect argument, using Gourard shading!\n");
		}
	}
	
	if(this->useGouraud) {
		this->shaderProgram.setVertexShader("shaders/vertexshader.gouraud.vs");
		this->shaderProgram.setFragmentShader("shaders/fragmentshader.gouraud.fs");
	} else {
		this->shaderProgram.setVertexShader("shaders/vertexshader.phong.vs");
		this->shaderProgram.setFragmentShader("shaders/fragmentshader.phong.fs");
	}
	
	this->shaderProgram.create();
	
	this->rotateMobile = true;
	
	// init the scene
	this->initScene();
}

void GlutProgram::printHelp(){
	std::stringstream help;

	help << "Command line arguments: " << "\n";
	help << "\tGouraud: -g or nothing" << "\n";
	help << "\tPhong: -p" << "\n";
	help << "\tHelp: -h" << "\n\n";

	help << "Runtime Options: " << "\n";
	help << "\tQuit: ESC or q" << "\n";
	help << "\tToggle Camera Auto-Rotating: r" << "\n";
	help << "\tDisable/Enable Mobile rotating: t" << "\n";
	help << "\tIncrease Ambient Intensity: m" << "\n";
	help << "\tDecrease Ambient Intensity: n" << "\n";
	help << "\tTranslate Z-Axis+: i" << "\n";
	help << "\tTranslate Z-Axis-: o" << "\n";
	help << "\tIncrease red: 1" << "\n";
	help << "\tIncrease green: 2" << "\n";
	help << "\tIncrease blue: 3" << "\n";
	help << "\tEnable/Disable ambient: a" << "\n";
	help << "\tEnable/Disable diffuse: d" << "\n";
	help << "\tEnable/Disable specular: s";

	std::cout << help.str() << std::endl;
}

void GlutProgram::initScene(void) {
	// init camera
	this->camera.init(&this->shaderProgram);
	
	this->camera.zoom(0.5f);
	this->camera.rotateY(-45);
	this->camera.translateZ(-2.0f);
	
	// init lightsources
	this->lightSources[0].init(&this->shaderProgram, 0);
	this->directionalLights[0].position = glm::vec3(4.0f, 4.0f, 10.0f);
	this->directionalLights[0].color = glm::vec3(1.0f, 1.0f, 1.0f);
    this->directionalLights[0].ambientIntensity = 0.5f;
	this->directionalLights[0].diffuseIntensity = 0.7f;
	this->directionalLights[0].useAmbient = 1;
	this->directionalLights[0].useDiffuse = 1;
	this->directionalLights[0].useSpecular = 1;
	this->lightSources[0].setDirectionalLight(this->directionalLights[0]);
	
	this->lightSources[1].init(&this->shaderProgram, 1);
	this->directionalLights[1].position = glm::vec3(-1.0f, 0.0f, 0.0f);
	this->directionalLights[1].color = glm::vec3(0.0f, 0.0f, 1.0f); // a second blue light ;)
    this->directionalLights[1].ambientIntensity = 0.0f;
	this->directionalLights[1].diffuseIntensity = 0.4f;
	this->directionalLights[1].useAmbient = 0;
	this->directionalLights[1].useDiffuse = 1;
	this->directionalLights[1].useSpecular = 1;
	this->lightSources[1].setDirectionalLight(this->directionalLights[1]);
	
	// init rendering cubes
	// left cube
	this->cube[0].initVertices("models/cube.obj", glm::vec3(1.0f,0.0f,0.0f));
	this->cube[0].init(&this->shaderProgram);
	this->cube[0].setMatSpecularIntensity(1.0f);
	this->cube[0].setMatSpecularPower(100.0f);
	this->cube[0].scale(1);
	this->cube[0].translate(0.0f, 2.0f, 0.0f);
	this->cube[0].setParent(&this->line[2]);
	// right cube
	this->cube[1].initVertices("models/cube.obj", glm::vec3(0.0f,1.0f,0.0f));
	this->cube[1].init(&this->shaderProgram);
	this->cube[1].setMatSpecularIntensity(1.0f);
	this->cube[1].setMatSpecularPower(50.0f);
	this->cube[1].rotate(45, glm::vec3(1.0,0.0,0.0));
	this->cube[1].translate(0.0f, 1.0f, 0.0f);
	this->cube[1].scale(0.6f);
	this->cube[1].setParent(&this->line[3]);
	
	// init rendering pyramids
	// left pyramid
	this->pyramid[0].initVertices("models/pyramid.obj", glm::vec3(0.0f,0.0f,1.0f));
	this->pyramid[0].init(&this->shaderProgram);
	this->pyramid[0].setMatSpecularIntensity(1.0f);
	this->pyramid[0].setMatSpecularPower(32.0f);
	this->pyramid[0].translate(-0.5f, 1.0f, 0.0f);
	this->pyramid[0].rotateY(90);
	this->pyramid[0].setParent(&this->line[5]);
	// right ball
	this->ball[0].initVertices("models/ball.obj", glm::vec3(1.0f,0.3f,0.6f));
	this->ball[0].init(&this->shaderProgram);
	this->ball[0].setMatSpecularIntensity(1.0f);
	this->ball[0].setMatSpecularPower(32.0f);
	this->ball[0].translate(-0.27f, 0.0f, 0.0f);
	this->ball[0].rotateZ(-90);
	this->ball[0].setParent(&this->line[5]);
	
	// init rendering teapot-objects
	this->teapot[0].initVertices("models/teapot.obj", glm::vec3(1.0f,1.0f,0.0f));
	this->teapot[0].init(&this->shaderProgram);
	this->teapot[0].setMatSpecularIntensity(1.0f);
	this->teapot[0].setMatSpecularPower(80.0f);
	this->teapot[0].translate(0.0f, -0.75f, 0.0f);
	this->teapot[0].scale(0.5f);
	this->teapot[0].setParent(&this->line[6]);
	
	// background walls
	this->wall[0].initVertices("models/rectangle.obj", glm::vec3(0.8f,0.8f,1.0f));
	this->wall[0].init(&this->shaderProgram);
	this->wall[0].rotateX(90);
	this->wall[0].scale(10);
	this->wall[0].translate(3, -7, 3);
	this->wall[1].initVertices("models/rectangle.obj", glm::vec3(0.8f,0.8f,1.0f));
	this->wall[1].init(&this->shaderProgram);
	this->wall[1].rotateY(-90);
	this->wall[1].scale(10);
	this->wall[1].translate(-7, 3, 3);
	this->wall[2].initVertices("models/rectangle.obj", glm::vec3(0.8f,0.8f,1.0f));
	this->wall[2].init(&this->shaderProgram);
	this->wall[2].scale(10);
	this->wall[2].translate(3, 3, -7);
	
	// lines
	// top centered vertical line
	this->line[0].initVertices(glm::vec3(0.0,0.0,0.0));
	this->line[0].init(&this->shaderProgram);
	this->line[0].scale(1);
	this->line[0].translate(0.0f,4.0f,-1.0f);
	// top horizontal line
	this->line[1].initVertices(glm::vec3(0.0,0.0,0.0)); 
	this->line[1].init(&this->shaderProgram);
	this->line[1].rotateZ(-90);
	this->line[1].scale(4);
	this->line[1].translate(-2.0f,0.0f,0.0f);
	this->line[1].setParent(&this->line[0]);
	// top left vertical line
	this->line[2].initVertices(glm::vec3(0.0,0.0,0.0)); 
	this->line[2].init(&this->shaderProgram);
	this->line[2].scale(1);
	this->line[2].rotateZ(-90);
	this->line[2].setParent(&this->line[1]);
	// top right vertical line
	this->line[3].initVertices(glm::vec3(0.0,0.0,0.0)); 
	this->line[3].init(&this->shaderProgram);
	this->line[3].scale(1);
	this->line[3].rotateZ(-90);
	this->line[3].translate(0.0f,1.0f,0.0f);
	this->line[3].setParent(&this->line[1]);
	// bottom centered vertical line
	this->line[4].initVertices(glm::vec3(0.0,0.0,0.0));
	this->line[4].init(&this->shaderProgram);
	this->line[4].scale(2);
	this->line[4].translate(0.0f,0.0f,0.0f);
	this->line[4].setParent(&this->cube[0]);
	// bottom horizontal line
	this->line[5].initVertices(glm::vec3(0.0,0.0,0.0));
	this->line[5].init(&this->shaderProgram);
	this->line[5].scale(4);
	this->line[5].rotateZ(-90);
	this->line[5].translate(-1.0f,1.0f,0.0f);
	this->line[5].setParent(&this->line[4]);
	// lowest vertical line
	this->line[6].initVertices(glm::vec3(0.0,0.0,0.0));
	this->line[6].init(&this->shaderProgram);
	this->line[6].scale(1);
	this->line[6].translate(0.0f,-1.5f,0.0f);
	this->line[6].setParent(&this->ball[0]);
}

void GlutProgram::run(void) {
	glutMainLoop();
}

void GlutProgram::onDisplay(void) {
	/* Clear window; color specified in 'Initialize()' */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->camera.render();
	
	// rendering hirarchie
	this->line[0].render();
		this->line[1].render();
			this->line[2].render();
				this->cube[0].render();
			this->line[3].render();
				this->cube[1].render();
					this->line[4].render();
						this->line[5].render();
							this->pyramid[0].render();
							this->ball[0].render();
								this->line[6].render();
									this->teapot[0].render();

	int i;
	for(i = 0; i < 3; i++) {
		this->wall[i].render();
	}

	/* Swap between front and back buffer */
	glutSwapBuffers();
}

void GlutProgram::onIdle(void) {

	this->camera.update();
	
	if(this->rotateMobile) {
		this->line[0].rotateY(0.01f);
		
		this->cube[0].rotateY(0.05f);
		this->cube[1].rotateY(0.02f);
			
		//this->pyramid[0].rotateX(0.02f);
		this->ball[0].rotateX(0.05f);
		
		this->teapot[0].rotateY(0.03f);
	}

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
	float oldR = this->directionalLights[0].color.x;
	float oldG = this->directionalLights[0].color.y;
	float oldB = this->directionalLights[0].color.z;
	
	switch (key) {
		case 27:
		case 'q':
			exit(0);
			break;
		case 'r':
			this->camera.toggleAutoRotate();
			break;
		case 't':
			this->rotateMobile = !this->rotateMobile;
			break;
		case 'm':
			this->directionalLights[0].ambientIntensity += 0.05f;
			break;
		case 'n':
			this->directionalLights[0].ambientIntensity -= 0.05f;
			break;
		case 'i':
			this->camera.translateZ(1.0f);
			break;
		case 'o':
			this->camera.translateZ(-1.0f);
			break;
		// color changing...
		case '1':
			oldR += 0.34f;
			
			if(oldR > 1.0f) {
				oldR = 0;
			}
			
			this->directionalLights[0].color = glm::vec3(oldR, oldG, oldB);
			this->lightSources[0].setDirectionalLight(this->directionalLights[0]);
			break;
		case '2':
			oldG += 0.34f;
			
			if(oldG > 1.0f) {
				oldG = 0;
			}
			
			this->directionalLights[0].color = glm::vec3(oldR, oldG, oldB);
			this->lightSources[0].setDirectionalLight(this->directionalLights[0]);
			break;
		case '3':
			oldB += 0.34f;
			
			if(oldB > 1.0f) {
				oldB = 0;
			}
			
			this->directionalLights[0].color = glm::vec3(oldR, oldG, oldB);
			this->lightSources[0].setDirectionalLight(this->directionalLights[0]);
			break;
		// enable lightning parts
		case 'a':
			this->directionalLights[0].useAmbient = glm::abs(1 - this->directionalLights[0].useAmbient);
			this->lightSources[0].setDirectionalLight(this->directionalLights[0]);
			break;
		case 'd':
			this->directionalLights[0].useDiffuse = glm::abs(1 - this->directionalLights[0].useDiffuse);
			this->lightSources[0].setDirectionalLight(this->directionalLights[0]);
			break;
		case 's':
			this->directionalLights[0].useSpecular = glm::abs(1 - this->directionalLights[0].useSpecular);
			this->lightSources[0].setDirectionalLight(this->directionalLights[0]);
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
