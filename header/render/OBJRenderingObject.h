#include "RenderingObject.h"
#include "../objparser/tiny_obj_loader.h"

#ifndef __OBJ_RENDERING_OBJECT_H__
#define __OBJ_RENDERING_OBJECT_H__
class OBJRenderingObject : public RenderingObject {
	private:
		std::vector<tinyobj::shape_t> shapes; // Structure for loading of OBJ data 
	public:
		void initVertices(const char* filename);
};
#endif // __OBJ_RENDERING_OBJECT_H__
 
