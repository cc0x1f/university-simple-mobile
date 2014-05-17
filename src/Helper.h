/* Standard includes */
#include <stdio.h>
#include <stdlib.h>

#define GLM_FORCE_RADIANS  /* Use radians in all GLM functions */
/* GLM includes - adjust path as required for local installation */
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" /* Provides glm::translate, glm::rotate, glm::scale, glm::perspective */
#include "glm/gtc/type_ptr.hpp"         /* Vector/matrix handling */

#ifndef __HELPER_H__
#define __HELPER_H__
class Helper {
	private:
		
		
	public:
		// A simple struct for a 2 point short vector
		struct vec2s {
			short x;
			short y;

			vec2s() {
			}

			vec2s(short fx, short fy) {
				x = fx;
				y = fy;
			}
		};
		// A simple struct for a 3 point short vector
		struct vec3s {
			short x;
			short y;
			short z;

			vec3s() {
			}

			vec3s(short fx, short fy, short fz) {
				x = fx;
				y = fy;
				z = fz;
			}
		};
		static void printMatrix(glm::mat4 matrix);
};
#endif // __HELPER_H__
 
