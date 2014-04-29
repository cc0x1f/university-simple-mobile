#include "RenderingObject.h"
#include "../objparser/OBJParser.h"

#ifndef __OBJ_RENDERING_OBJECT_H__
#define __OBJ_RENDERING_OBJECT_H__
class OBJRenderingObject : public RenderingObject {
	private:
		Vector3f color; // not used atm
		obj_scene_data data; // Structure for loading of OBJ data 
	public:
		void initVertices(const char* filename, Vector3f color);
		void setColor(Vector3f color);
};
#endif // __OBJ_RENDERING_OBJECT_H__
 
