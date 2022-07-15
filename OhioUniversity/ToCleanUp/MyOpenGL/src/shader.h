#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

class Shader{
	public:
		Shader(const std::string& filename);
		void Bind();
		virtual ~Shader();
	protected:
	private:
		static const unsigned int NUM_SHADERS = 2; //set to 3 if using geometry shaders
		//Shader(const Shader& other);
		//Shader& operator=(const Shader& other);
		GLuint m_program; //handler to the shader program
		GLuint m_shaders[NUM_SHADERS];
};



#endif /* SHADER_H_ */
