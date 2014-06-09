#include "../../header/render/RenderingObject.h"

void RenderingObject::initUniformAndBuffer(ShaderProgram *shaderProgram) {
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * this->VBO_data.size(), &this->VBO_data[0], GL_STATIC_DRAW);

	glGenBuffers(1, &this->IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Helper::vec3s) * this->IBO_data.size(), &this->IBO_data[0], GL_STATIC_DRAW);

	glGenBuffers(1, &this->UV);
	glBindBuffer(GL_ARRAY_BUFFER, this->UV);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * this->UV_data.size(), &this->UV_data[0], GL_STATIC_DRAW);

	// init uniform variables
	this->modelUniform = shaderProgram->getUniformLocation("ModelMatrix");
	this->specularIntensityUniform = shaderProgram->getUniformLocation("materialSpecularIntensity");
	this->specularPowerUniform = shaderProgram->getUniformLocation("materialSpecularPower");
	this->textureUniform = shaderProgram->getUniformLocation("TextureSampler");
}

void RenderingObject::initTexture(const char *textureFile) {
	// Allocate texture container
	this->texture = (TextureDataPtr*) malloc(sizeof(TextureDataPtr));

	int success = Texture::load(textureFile, this->texture);
	if (!success) {
		printf("Error loading texture. Exiting.\n");
		exit(-1);
	}

	// Create texture name and store in handle
	glGenTextures(1, &TEXTURE);

	// Bind texture
	glBindTexture(GL_TEXTURE_2D, TEXTURE);

	// Load texture image into memory
	glTexImage2D(GL_TEXTURE_2D,	// Target texture
			0,					// Base level
			GL_RGB,				// Each element is RGB triple
			this->texture->width, this->texture->height, 
			0,					// Border should be zero
			GL_BGR,				// Data storage format
			GL_UNSIGNED_BYTE,	// Type of pixel data
			this->texture->data);		// Pointer to image data

	// Set up texturing parameters

	// Repeat texture on edges when tiling
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Linear interpolation for magnification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Trilinear MIP mapping for minification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glGenerateMipmap(GL_TEXTURE_2D); 

	// Note: MIP mapping not visible due to fixed camera
}

void RenderingObject::init(ShaderProgram *shaderProgram) {
	this->initUniformAndBuffer(shaderProgram);
	
	/* initialize temp matrices */
	this->translationMatrix = glm::mat4(1.0f);
	this->scaleMatrix = glm::mat4(1.0f);
	this->rotationMatrix = glm::mat4(1.0f);
	this->modelMatrix = glm::mat4(1.0f);
	this->renderingModelMatrix = glm::mat4(1.0f);
	
	// set rendering type
	this->renderingMode = GL_TRIANGLES;
	
	//set no parent
	this->parent = NULL;
	
	//set material behaviour
	this->specularPower = 0.0f;
	this->specularIntensity = 0.0f;
}

void RenderingObject::setParent(RenderingObject *parent){
	this->parent = parent;
}

RenderingObject *RenderingObject::getParent(void){
	return this->parent;
}

void RenderingObject::calculateModelMatrix(void) {
	glm::mat4 tmpScaleMatrix;
	
	tmpScaleMatrix = this->scaleMatrix;
	
	// if we have a parent, recalculate our scale matrix
	if(this->parent != NULL) {
		glm::mat4 parentScalingMatrix = this->parent->getScaleMatrix();
		tmpScaleMatrix = this->scaleMatrix * glm::inverse(parentScalingMatrix);
	}
	
	this->modelMatrix = this->translationMatrix * this->rotationMatrix * tmpScaleMatrix;
	this->renderingModelMatrix = this->modelMatrix;
}

glm::mat4 RenderingObject::getRenderingMatrix(void) {
	return this->renderingModelMatrix;
}

glm::mat4 RenderingObject::getRotationMatrix(void) {
	return this->rotationMatrix;
}

glm::mat4 RenderingObject::getScaleMatrix(void) {
	return this->scaleMatrix;
}

glm::mat4 RenderingObject::getTranslationMatrix(void) {
	return this->translationMatrix;
}

void RenderingObject::scale(float scale) {
	this->scaleMatrix = glm::scale(glm::mat4(1.0f),glm::vec3(scale)) * this->scaleMatrix;
}

void RenderingObject::rotateX(float angle) {
	angle = angle * M_PI / 180.0;
	this->rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 0.0f, 0.0f)) * this->rotationMatrix;
}

void RenderingObject::rotateY(float angle) {
	angle = angle * M_PI / 180.0;
	this->rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f)) * this->rotationMatrix;
}

void RenderingObject::rotateZ(float angle) {
	angle = angle * M_PI / 180.0;
	this->rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f)) * this->rotationMatrix;
}

void RenderingObject::rotate(float angle, glm::vec3 axes) {
	angle = angle * M_PI / 180.0;
	this->rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, axes) * this->rotationMatrix;
}

void RenderingObject::translateX(float x) {
	this->translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, 0.0f, 0.0f)) * this->translationMatrix;
}

void RenderingObject::translateY(float y) {
	this->translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, y, 0.0f)) * this->translationMatrix;
}

void RenderingObject::translateZ(float z) {
	this->translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, z)) * this->translationMatrix;
}

void RenderingObject::translate(float x, float y, float z) {
	this->translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z)) * this->translationMatrix;
}

// see http://www.opengl.org/wiki/Calculating_a_Surface_Normal
// very helpful!
void RenderingObject::calcNormals(void) {
	
	this->NORMALS_data.resize(this->VBO_data.size());
	std::vector<bool> needsRecalc;
	
	needsRecalc.resize(this->VBO_data.size());
	
	for( unsigned int i = 0; i < this->NORMALS_data.size(); i++ ) {
		this->NORMALS_data[i] = glm::vec3(0); // init with 0 vector
	}
	
	for( unsigned int i = 0; i < needsRecalc.size(); i++ ) {
		needsRecalc[i] = false;
	}
	
	// iterate over each face
	for( unsigned int i = 0; i < this->IBO_data.size(); i++ ) {
		// get the three vertices that make the faces
		glm::vec3 p1 = this->VBO_data[this->IBO_data[i].x];
		glm::vec3 p2 = this->VBO_data[this->IBO_data[i].y];
		glm::vec3 p3 = this->VBO_data[this->IBO_data[i].z];

		glm::vec3 v1 = p2 - p1;
		glm::vec3 v2 = p3 - p1;
		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

		// Store the face's normal for each of the vertices that make up the face.
		if(this->NORMALS_data[this->IBO_data[i].x] != glm::vec3(0)) needsRecalc[this->IBO_data[i].x] = true;
		if(this->NORMALS_data[this->IBO_data[i].y] != glm::vec3(0)) needsRecalc[this->IBO_data[i].y] = true;
		if(this->NORMALS_data[this->IBO_data[i].z] != glm::vec3(0)) needsRecalc[this->IBO_data[i].z] = true;

		this->NORMALS_data[this->IBO_data[i].x] += normal;
		this->NORMALS_data[this->IBO_data[i].y] += normal;
		this->NORMALS_data[this->IBO_data[i].z] += normal;
	}
	
	for( unsigned int i = 0; i < needsRecalc.size(); i++ ) {
		if(needsRecalc[i]) {
			this->NORMALS_data[i] = glm::normalize(this->NORMALS_data[i]);
		}
	}
	
	glGenBuffers(1, &this->NORMALS);
	glBindBuffer(GL_ARRAY_BUFFER, this->NORMALS);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * this->NORMALS_data.size(), &this->NORMALS_data[0], GL_STATIC_DRAW);
}

void RenderingObject::setMatSpecularIntensity(float intensity) {
	this->specularIntensity = intensity;
}

void RenderingObject::setMatSpecularPower(float power) {
	this->specularPower = power;
}

void RenderingObject::render(void) {
	// set buffers
	glEnableVertexAttribArray(S_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glVertexAttribPointer(S_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(S_UV);
	glBindBuffer(GL_ARRAY_BUFFER, this->UV);
	glVertexAttribPointer(S_UV, 3, GL_FLOAT,GL_FALSE, 0, 0);   

	if(this->renderingMode == GL_TRIANGLES) { // we do not calculate normals for lines... to much work ;)
		glEnableVertexAttribArray(S_NORMALS);
		glBindBuffer(GL_ARRAY_BUFFER, this->NORMALS);
		glVertexAttribPointer(S_NORMALS, 3, GL_FLOAT,GL_FALSE, 0, 0);
	}
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
	GLint size; 
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	
	// calculate the model matrix
	this->calculateModelMatrix();
	
	// if we have a parent, recalculate our model matrix
	if(this->parent != NULL) {
		this->renderingModelMatrix = this->parent->getRenderingMatrix() * this->modelMatrix;
	}
	
	// Texture stuff
	//Activate first (and only) texture unit
	glActiveTexture(GL_TEXTURE0);

	// Bind current texture 
	glBindTexture(GL_TEXTURE_2D, TEXTURE);

	// Set location of uniform sampler variable 
	glUniform1i(this->textureUniform, 0);

	// set uniform variables
	glUniformMatrix4fv(this->modelUniform, 1, GL_FALSE, glm::value_ptr(this->renderingModelMatrix));
	glUniform1f(this->specularIntensityUniform, this->specularIntensity);
	glUniform1f(this->specularPowerUniform, this->specularPower);

	// draw
	glDrawElements(this->renderingMode, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

	// disable attributes
	glDisableVertexAttribArray(S_POSITION);
	glDisableVertexAttribArray(S_UV);
}
