#include "GridRenderingObject.h" 

void GridRenderingObject::initVertices(int linesx, int linesy, Vector3f color) {
	this->VBO_size = (2*linesx) + (2*linesy) + 4; // +4 for the last 2 lines
	this->CBO_size = (2*linesx) + (2*linesy) + 4;
	this->IBO_size = linesx + linesy + 2;

	this->VBO_data = (Vector3f*) calloc (this->VBO_size, sizeof(Vector3f)); // we need 3 vertices to describe a triangle
	this->CBO_data = (Vector3f*) calloc (this->CBO_size, sizeof(Vector3f)); // colors for each vertex
	this->IBO_data = (Vector2s*) calloc (this->IBO_size, sizeof(Vector2s));

	int i;
	int j;
	for(i = 0, j = 0; i <= linesx*2; i+=2, j++) {
		this->VBO_data[i] = Vector3f(i/(2.0*linesx), 0.0,  0.0);
		this->VBO_data[i+1] = Vector3f(i/(2.0*linesx), 1.0,  0.0);
		
		this->CBO_data[i] = color;
		this->CBO_data[i+1] = color;
		
		this->IBO_data[j] = Vector2s(i, i+1);

	}

	int lim = i + (linesy*2);
	for(; i <= lim ; i+=2, j++) {
		this->VBO_data[i] = Vector3f(0.0, (i-2)/(2.0*linesy) - 1,  0.0);
		this->VBO_data[i+1] = Vector3f(1.0, (i-2)/(2.0*linesy) - 1,  0.0);
		
		this->CBO_data[i] = color;
		this->CBO_data[i+1] = color;
		
		this->IBO_data[j] = Vector2s(i, i+1);
	}

#ifdef DEBUG
	for(int i=0; i <= this->VBO_size; i++) {
		printf("%d:\t%f,%f,%f\n", i, this->VBO_data[i].x, this->VBO_data[i].y, this->VBO_data[i].z);
	}

	printf("Grid-Rendering vertices set!\n");
	fflush(stdout);
#endif
}

void GridRenderingObject::init(ShaderProgram *shaderProgramm) {
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f)*this->VBO_size, this->VBO_data, GL_STATIC_DRAW);

	glGenBuffers(1, &this->IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Vector2s)*this->IBO_size, this->IBO_data, GL_STATIC_DRAW);

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

	// set rendering type
	this->renderingMode = GL_LINES;
	//set no parent
	this->parent = NULL;

#ifdef DEBUG
	printf("Grid-Renderingobject initialized!\n");
	fflush(stdout);
#endif
}
