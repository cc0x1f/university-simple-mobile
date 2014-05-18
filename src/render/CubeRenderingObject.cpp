#include "CubeRenderingObject.h" 

void CubeRenderingObject::initVertices(glm::vec3 color) {
	
	this->VBO_data.push_back(glm::vec3(-1.0, -1.0,  1.0));
	this->VBO_data.push_back(glm::vec3(1.0, -1.0,  1.0));
	this->VBO_data.push_back(glm::vec3(1.0,  1.0,  1.0));
	this->VBO_data.push_back(glm::vec3(-1.0,  1.0,  1.0));
	this->VBO_data.push_back(glm::vec3(-1.0, -1.0, -1.0));
	this->VBO_data.push_back(glm::vec3(1.0, -1.0, -1.0));
	this->VBO_data.push_back(glm::vec3(1.0,  1.0, -1.0));
	this->VBO_data.push_back(glm::vec3(-1.0,  1.0, -1.0));


	for(int i=0; i<8; i++) {
		this->CBO_data.push_back(color);
	}

	this->IBO_data.push_back(Helper::vec3s(0, 1, 2));
	this->IBO_data.push_back(Helper::vec3s(2, 3, 0));
	this->IBO_data.push_back(Helper::vec3s(1, 5, 6));
	this->IBO_data.push_back(Helper::vec3s(6, 2, 1));
	this->IBO_data.push_back(Helper::vec3s(7, 6, 5));
	this->IBO_data.push_back(Helper::vec3s(5, 4, 7));
	this->IBO_data.push_back(Helper::vec3s(4, 0, 3));
	this->IBO_data.push_back(Helper::vec3s(3, 7, 4));
	this->IBO_data.push_back(Helper::vec3s(4, 5, 1));
	this->IBO_data.push_back(Helper::vec3s(1, 0, 4));
	this->IBO_data.push_back(Helper::vec3s(3, 2, 6));
	this->IBO_data.push_back(Helper::vec3s(6, 7, 3));
	
	this->calcNormals();
	
	#ifdef DEBUG
	for(uint i=0; i< this->NORMALS_data.size(); i++) {
		printf("%d:\t%f,%f,%f\n", i, this->NORMALS_data.at(i).x, this->NORMALS_data.at(i).y, this->NORMALS_data.at(i).z);
	}

	printf("Printed cube normals!\n");
	fflush(stdout);
	#endif
}
