#include "GridRenderingObject.h" 

void GridRenderingObject::initVertices(int linesx, int linesy, glm::vec3 color) {
	int i;
	int j;
	for(i = 0, j = 0; i <= linesx*2; i+=2, j++) {
		this->VBO_data.push_back(glm::vec3(i/(2.0*linesx), 0.0,  0.0));
		this->VBO_data.push_back(glm::vec3(i/(2.0*linesx), 1.0,  0.0));
		
		this->CBO_data.push_back(color);
		this->CBO_data.push_back(color);
		
		this->IBO_data.push_back(Helper::vec2s(i, i+1));

	}

	int lim = i + (linesy*2);
	for(; i <= lim ; i+=2, j++) {
		this->VBO_data.push_back(glm::vec3(0.0, (i-2)/(2.0*linesy) - 1,  0.0));
		this->VBO_data.push_back(glm::vec3(1.0, (i-2)/(2.0*linesy) - 1,  0.0));
		
		this->CBO_data.push_back(color);
		this->CBO_data.push_back(color);
		
		this->IBO_data.push_back(Helper::vec2s(i, i+1));
	}
}

void GridRenderingObject::init(ShaderProgram *shaderProgramm) {
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * this->VBO_data.size(), &this->VBO_data[0], GL_STATIC_DRAW);

	glGenBuffers(1, &this->IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Helper::vec2s) * this->IBO_data.size(), &this->IBO_data[0], GL_STATIC_DRAW);

	glGenBuffers(1, &this->CBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->CBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * this->CBO_data.size(), &this->CBO_data[0], GL_STATIC_DRAW);

	// init uniform variables
	this->modelUniform = shaderProgramm->getUniformLocation("ModelMatrix");

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
