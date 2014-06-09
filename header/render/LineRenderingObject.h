#include "RenderingObject.h"

#ifndef __LINE_RENDERING_OBJECT_H__
#define __LINE_RENDERING_OBJECT_H__
class LineRenderingObject : public RenderingObject {
	public:
		void initVertices();
		void init(ShaderProgram *shaderProgram);
};
#endif // __GRID_RENDERING_OBJECT_H__
 
