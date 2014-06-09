#include "../../header/render/LineRenderingObject.h"

void LineRenderingObject::initVertices() {
	this->VBO_data.push_back(0.0f);
	this->VBO_data.push_back(0.0f);
	this->VBO_data.push_back(0.0f);
	this->VBO_data.push_back(0.0f);
	this->VBO_data.push_back(1.0f);
	this->VBO_data.push_back(0.0f);
		
	this->UV_data.push_back(0.0f);
	this->UV_data.push_back(0.0f);
	this->UV_data.push_back(0.0f);
	this->UV_data.push_back(0.0f);
		
	this->IBO_data.push_back(0);
	this->IBO_data.push_back(1);
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
