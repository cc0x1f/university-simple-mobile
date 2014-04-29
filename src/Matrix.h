/******************************************************************
*
* Matrix.h
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
#include "GlHelper.h"

#ifndef __MATRIX_H__
#define __MATRIX_H__

void CopyMatrix(Matrix4f src, Matrix4f &dst);
void SetIdentityMatrix(Matrix4f &result);
void UpdateScaleMatrix(Matrix4f old, Matrix4f newScale, Matrix4f &result);
void SetRotationX(float anglex, Matrix4f &result);
void SetRotationY(float angley, Matrix4f &result);
void SetRotationZ(float anglez, Matrix4f &result);
void SetScaleMatrix(float scale, Matrix4f &result);
void SetTranslation(float x, float y, float z, Matrix4f &result);
void MultiplyMatrix(Matrix4f m1, Matrix4f m2, Matrix4f &result);
void SetPerspectiveMatrix(float fov, float aspect, float nearPlane, float farPlane, Matrix4f &result);
void PrintMatrix(Matrix4f matrix);

#endif // __MATRIX_H__
