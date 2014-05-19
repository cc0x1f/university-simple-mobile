/* Standard includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../header/ShaderProgram.h"

/******************************************************************
*
* AddShader
*
* This function creates and adds individual shaders
*
*******************************************************************/
void ShaderProgram::AddShader(const char* ShaderCode, GLenum ShaderType) {
	/* Create shader object */
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
		exit(0);
	}

	/* Associate shader source code string with shader object */
	glShaderSource(ShaderObj, 1, &ShaderCode, NULL);

	GLint success = 0;
	GLchar InfoLog[1024];

	/* Compile shader source code */
	glCompileShader(ShaderObj);
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		exit(1);
	}

	/* Associate shader with shader program */
	glAttachShader(this->shaderProgram, ShaderObj);
} 

/******************************************************************
*
* LoadShader
*
* This function reads and returns a string from the file 'filename';
* it is used to load the shader source code
*
*******************************************************************/
const char* ShaderProgram::LoadShader(const char* filename) {
#ifdef __MINGW32__
	FILE* infile = fopen(filename, "rb");
#elif WIN32
	FILE* infile;
	fopen_s(&infile, filename, "rb");
#else
	FILE* infile = fopen(filename, "rb");
#endif // WIN32

	if (!infile) {
		fprintf(stderr, "Could not open shader file %s\n", filename);
		exit(0);
	}

	fseek(infile, 0, SEEK_END);
	int len = ftell(infile);
	fseek(infile, 0, SEEK_SET);

	char* source = (char *) malloc(sizeof(char) * (len+1));

	fread(source, 1, len, infile);
	fclose(infile);

	source[len] = 0;

	return (const char*)(source);
}

/******************************************************************
*
* setVertexShader
*
* Set the filename for the vertex shader
*
*******************************************************************/
void ShaderProgram::setVertexShader(const char* filename){
	this->VertexShaderFilename = filename;
}

/******************************************************************
*
* setFragmentShader
*
* Set the filename for the fragment shader
*
*******************************************************************/
void ShaderProgram::setFragmentShader(const char* filename){
	this->FragmentShaderFilename = filename;
}

/******************************************************************
*
* create
*
* Create the final ShaderProgramm
*
*******************************************************************/
void ShaderProgram::create(void) {
	/* Allocate shader object */
	this->shaderProgram = glCreateProgram();

	if (this->shaderProgram == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	/* Load shader code from file */
	this->VertexShaderString = this->LoadShader(this->VertexShaderFilename);
	this->FragmentShaderString = this->LoadShader(this->FragmentShaderFilename);

	/* Separately add vertex and fragment shader to program */
	this->AddShader(this->VertexShaderString, GL_VERTEX_SHADER);
	this->AddShader(this->FragmentShaderString, GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024];

	/* Link shader code into executable shader program */
	glLinkProgram(this->shaderProgram);

	/* Check results of linking step */
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &Success);

	if (Success == 0) {
		glGetProgramInfoLog(this->shaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	/* Check if shader program can be executed */ 
	glValidateProgram(this->shaderProgram);
	glGetProgramiv(this->shaderProgram, GL_VALIDATE_STATUS, &Success);

	if (!Success) {
		glGetProgramInfoLog(this->shaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	/* Put linked shader program into drawing pipeline */
	glUseProgram(this->shaderProgram);
}

/******************************************************************
*
* getUniformLocation
*
* return the location to a uniform variable
*
*******************************************************************/
GLuint ShaderProgram::getUniformLocation(const char* varname) {
	GLint uniform = glGetUniformLocation(this->shaderProgram, varname);
	if (uniform == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", varname);
		exit(-1);
	}
	return uniform;
}
