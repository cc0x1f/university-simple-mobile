/******************************************************************
*
* Texture.cpp
*
* Description: Helper routine for loading texture.
* Adapted from texture loading code of the online OpenGL Tutorial:
*
* http://www.opengl-tutorial.org/	
*
* Computer Graphics Proseminar SS 2014
* 
* Interactive Graphics and Simulation Group
* Institute of Computer Science
* University of Innsbruck
*
*******************************************************************/

/* Standard includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../header/Texture.h"

/******************************************************************
*
* LoadTexture
*
* This function loads a BMP texture from the file 'filename';
* it is used to load the shader source code
*
*******************************************************************/

int Texture::load(const char* filename, TextureDataPtr *texture) {
	printf("Reading image %s.\n", filename);

	/* Header data of BMP file */
	unsigned char header[54];
	unsigned int dataPos; 
	unsigned int imageSize;

	/* Open the file */
	FILE* file = fopen(filename,"rb");

	if (!file) {
		printf("%s could not be opened.\n", filename); 
		return 0;
	}

	/* Parse the header (i.e. first 54 bytes) */
	if (fread(header, 1, 54, file) != 54) { 
		printf("Not a correct BMP file.\n");
		fclose (file);
		return 0;
	}

	/* BMP files begin with "BM" */
	if (header[0]!='B' || header[1]!='M') {
		printf("Not a correct BMP file.\n");
		fclose(file);
		return 0;
	}

	/* Make sure file is 24bpp */
	if (*(int*)&(header[0x1E]) !=0) { 
		printf("Not a correct BMP file\n");    
		return 0;
	}

	if (*(int*)&(header[0x1C]) != 24) {
		printf("Not a correct BMP file\n");    
		return 0;
	}

	/* Read image information */
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	texture->width = *(int*)&(header[0x12]);
	texture->height = *(int*)&(header[0x16]);

	/* Guess size if not provided, assuming one byte
		* each for RGB */
	if (imageSize == 0)    
		imageSize = texture->width * texture->height * 3; 

	/* Adjust for BMP header */	
	if (dataPos == 0)      
		dataPos = 54; 

	/* Allocate memory for RGB data */
	texture->data = (unsigned char*) malloc(sizeof(unsigned char) * (imageSize+1));

	/* Read data from file */
	fread(texture->data, 1, imageSize, file);

	fclose (file);
	return 1;
}


