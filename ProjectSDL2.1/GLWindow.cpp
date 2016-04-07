#include "GLWindow.h"



GLWindow::GLWindow()
{
	InitWindow(1024, 768, "ProjectSDL2");
	this->m_LastX = 1024 / 2;
	this->m_LastY = 768 / 2;
	this->m_Camera = nullptr;
	this->m_LockCamera = false;
	this->m_LockMouse = false;
	this->m_IsClosed = false;
}

GLWindow::GLWindow(int width, int height, const std::string & title)
{
	InitWindow(width, height, title);
	this->m_LastX = width / 2;
	this->m_LastY = height / 2;
	this->m_Camera = nullptr;
	this->m_LockMouse = false;
	this->m_IsClosed = false;
}


GLWindow::~GLWindow()
{

	SDL_GL_DeleteContext(m_Context);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

void GLWindow::Clear(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWindow::Update(float deltaTime)
{
	SDL_GL_SwapWindow(m_Window);
}

void GLWindow::BindCamera(GLCamera* camera)
{
	this->m_Camera = camera;
}

void GLWindow::UnbindCamera()
{
	this->m_Camera = nullptr;
}

bool GLWindow::IsClosed()
{
	return this->m_IsClosed;
}

float GLWindow::GetAspect()
{
	return (float)this->m_Width/(float)this->m_Height;
}

int GLWindow::GetWidth()
{
	return this->m_Width;
}

int GLWindow::GetHeight()
{
	return this->m_Height;
}

SDL_Window * GLWindow::GetWindow()
{
	return this->m_Window;
}

void GLWindow::InitWindow(int width, int height, const std::string & title)
{
	this->m_Width = width;
	this->m_Height = height;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

	this->m_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	this->m_Context = SDL_GL_CreateContext(m_Window);

	glEnable(GL_DEPTH_TEST);

	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
		OutputDebugStringA("Glew failed to init");
	}
	this->m_IsClosed = false;
}
