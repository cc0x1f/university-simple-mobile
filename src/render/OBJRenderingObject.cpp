#include "OBJRenderingObject.h"

void OBJRenderingObject::setColor(glm::vec3 color) {
	this->color = color;
}

void OBJRenderingObject::initVertices(const char* filename, glm::vec3 color) {
	int success, i;
	
	this->color = color;
	success = parse_obj_scene(&this->data, filename); // Load OBJ model
	
	if(!success) {
		printf("Could not load file (%s). Exiting.\n", filename);
		exit(1);
	}

	 /* Vertices */
    for(i=0; i < this->data.vertex_count; i++) {
		this->VBO_data.push_back(glm::vec3((GLfloat)(*this->data.vertex_list[i]).e[0], (GLfloat)(*this->data.vertex_list[i]).e[1], (GLfloat)(*this->data.vertex_list[i]).e[2]));
		this->CBO_data.push_back(this->color);
    }

    /* Indices */
    for(i=0; i < this->data.face_count; i++) {
		this->IBO_data.push_back(Helper::vec3s((GLushort)(*this->data.face_list[i]).vertex_index[0],(GLushort)(*this->data.face_list[i]).vertex_index[1],(GLushort)(*this->data.face_list[i]).vertex_index[2]));
    }
    
    this->calcNormals();
}
