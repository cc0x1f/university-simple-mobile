#include "TriangleRenderingObject.h" 

void TriangleRenderingObject::initVertices(void) {
	this->VBO_data.push_back(glm::vec3(-1.0, -1.0,  0.0));
	this->VBO_data.push_back(glm::vec3(1.0, -1.0,  0.0));
	this->VBO_data.push_back(glm::vec3(0.0,  1.0,  0.0));


	this->CBO_data.push_back(glm::vec3(0.0, 0.0,  1.0));
	this->CBO_data.push_back(glm::vec3(0.0, 0.0,  0.0));
	this->CBO_data.push_back(glm::vec3(0.0,  1.0,  1.0));

	this->IBO_data.push_back(Helper::vec3s(0, 1, 2));
}
