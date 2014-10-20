#ifndef __TEXTURE_H__
#define __TEXTURE_H__

/* Structure containing texture RGB array and dimensions  */
typedef struct {
	unsigned char *data;
	unsigned int width, height;
} TextureDataPtr;

class Texture {
	public:
		static int load(const char* filename, TextureDataPtr *data); // Load BMP file specified by filename
};

#endif // __TEXTURE_H__