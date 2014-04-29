#include "TriangleRenderingObject.h" 

void TriangleRenderingObject::initVertices(void) {

	this->VBO_size = 3;
	this->CBO_size = 3;
	this->IBO_size = 1;

	this->VBO_data = (Vector3f*) calloc (this->VBO_size, sizeof(Vector3f)); // we need 3 vertices to describe a triangle
	this->CBO_data = (Vector3f*) calloc (this->CBO_size, sizeof(Vector3f)); // colors for each vertex
	this->IBO_data = (Vector3s*) calloc (this->IBO_size, sizeof(Vector3s)); // Indices of 1 triangles

	this->VBO_data[0] = Vector3f(-1.0, -1.0,  0.0);
	this->VBO_data[1] = Vector3f(1.0, -1.0,  0.0);
	this->VBO_data[2] = Vector3f(0.0,  1.0,  0.0);


	this->CBO_data[0] = Vector3f(0.0, 0.0,  1.0);
	this->CBO_data[1] = Vector3f(0.0, 0.0,  0.0);
	this->CBO_data[2] = Vector3f(0.0,  1.0,  1.0);

	this->IBO_data[0] = Vector3s(0, 1, 2);

#ifdef DEBUG
	for(int i=0; i < this->VBO_size; i++) {
		printf("%d:\t%f,%f,%f\n", i, this->VBO_data[i].x, this->VBO_data[i].y, this->VBO_data[i].z);
	}

	printf("Triangle-Rendering vertices set!\n");
	fflush(stdout);
#endif
}
