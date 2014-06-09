#include "../../header/render/BillboardRenderingObject.h"

void BillboardRenderingObject::initVertices(void) {
	this->VBO_data.push_back(0.0f);	this->VBO_data.push_back(0.0f);	this->VBO_data.push_back(0.0f);
	this->VBO_data.push_back(0.0f);	this->VBO_data.push_back(1.0f);	this->VBO_data.push_back(0.0f);
	this->VBO_data.push_back(1.0f);	this->VBO_data.push_back(1.0f);	this->VBO_data.push_back(0.0f);
	this->VBO_data.push_back(1.0f);	this->VBO_data.push_back(0.0f);	this->VBO_data.push_back(0.0f);
		
	this->UV_data.push_back(0.0f);	this->UV_data.push_back(0.0f);
	this->UV_data.push_back(0.0f);	this->UV_data.push_back(1.0f);
	this->UV_data.push_back(1.0f);	this->UV_data.push_back(1.0f);
	this->UV_data.push_back(1.0f);	this->UV_data.push_back(0.0f);
		
	this->IBO_data.push_back(0);	this->IBO_data.push_back(1);	this->IBO_data.push_back(3);
	this->IBO_data.push_back(1);	this->IBO_data.push_back(2);	this->IBO_data.push_back(3);
	
	// set animation animationtime
	this->animationTime = 100; // milliseconds
	
	// init animation step 
	this->animationStep = 0;
	
	// Define normals
	this->NORMALS_data.resize(this->VBO_data.size());
	for (unsigned int i = 0; i < this->VBO_data.size(); i = i+3){
		this->NORMALS_data[i] = 0.0f;
		this->NORMALS_data[i+1] = 0.0f;
		this->NORMALS_data[i+2] = 1.0f;
	}
}

void BillboardRenderingObject::update(void) {
	int now = glutGet(GLUT_ELAPSED_TIME);
	if(now - this->lastTimestamp < this->animationTime) {
		return;
	}
	this->lastTimestamp = now;
	
	float stepSize = 0.25f; // imgSize/4 = 0.25 normalized;
	
	if(this->animationStep > 15) {
		this->animationStep = 0;
	}
	
	this->UV_data.clear();
	
	switch(this->animationStep) {
		case 0:
		case 1:
		case 2:
		case 3:
			this->UV_data.push_back(0.0f); this->UV_data.push_back(0.75f - stepSize);
			this->UV_data.push_back(0.25f); this->UV_data.push_back(1.0f - stepSize);
			this->UV_data.push_back(0.25f); this->UV_data.push_back(0.75f - stepSize);
			this->UV_data.push_back(0.0f); this->UV_data.push_back(1.0f - stepSize);
			break;
		case 4:
		case 5:
		case 6:
		case 7:
			this->UV_data.push_back(0.25f); this->UV_data.push_back(1.0f - (stepSize - 4));
			this->UV_data.push_back(0.5f); this->UV_data.push_back(1.0f - (stepSize - 4));
			this->UV_data.push_back(0.5f); this->UV_data.push_back(0.75f - (stepSize - 4));
			this->UV_data.push_back(0.25f); this->UV_data.push_back(0.75f - (stepSize - 4));
			break;
		case 8:
		case 9:
		case 10:
		case 11:
			this->UV_data.push_back(0.5f); this->UV_data.push_back(1.0f - (stepSize - 8));
			this->UV_data.push_back(0.75f); this->UV_data.push_back(1.0f - (stepSize - 8));
			this->UV_data.push_back(0.75f); this->UV_data.push_back(0.75f - (stepSize - 8));
			this->UV_data.push_back(0.5f); this->UV_data.push_back(0.75f - (stepSize - 8));
			break;
		case 12:
		case 13:
		case 14:
		case 15:
			this->UV_data.push_back(0.75f); this->UV_data.push_back(1.0f - (stepSize - 12));
			this->UV_data.push_back(0.1f); this->UV_data.push_back(1.0f - (stepSize - 12));
			this->UV_data.push_back(0.1f); this->UV_data.push_back(0.75f - (stepSize - 12));
			this->UV_data.push_back(0.75f); this->UV_data.push_back(0.75f - (stepSize - 12));
			break;
		default:
			break;
	}
	
	this->animationStep++;
	
	//glGenBuffers(1, &this->UV);
	glBindBuffer(GL_ARRAY_BUFFER, this->UV);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->UV_data.size(), &this->UV_data[0], GL_STATIC_DRAW);
}

void BillboardRenderingObject::setCam(Camera *cam){
	this->cam = cam;
}

void BillboardRenderingObject::render(void) {
	
	// animate
	this->update();
	
	// set buffers
	glEnableVertexAttribArray(S_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glVertexAttribPointer(S_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(S_UV);
	glBindBuffer(GL_ARRAY_BUFFER, this->UV);
	glVertexAttribPointer(S_UV, 3, GL_FLOAT,GL_FALSE, 0, 0);   

	glEnableVertexAttribArray(S_NORMALS);
	glBindBuffer(GL_ARRAY_BUFFER, this->NORMALS);
	glVertexAttribPointer(S_NORMALS, 3, GL_FLOAT,GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
	GLint size; 
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	
	// calculate the model matrix
	this->calculateModelMatrix();
		
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
