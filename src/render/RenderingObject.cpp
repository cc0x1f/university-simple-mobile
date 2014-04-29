#include "RenderingObject.h" 

void RenderingObject::init(ShaderProgram *shaderProgramm) {
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f)*this->VBO_size, this->VBO_data, GL_STATIC_DRAW);

	glGenBuffers(1, &this->IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Vector3s)*this->IBO_size, this->IBO_data, GL_STATIC_DRAW);

	glGenBuffers(1, &this->CBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->CBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f)*this->CBO_size, this->CBO_data, GL_STATIC_DRAW);

	// init uniform variables
	this->modelUniform = shaderProgramm->getUniformLocation("ModelMatrix");

	// Initialize matrix
	SetIdentityMatrix(this->scaleMatrix);
	SetIdentityMatrix(this->rotationMatrix);
	SetIdentityMatrix(this->translationMatrix);
	SetIdentityMatrix(this->modelMatrix);
	SetIdentityMatrix(this->renderingModelMatrix);
	
	// set rendering type
	this->renderingMode = GL_TRIANGLES;
	//set no parent
	this->parent = NULL;
	
#ifdef DEBUG
	printf("Renderingobject initialized!\n");
	fflush(stdout);
#endif
}

void RenderingObject::setParent(RenderingObject *parent){
	this->parent = parent;
}

RenderingObject *RenderingObject::getParent(void){
	return this->parent;
}

void RenderingObject::calculateModelMatrix(void) {
	Matrix4f scaleRotateMatrix;
	Matrix4f tmpScaleMatrix;
	
	CopyMatrix(this->scaleMatrix, tmpScaleMatrix);
	
	// if we have a parent, recalculate our scale matrix
	if(this->parent != NULL) {
		Matrix4f parentScalingMatrix = this->parent->getScaleMatrix();
		UpdateScaleMatrix(parentScalingMatrix, this->scaleMatrix, tmpScaleMatrix); // set correct scaling =)
	}
	
	// Calculate model matrix.
	MultiplyMatrix(tmpScaleMatrix, this->rotationMatrix, scaleRotateMatrix);
	MultiplyMatrix(this->translationMatrix, scaleRotateMatrix, this->modelMatrix);

	CopyMatrix(this->modelMatrix, this->renderingModelMatrix);
	
#ifdef DEBUG
	PrintMatrix(this->modelMatrix);
#endif
}

Matrix4f RenderingObject::getRenderingMatrix(void) {
	return this->renderingModelMatrix;
}

Matrix4f RenderingObject::getRotationMatrix(void) {
	return this->rotationMatrix;
}

Matrix4f RenderingObject::getScaleMatrix(void) {
	return this->scaleMatrix;
}

Matrix4f RenderingObject::getTranslationMatrix(void) {
	return this->translationMatrix;
}

void RenderingObject::scale(float scale) {
	Matrix4f tmp;
	SetScaleMatrix(scale, tmp);
	MultiplyMatrix(tmp, this->scaleMatrix, this->scaleMatrix);
}

void RenderingObject::rotateX(float angle) {
	Matrix4f tmp;
	SetRotationX(angle, tmp);
	MultiplyMatrix(tmp, this->rotationMatrix, this->rotationMatrix);
}

void RenderingObject::rotateY(float angle) {
	Matrix4f tmp;
	SetRotationY(angle, tmp);
	MultiplyMatrix(tmp, this->rotationMatrix, this->rotationMatrix);
}

void RenderingObject::rotateZ(float angle) {
	Matrix4f tmp;
	SetRotationZ(angle, tmp);
	MultiplyMatrix(tmp, this->rotationMatrix, this->rotationMatrix);
}

void RenderingObject::rotate(float angle, Vector3f axes) {
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
}

void RenderingObject::translateX(float x) {
	Matrix4f tmp;
	SetTranslation(x, 0.0f, 0.0f, tmp);
	MultiplyMatrix(tmp, this->translationMatrix, this->translationMatrix);
}

void RenderingObject::translateY(float y) {
	Matrix4f tmp;
	SetTranslation(0.0f, y, 0.0f, tmp);
	MultiplyMatrix(tmp, this->translationMatrix, this->translationMatrix);
}

void RenderingObject::translateZ(float z) {
	Matrix4f tmp;
	SetTranslation(0.0f, 0.0f, z, tmp);
	MultiplyMatrix(tmp, this->translationMatrix, this->translationMatrix);
}

void RenderingObject::translate(float x, float y, float z) {
	SetTranslation(x, y, z, this->translationMatrix);
}

void RenderingObject::render(void) {
	// set buffers
	glEnableVertexAttribArray(S_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glVertexAttribPointer(S_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(S_COLOR);
	glBindBuffer(GL_ARRAY_BUFFER, this->CBO);
	glVertexAttribPointer(S_COLOR, 3, GL_FLOAT,GL_FALSE, 0, 0);   

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
	GLint size; 
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	
	// calculate the model matrix
	this->calculateModelMatrix();
	
	// if we have a parent, recalculate our model matrix
	if(this->parent != NULL) {
		MultiplyMatrix(this->parent->getRenderingMatrix(), this->modelMatrix, this->renderingModelMatrix);
	}

	// set uniform variables
	glUniformMatrix4fv(this->modelUniform, 1, GL_TRUE, &this->renderingModelMatrix.m[0][0]);

	// draw
	glDrawElements(this->renderingMode, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

	// disable attributes
	glDisableVertexAttribArray(S_POSITION);
	glDisableVertexAttribArray(S_COLOR);
}
