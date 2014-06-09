#include "RenderingObject.h"

#ifndef __LINE_RENDERING_OBJECT_H__
#define __LINE_RENDERING_OBJECT_H__
class LineRenderingObject : public RenderingObject {
	private:
		std::vector<Helper::vec2s> IBO_data;
	public:
		void initVertices();
		void initUniformAndBuffer(ShaderProgram *shaderProgram);
		void init(ShaderProgram *shaderProgram);
};
#endif // __GRID_RENDERING_OBJECT_H__
 
