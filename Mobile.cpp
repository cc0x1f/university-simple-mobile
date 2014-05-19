#include "header/GlutProgram.h"

/*----------------------------------------------------------------*/
GlutProgram *glutProgram;
/*----------------------------------------------------------------*/

int main(int argc, char** argv) {
	glutProgram = new GlutProgram();

	glutProgram->setInstance(glutProgram);
	glutProgram->setDimensions(600, 600);
	glutProgram->setPosition(100,100);
	glutProgram->setTitle("Christoph's & Claudio's Mobile");
	glutProgram->init(&argc, argv);
	glutProgram->run();

	return 0;
}
