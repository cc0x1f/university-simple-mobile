#include "RenderingObject.h"
#include "../objparser/OBJParser.h"

#ifndef __OBJ_RENDERING_OBJECT_H__
#define __OBJ_RENDERING_OBJECT_H__
class OBJRenderingObject : public RenderingObject {
	private:
		glm::vec3 color; // not used atm
		obj_scene_data data; // Structure for loading of OBJ data 
	public:
		void initVertices(const char* filename, glm::vec3 color);
		void setColor(glm::vec3 color);
};
#endif // __OBJ_RENDERING_OBJECT_H__
 
