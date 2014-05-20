#include "../header/Camera.h"

void Camera::initUniformAndBuffer(ShaderProgram *shaderProgram) {
	// init uniform variables
	this->projectionUniform = shaderProgram->getUniformLocation("ProjectionMatrix");
	this->viewUniform = shaderProgram->getUniformLocation("ViewMatrix");
}

void Camera::init(ShaderProgram *shaderProgram) {
	this->initUniformAndBuffer(shaderProgram);
	this->autoRotate = true;
	this->autoRotated = 0;
	
	/* Initialize matrices */
	/* Set projection transform */
	float fovy = 45.0 * M_PI / 180.0;
	float aspect = 1.0; 
	float nearPlane = 1.0; 
	float farPlane = 50.0;
	this->projectionMatrix = glm::perspective(fovy, aspect, nearPlane, farPlane);
	
	/* Set viewing transform */  
	this->viewMatrix = glm::lookAt(glm::vec3(0,0,10),    /* Eye vector */
				 glm::vec3(0,0,0),     /* Viewing center */
				 glm::vec3(0,1,-1) );  /* Up vector */
	
	/* initialize temp matrices */
	translationMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
	
	/* Translate */
	float camera_disp = -10.0f;
    this->translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, camera_disp));
	
	this->calculateViewMatrix();
}

void Camera::setAutoRotate(bool autoRotate) {
	this->autoRotate = autoRotate;
}

bool Camera::getAutoRotate() {
	return this->autoRotate;
}

void Camera::toggleAutoRotate() {
	this->autoRotate = !this->autoRotate;
}

void Camera::calculateViewMatrix(void) {	
	this->viewMatrix = this->translationMatrix * this->rotationMatrix * this->scaleMatrix;
}

void Camera::zoom(float scale) {
	this->scaleMatrix = glm::scale(glm::mat4(1.0f),glm::vec3(scale));
	this->calculateViewMatrix();
}

void Camera::rotateX(float angle) {
	angle = angle * M_PI / 180.0;
	this->rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 0.0f, 0.0f)) * this->rotationMatrix;
	this->calculateViewMatrix();
}

void Camera::rotateY(float angle) {
	angle = angle * M_PI / 180.0;
	this->rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f)) * this->rotationMatrix;
	this->calculateViewMatrix();
}

void Camera::rotateZ(float angle) {
	angle = angle * M_PI / 180.0;
	this->rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f)) * this->rotationMatrix;
	this->calculateViewMatrix();
}

void Camera::rotate(float angle, glm::vec3 axes) {
	angle = angle * M_PI / 180.0;
	this->rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, axes) * this->rotationMatrix;
	this->calculateViewMatrix();
}

void Camera::translateX(float x) {
	this->translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, 0.0f, 0.0f)) * this->translationMatrix;
	this->calculateViewMatrix();
}

void Camera::translateY(float y) {
	this->translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, y, 0.0f)) * this->translationMatrix;
	this->calculateViewMatrix();
}

void Camera::translateZ(float z) {
	this->translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, z)) * this->translationMatrix;
	this->calculateViewMatrix();
}

void Camera::translate(float x, float y, float z) {
	this->translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z)) * this->translationMatrix;
	this->calculateViewMatrix();
}

void Camera::update(void) {    
	// rotate the cam
	if(this->autoRotate == true) {
		this->autoRotated += 0.01f;
		
		if(this->autoRotated >= 0 && this->autoRotated < 55.0f) {
			this->rotateY(0.01f);
		} else if (this->autoRotated >= 55.0f && this->autoRotated < 160.0f) {
			this->rotateY(-0.01f);
		} else if (this->autoRotated >= 160.0f && this->autoRotated < 265.0f){
			this->rotateY(0.01f);
		} else {
			this->autoRotated = 55;
		}
	}
}

void Camera::render(void) {    
	// set uniform variables
	glUniformMatrix4fv(this->projectionUniform, 1, GL_FALSE, glm::value_ptr(this->projectionMatrix));
	glUniformMatrix4fv(this->viewUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
}

glm::mat4 Camera::getProjectionMatrix(void) {
	return this->projectionMatrix;
}

glm::mat4 Camera::getViewMatrix(void) {
	return this->viewMatrix;
}

glm::mat4 Camera::getRotationMatrix(void) {
	return this->rotationMatrix;
}

glm::mat4 Camera::getScaleMatrix(void) {
	return this->scaleMatrix;
}

glm::mat4 Camera::getTranslationMatrix(void) {
	return this->translationMatrix;
}
