#include "RenderingObject.h"

#ifndef __GRID_RENDERING_OBJECT_H__
#define __GRID_RENDERING_OBJECT_H__
class GridRenderingObject : public RenderingObject {
	private:
		Vector2s *IBO_data;
	public:
		void initVertices(int linesx, int linesy, Vector3f color);
		void init(ShaderProgram *shaderProgramm);
};
#endif // __GRID_RENDERING_OBJECT_H__
 
