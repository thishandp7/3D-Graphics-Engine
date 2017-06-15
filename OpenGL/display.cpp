#include "display.h"
#include <GL/glew.h>
#include <iostream>


using namespace std;

Display::Display(int width, int height, string title)
{
	//To say initalize everything! 
	SDL_Init(SDL_INIT_EVERYTHING);

	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);	//setting the amount of bits for the RED pixel
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);	//setting the amount of bits for the GREEN pixel
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);	//setting the amount of bits for the BLUE pixel
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);	//setting the amount of bits for the ALPHA pixel
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);	//setting the total size of a pixel
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);	//setting the total size for the zDepth
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);	//how many buffers needed
 
	//Set the window properties for the window we are creating(Name title of the window, PositionX, PositionY, width, height, flags)
	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	//To use the window for the GPU rather than from the OS
	m_glContext = SDL_GL_CreateContext(m_window);

	GLenum status = glewInit(); //To initialize all the OpenGL functions

	//To check the OpenGL initialization process is successful
	if (status != GLEW_OK)
	{
		cout << "GLEW failed to initalized!!" << endl;
	}

	m_isClosed = false;

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}
Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext);//1st delete the OpenGL context
	SDL_DestroyWindow(m_window);//2nd delete the Window
	SDL_Quit();	//To quit the window
}
void Display::Update()
{
	SDL_GL_SwapWindow(m_window);

	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			m_isClosed = true;
		}
	}
}
// To check the window is closed
bool Display::isClosed()
{
	return m_isClosed;
}
void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}