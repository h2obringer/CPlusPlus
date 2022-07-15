#include <SDL2/SDL.h>
#include <GL/glew.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include <iostream>
using namespace std;




int main(){
	Display display(800,600, "Hello World!");

	Vertex vertices[] = {Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(0,0)),
						Vertex(glm::vec3(0,0.5,0), glm::vec2(0,0)),
						Vertex(glm::vec3(0.5,-0.5,0), glm::vec2(0,0))};
	Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0])); //# of elements in the array
	Shader shader("./res/shaders/basicShader");
	//Texture texture("./res/textures/test.jpg");

	while(!display.IsClosed()){
		glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.Bind();
		//texture.Bind(0);
		mesh.Draw();
		display.Update();
	}
	return 0;
}
