#include "OBJRenderingObject.h"

void OBJRenderingObject::setColor(Vector3f color) {
	this->color = color;
}

void OBJRenderingObject::initVertices(const char* filename, Vector3f color) {
	int success, i;
	
	this->color = color;
	success = parse_obj_scene(&this->data, filename); // Load OBJ model
	
	if(!success) {
		printf("Could not load file (%s). Exiting.\n", filename);
		exit(1);
	}

	this->VBO_size = this->data.vertex_count;
	this->CBO_size = this->data.vertex_count;
	this->IBO_size = this->data.face_count;

	this->VBO_data = (Vector3f*) calloc (this->VBO_size, sizeof(Vector3f));
	this->CBO_data = (Vector3f*) calloc (this->CBO_size, sizeof(Vector3f));
	this->IBO_data = (Vector3s*) calloc (this->IBO_size, sizeof(Vector3s));

	 /* Vertices */
    for(i=0; i < this->VBO_size; i++) {
		this->VBO_data[i] = Vector3f((GLfloat)(*this->data.vertex_list[i]).e[0], (GLfloat)(*this->data.vertex_list[i]).e[1], (GLfloat)(*this->data.vertex_list[i]).e[2]);
		this->CBO_data[i] = Vector3f((GLfloat)(*this->data.vertex_list[i]).e[0], (GLfloat)(*this->data.vertex_list[i]).e[1], (GLfloat)(*this->data.vertex_list[i]).e[2]);
    }

    /* Indices */
    for(i=0; i < this->IBO_size; i++) {
		this->IBO_data[i] = Vector3s((GLushort)(*this->data.face_list[i]).vertex_index[0],(GLushort)(*this->data.face_list[i]).vertex_index[1],(GLushort)(*this->data.face_list[i]).vertex_index[2]);
    }

#ifdef DEBUG
	for(int i=0; i< this->VBO_size; i++) {
		printf("%d:\t%f,%f,%f\n", i, this->VBO_data[i].x, this->VBO_data[i].y, this->VBO_data[i].z);
	}

	printf("Hexagon-Rendering vertices set!\n");
	fflush(stdout);
#endif
}
