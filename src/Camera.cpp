#include "Camera.h" 

void Camera::init(ShaderProgram *shaderProgramm) {
	// init uniform variables
	this->projectionUniform = shaderProgramm->getUniformLocation("ProjectionMatrix");
	this->viewUniform = shaderProgramm->getUniformLocation("ViewMatrix");
	this->autoRotate = true;
	
	/* Initialize matrices */
	SetIdentityMatrix(this->scaleMatrix);
	SetIdentityMatrix(this->rotationMatrix);
	SetIdentityMatrix(this->translationMatrix);
	SetIdentityMatrix(this->projectionMatrix);
	SetIdentityMatrix(this->viewMatrix);
	
	/* Set projection transform */
	float fovy = 45.0;
	float aspect = 1.0; 
	float nearPlane = 1.0; 
	float farPlane = 50.0;
	SetPerspectiveMatrix(fovy, aspect, nearPlane, farPlane, this->projectionMatrix);

	/* Set viewing transform */
	float camera_disp = -10.0;
	SetTranslation(0.0, 0.0, camera_disp, this->translationMatrix);
	this->calculateViewMatrix();
	
#ifdef DEBUG
	printf("Camera initialized!\n");
	fflush(stdout);
#endif
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
	Matrix4f scaleRotateMatrix;
	
	// Calculate model matrix.
	MultiplyMatrix(this->scaleMatrix, this->rotationMatrix, scaleRotateMatrix);
	MultiplyMatrix(this->translationMatrix, scaleRotateMatrix, this->viewMatrix);

#ifdef DEBUG
	PrintMatrix(this->viewMatrix);
#endif
}

void Camera::zoom(float scale) {
	SetScaleMatrix(scale, this->scaleMatrix);
	this->calculateViewMatrix();
}

void Camera::rotateX(float angle) {
	Matrix4f tmp;
	SetRotationX(angle, tmp);
	MultiplyMatrix(tmp, this->rotationMatrix, this->rotationMatrix);
	this->calculateViewMatrix();
}

void Camera::rotateY(float angle) {
	Matrix4f tmp;
	SetRotationY(angle, tmp);
	MultiplyMatrix(tmp, this->rotationMatrix, this->rotationMatrix);
	this->calculateViewMatrix();
}

void Camera::rotateZ(float angle) {
	Matrix4f tmp;
	SetRotationZ(angle, tmp);
	MultiplyMatrix(tmp, this->rotationMatrix, this->rotationMatrix);
	this->calculateViewMatrix();
}

void Camera::rotate(float angle, Vector3f axes) {
	Matrix4f tmp;
	Matrix4f tmp2;
	
	SetIdentityMatrix(tmp);
	
	if(axes.x == 1.0f) {
		SetRotationX(angle, tmp2);
		MultiplyMatrix(tmp2, tmp, tmp);
	}
	if(axes.y == 1.0f) {
		SetRotationY(angle, tmp2);
		MultiplyMatrix(tmp2, tmp, tmp);
	}
	if(axes.z == 1.0f) {
		SetRotationZ(angle, tmp2);
		MultiplyMatrix(tmp2, tmp, tmp);
	}
	
	MultiplyMatrix(tmp, this->rotationMatrix, this->rotationMatrix);
		
	this->calculateViewMatrix();
}

void Camera::translateX(float x) {
	Matrix4f tmp;
	SetTranslation(x, 0.0f, 0.0f, tmp);
	MultiplyMatrix(tmp, this->translationMatrix, this->translationMatrix);
	this->calculateViewMatrix();
}

void Camera::translateY(float y) {
	Matrix4f tmp;
	SetTranslation(0.0f, y, 0.0f, tmp);
	MultiplyMatrix(tmp, this->translationMatrix, this->translationMatrix);
	this->calculateViewMatrix();
}

void Camera::translateZ(float z) {
	Matrix4f tmp;
	SetTranslation(0.0f, 0.0f, z, tmp);
	MultiplyMatrix(tmp, this->translationMatrix, this->translationMatrix);
	this->calculateViewMatrix();
}

void Camera::translate(float x, float y, float z) {
	SetTranslation(x, y, z, this->translationMatrix);
	this->calculateViewMatrix();
}

void Camera::update(void) {    
	// rotate the cam
	if(this->autoRotate == true) {
		this->rotateY(0.1f);
	}
}

void Camera::render(void) {    
	// set uniform variables
	glUniformMatrix4fv(this->projectionUniform, 1, GL_TRUE, &this->projectionMatrix.m[0][0]);
	glUniformMatrix4fv(this->viewUniform, 1, GL_TRUE, &this->viewMatrix.m[0][0]);
}
