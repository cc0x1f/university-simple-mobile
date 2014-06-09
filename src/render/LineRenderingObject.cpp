#include "../../header/render/LineRenderingObject.h"

void LineRenderingObject::initVertices() {
	this->VBO_data.push_back(glm::vec3(0.0f, 0.0f,  0.0f));
	this->VBO_data.push_back(glm::vec3(0.0f, 1.0f,  0.0f));
		
	this->UV_data.push_back(glm::vec2(0.0f, 0.0f));
	this->UV_data.push_back(glm::vec2(1.0f, 1.0f));
		
	this->IBO_data.push_back(Helper::vec2s(0, 1));
}

void LineRenderingObject::initUniformAndBuffer(ShaderProgram *shaderProgram) {
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * this->VBO_data.size(), &this->VBO_data[0], GL_STATIC_DRAW);

	glGenBuffers(1, &this->IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Helper::vec2s) * this->IBO_data.size(), &this->IBO_data[0], GL_STATIC_DRAW);

	glGenBuffers(1, &this->UV);
	glBindBuffer(GL_ARRAY_BUFFER, this->UV);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * this->UV_data.size(), &this->UV_data[0], GL_STATIC_DRAW);

	// init uniform variables
	this->modelUniform = shaderProgram->getUniformLocation("ModelMatrix");
}

void LineRenderingObject::init(ShaderProgram *shaderProgram) {
	this->initUniformAndBuffer(shaderProgram);
	
	// Initialize matrix
	this->translationMatrix = glm::mat4(1.0f);
	this->scaleMatrix = glm::mat4(1.0f);
	this->rotationMatrix = glm::mat4(1.0f);
	this->modelMatrix = glm::mat4(1.0f);
	this->renderingModelMatrix = glm::mat4(1.0f);

	// set rendering type
	this->renderingMode = GL_LINES;
	//set no parent
	this->parent = NULL;
}
