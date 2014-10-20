#include "RenderingObject.h"
#include "../Camera.h"

#ifndef __BILLBOARD_RENDERING_OBJECT_H__
#define __BILLBOARD_RENDERING_OBJECT_H__
class BillboardRenderingObject : public RenderingObject {
	private:
		int animationStep;
		int lastTimestamp;
		int animationTime;
		Camera *cam;
		
		void update(void);
	public:
		void initVertices(void);
		void setCam(Camera *cam);
		void render(void);
};
#endif // __BILLBOARD_RENDERING_OBJECT_H__
 
