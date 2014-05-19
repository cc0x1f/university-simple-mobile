/* OpenGL includes */
#include <GL/glew.h>
#include <GL/freeglut.h>

#ifndef __SHADER_PROGRAM_H__
#define __SHADER_PROGRAM_H__

// Mapping for our vertex attributes in the shader files
// this is the hardcoded variant.
// TODO: move to glGetAttribLocation
enum ShaderMapping {S_POSITION = 0, S_COLOR = 1, S_NORMALS = 2};

class ShaderProgram {
	private:
		GLuint shaderProgram;
		const char* VertexShaderString;
		const char* FragmentShaderString;
		const char* VertexShaderFilename;
		const char* FragmentShaderFilename;
		
		const char* LoadShader(const char* filename);
		void AddShader(const char* ShaderCode, GLenum ShaderType);
	public:
		void setVertexShader(const char* filename);
		void setFragmentShader(const char* filename);
		GLuint getUniformLocation(const char* varname);
		void create(void);
		void remove(void);
};
#endif // __SHADER_PROGRAM_H__
