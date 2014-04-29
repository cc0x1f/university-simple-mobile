#include "RenderingObject.h"

#ifndef __LINE_RENDERING_OBJECT_H__
#define __LINE_RENDERING_OBJECT_H__
class LineRenderingObject : public RenderingObject {
	private:
		Vector2s *IBO_data;
	public:
		void initVertices(Vector3f color);
		void init(ShaderProgram *shaderProgramm);
};
#endif // __GRID_RENDERING_OBJECT_H__
 
