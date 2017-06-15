#ifndef DISPLAY_H
#define DISPLAY_H
#include <string>
#include <SDL2/SDL.h>


using namespace std;

class Display
{
private:

	SDL_Window* m_window;	//allocating memeory for a window
	SDL_GLContext m_glContext;	//Creating an OpenGL context(OpenGL window)
	bool m_isClosed;
public:
	//Constructor
	Display(int width, int height, string title);
	//Destructor
	virtual ~Display();
	//To swap the buffers form the OpenGL to window and vice versa
	void Update();
	//To clear everything in the window
	void Clear(float r, float g, float b, float a);
	bool isClosed();

};
#endif
