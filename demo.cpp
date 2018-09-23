#define HAVE_OPENGL
#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "SDL2/SDL_opengl.h"


SDL_Window*	g_window;
int16_t		g_window_width;
int16_t		g_window_height;
/**** 
 *   INIT FUNCTIONS  *
                  ****/

SDL_Window* init_SDL(const char* window_name, int16_t width, int16_t height)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL caput!\nmsg:%s\n", 
				SDL_GetError());
		return NULL;
	}
	
	SDL_Window* window = SDL_CreateWindow(window_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if(!window)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL window boing!\n"
				"msg:%s\n", SDL_GetError());
		SDL_Quit();
		return NULL;
	}
	
	return window;
}

int configure_OpenGL(int16_t width, int16_t height)
{
	GLdouble aspect;

	glViewport(0, 0, width, height);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShaderModel(GL_SMOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspect = (GLdouble)width/ height;
	glOrtho(-1.0, 1.0, -1.0/aspect, 1.0/aspect, -1.0, 1.0);
	
	glMatrixMode(GL_MODELVIEW);
}

int init_OpenGL(SDL_Window* window, int16_t width, int16_t height)
{
	if(!SDL_GL_CreateContext(window))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "OpenGL context"
				" kaboom!\nmsg:%s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}
	
	SDL_GL_SetSwapInterval(1);
	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GLEW boom!!!\n");
		return -1;
	}
	
	configure_OpenGL(width, height);

	return 0;
}

int init_audio_input()
{
}

int main()
{
	return 0;
}
