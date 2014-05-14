#include "CubeRenderingObject.h" 

void CubeRenderingObject::initVertices(Vector3f color) {
	
	this->VBO_size = 8;
	this->CBO_size = 8;
	this->IBO_size = 12;

	this->VBO_data = (Vector3f*) calloc (this->VBO_size, sizeof(Vector3f)); // we need 8 vertices to describe a cube
	this->CBO_data = (Vector3f*) calloc (this->CBO_size, sizeof(Vector3f)); // colors for each vertex
	this->IBO_data = (Vector3s*) calloc (this->IBO_size, sizeof(Vector3s)); // Indices of 6*2 triangles

	this->VBO_data[0] = Vector3f(-1.0, -1.0,  1.0);
	this->VBO_data[1] = Vector3f(1.0, -1.0,  1.0);
	this->VBO_data[2] = Vector3f(1.0,  1.0,  1.0);
	this->VBO_data[3] = Vector3f(-1.0,  1.0,  1.0);
	this->VBO_data[4] = Vector3f(-1.0, -1.0, -1.0);
	this->VBO_data[5] = Vector3f(1.0, -1.0, -1.0);
	this->VBO_data[6] = Vector3f(1.0,  1.0, -1.0);
	this->VBO_data[7] = Vector3f(-1.0,  1.0, -1.0);


	for(int i=0; i<8; i++) {
		this->CBO_data[i] = color;
	}

	this->IBO_data[0] = Vector3s(0, 1, 2);
	this->IBO_data[1] = Vector3s(2, 3, 0);
	this->IBO_data[2] = Vector3s(1, 5, 6);
	this->IBO_data[3] = Vector3s(6, 2, 1);
	this->IBO_data[4] = Vector3s(7, 6, 5);
	this->IBO_data[5] = Vector3s(5, 4, 7);
	this->IBO_data[6] = Vector3s(4, 0, 3);
	this->IBO_data[7] = Vector3s(3, 7, 4);
	this->IBO_data[8] = Vector3s(4, 5, 1);
	this->IBO_data[9] = Vector3s(1, 0, 4);
	this->IBO_data[10] = Vector3s(3, 2, 6);
	this->IBO_data[11] = Vector3s(6, 7, 3);

#ifdef DEBUG
	for(int i=0; i< this->VBO_size; i++) {
		printf("%d:\t%f,%f,%f\n", i, this->VBO_data[i].x, this->VBO_data[i].y, this->VBO_data[i].z);
	}

	printf("Cube-Rendering vertices set!\n");
	fflush(stdout);
#endif
}
