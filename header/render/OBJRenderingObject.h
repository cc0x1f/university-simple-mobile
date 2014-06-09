#include "RenderingObject.h"
#include "../objparser/OBJParser.h"

#ifndef __OBJ_RENDERING_OBJECT_H__
#define __OBJ_RENDERING_OBJECT_H__
class OBJRenderingObject : public RenderingObject {
	private:
		obj_scene_data data; // Structure for loading of OBJ data 
	public:
		void initVertices(const char* filename);
};
#endif // __OBJ_RENDERING_OBJECT_H__
 
