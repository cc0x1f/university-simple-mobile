#ifndef __GL_HELPER_H__
#define __GL_HELPER_H__

// A simple struct for a 2 point float vector
struct Vector2f {
	float x;
	float y;
	
	Vector2f() {
	}

	Vector2f(float fx, float fy) {
		x = fx;
		y = fy;
	}
};

// A simple struct for a 2 point float vector
struct Vector2s {
	short x;
	short y;
	
	Vector2s() {
	}

	Vector2s(short fx, short fy) {
		x = fx;
		y = fy;
	}
};

// A simple struct for a 3 point float vector
struct Vector3f {
	float x;
	float y;
	float z;
	
	Vector3f() {
	}

	Vector3f(float fx, float fy, float fz) {
		x = fx;
		y = fy;
		z = fz;
	}
};

// A simple struct for a 3 point short vector
struct Vector3s {
	short x;
	short y;
	short z;
	
	Vector3s() {
	}

	Vector3s(short fx, short fy, short fz) {
		x = fx;
		y = fy;
		z = fz;
	}
};

// A simple 4 by 4 float matrix
struct Matrix4f {
	float m[4][4];
};

#endif // __GL_HELPER_H__
 
