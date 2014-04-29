/******************************************************************
*
* Matrix.c
*
* Description: Helper routine for matrix computations.
*
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
#include <math.h>
#include "GlHelper.h"

/******************************************************************
*
* SetIdentityMatrix
*
*******************************************************************/

void SetIdentityMatrix(Matrix4f &identity) {
	identity.m[0][0] = 1.0f; identity.m[0][1] = 0.0f; identity.m[0][2] = 0.0f; identity.m[0][3] = 0.0f;
	identity.m[1][0] = 0.0f; identity.m[1][1] = 1.0f; identity.m[1][2] = 0.0f; identity.m[1][3] = 0.0f;
	identity.m[2][0] = 0.0f; identity.m[2][1] = 0.0f; identity.m[2][2] = 1.0f; identity.m[2][3] = 0.0f;
	identity.m[3][0] = 0.0f; identity.m[3][1] = 0.0f; identity.m[3][2] = 0.0f; identity.m[3][3] = 1.0f;
}

/******************************************************************
*
* SetScaleMatrix
*
*******************************************************************/

void SetScaleMatrix(float scale, Matrix4f &identity) {
	identity.m[0][0] = scale; identity.m[0][1] = 0.0f; identity.m[0][2] = 0.0f; identity.m[0][3] = 0.0f;
	identity.m[1][0] = 0.0f; identity.m[1][1] = scale; identity.m[1][2] = 0.0f; identity.m[1][3] = 0.0f;
	identity.m[2][0] = 0.0f; identity.m[2][1] = 0.0f; identity.m[2][2] = scale; identity.m[2][3] = 0.0f;
	identity.m[3][0] = 0.0f; identity.m[3][1] = 0.0f; identity.m[3][2] = 0.0f; identity.m[3][3] = 1.0f;
}

/******************************************************************
*
* UpdateScaleMatrix
*
*******************************************************************/

void UpdateScaleMatrix(Matrix4f old, Matrix4f newScale, Matrix4f &result) {
	result.m[0][0] = newScale.m[0][0] / old.m[0][0];	
	result.m[1][1] = newScale.m[1][1] / old.m[1][1];	
	result.m[2][2] = newScale.m[2][2] / old.m[2][2];
}

/******************************************************************
*
* SetRotationX
*
*******************************************************************/

void SetRotationX(float anglex, Matrix4f &identity) {
	anglex = M_PI/180 * anglex;   /* Conversion angle from degree to radians */

	identity.m[0][0] = 1.0f; identity.m[0][1] = 0.0f; identity.m[0][2] = 0.0f; identity.m[0][3] = 0.0f;
	identity.m[1][0] = 0.0f; identity.m[1][1] = cosf(anglex); identity.m[1][2] = -sinf(anglex); identity.m[1][3] = 0.0f;
	identity.m[2][0] = 0.0f; identity.m[2][1] = sinf(anglex); identity.m[2][2] = cosf(anglex); identity.m[2][3] = 0.0f;
	identity.m[3][0] = 0.0f; identity.m[3][1] = 0.0f; identity.m[3][2] = 0.0f; identity.m[3][3] = 1.0f;
}


/******************************************************************
*
* SetRotationY
*
*******************************************************************/

void SetRotationY(float angley, Matrix4f &identity) {
	angley = M_PI/180 * angley;   /* Conversion angle from degree to radians */

	identity.m[0][0] = cosf(angley); identity.m[0][1] = 0.0f; identity.m[0][2] = sinf(angley); identity.m[0][3] = 0.0f;
	identity.m[1][0] = 0.0f; identity.m[1][1] = 1.0f; identity.m[1][2] = 0.0f; identity.m[1][3] = 0.0f;
	identity.m[2][0] = -sinf(angley); identity.m[2][1] = 0.0f; identity.m[2][2] = cosf(angley); identity.m[2][3] = 0.0f;
	identity.m[3][0] = 0.0f; identity.m[3][1] = 0.0f; identity.m[3][2] = 0.0f; identity.m[3][3] = 1.0f;
}


/******************************************************************
*
* SetRotationZ
*
*******************************************************************/

void SetRotationZ(float anglez, Matrix4f &identity) {
	anglez = M_PI/180 * anglez;   /* Conversion angle from degree to radian */

	identity.m[0][0] = cosf(anglez); identity.m[0][1] = -sinf(anglez); identity.m[0][2] = 0.0f; identity.m[0][3] = 0.0f;
	identity.m[1][0] = sinf(anglez); identity.m[1][1] = cosf(anglez); identity.m[1][2] = 0.0f; identity.m[1][3] = 0.0f;
	identity.m[2][0] = 0.0f; identity.m[2][1] = 0.0f; identity.m[2][2] = 1.0f; identity.m[2][3] = 0.0f;
	identity.m[3][0] = 0.0f; identity.m[3][1] = 0.0f; identity.m[3][2] = 0.0f; identity.m[3][3] = 1.0f;
}


/******************************************************************
*
* SetTranslation
*
*******************************************************************/

void SetTranslation(float x, float y, float z, Matrix4f &identity) {
	identity.m[0][0] = 1.0f; identity.m[0][1] = 0.0f; identity.m[0][2] = 0.0f; identity.m[0][3] = x;
	identity.m[1][0] = 0.0f; identity.m[1][1] = 1.0f; identity.m[1][2] = 0.0f; identity.m[1][3] = y;
	identity.m[2][0] = 0.0f; identity.m[2][1] = 0.0f; identity.m[2][2] = 1.0f; identity.m[2][3] = z;
	identity.m[3][0] = 0.0f; identity.m[3][1] = 0.0f; identity.m[3][2] = 0.0f; identity.m[3][3] = 1.0f;
}


/******************************************************************
*
* MultiplyMatrix
*
*******************************************************************/

void MultiplyMatrix(Matrix4f m1, Matrix4f m2, Matrix4f &result) {
	int i, j, k;

	for (i=0; i<4 ;i++){
		for(j=0; j<4 ;j++){
			float sum = 0.0;
			for(k=0; k<4 ;k++){
				sum += m1.m[i][k] * m2.m[k][j];
			}
			result.m[i][j] = sum;
		}
	}
}


/******************************************************************
*
* SetPerspectiveMatrix
*
*******************************************************************/

void SetPerspectiveMatrix(float fov, float aspect, float nearPlane, float farPlane, Matrix4f &identity) {
	float f = 1.0 / tan(fov * 3.1415926/360.0);
	float c1 = -(farPlane + nearPlane) / (farPlane - nearPlane);
	float c2 = -(2.0 * farPlane * nearPlane) / (farPlane - nearPlane);

	identity.m[0][0] = f/aspect; identity.m[0][1] = 0.0f; identity.m[0][2] = 0.0f; identity.m[0][3] = 0.0f;
	identity.m[1][0] = 0.0f; identity.m[1][1] = f; identity.m[1][2] = 0.0f; identity.m[1][3] = 0.0f;
	identity.m[2][0] = 0.0f; identity.m[2][1] = 0.0f; identity.m[2][2] = c1; identity.m[2][3] = c2;
	identity.m[3][0] = 0.0f; identity.m[3][1] = 0.0f; identity.m[3][2] = -1.0f; identity.m[3][3] = 0.0f;
}

/******************************************************************
*
* PrintMatrix
*
*******************************************************************/

void PrintMatrix(Matrix4f matrix) {
	int row, columns;
	
	printf("\n---------------------------------------\n");
	for (row=0; row<4; row++) {
		for(columns=0; columns<4; columns++)
			printf("%f\t", matrix.m[row][columns]);
		printf("\n");
	}
	printf("---------------------------------------\n");
	
	fflush(stdout);
}

/******************************************************************
*
* CopyMatrix
*
*******************************************************************/

void CopyMatrix(Matrix4f src, Matrix4f &dst) {
	int i,j;
	
	for(i=0; i < 4; i++) {
		for(j=0; j <4; j++) {
			dst.m[i][j] = src.m[i][j];
		}
	}
}

