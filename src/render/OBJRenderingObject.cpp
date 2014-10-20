#include "../../header/render/OBJRenderingObject.h"

void OBJRenderingObject::initVertices(const char* filename) {
	int i = 0; // only use the first 
	
	std::string err = tinyobj::LoadObj(this->shapes, filename, NULL);
	
	if (!err.empty()) {
    	printf("Could not load file (%s): %s Exiting.\n", filename, err.c_str());
		exit(1);
	}

	this->VBO_data.swap(shapes[i].mesh.positions);
	this->UV_data.swap(shapes[i].mesh.texcoords);
	this->IBO_data.swap(shapes[i].mesh.indices);
	this->NORMALS_data.swap(shapes[i].mesh.normals);
}
