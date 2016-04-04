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
	SDL_PumpEvents();
	SDL_Event e;

	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	//continuous-response keys
	if (keyState[SDL_SCANCODE_W])
	{
		this->m_Camera->ProcessKeyboard(GLCamera::FORWARD, deltaTime);
	}
	if (keyState[SDL_SCANCODE_A])
	{
		this->m_Camera->ProcessKeyboard(GLCamera::LEFT, deltaTime);
	}
	if (keyState[SDL_SCANCODE_S])
	{
		this->m_Camera->ProcessKeyboard(GLCamera::BACK, deltaTime);
	}
	if (keyState[SDL_SCANCODE_D])
	{
		this->m_Camera->ProcessKeyboard(GLCamera::RIGHT, deltaTime);
	}
	if (keyState[SDL_SCANCODE_SPACE])
	{
		this->m_Camera->ProcessKeyboard(GLCamera::UP, deltaTime);
	}
	if (keyState[SDL_SCANCODE_LCTRL])
	{
		this->m_Camera->ProcessKeyboard(GLCamera::DOWN, deltaTime);
	}

	//single-hit keys, mouse, and other general SDL events (eg. windowing)
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			m_IsClosed = true;
		}
		else if (e.type == SDL_KEYDOWN)
		{
			
			switch (e.key.keysym.scancode)
			{
			case SDL_SCANCODE_T:
				if (m_LockMouse)
				{
					m_LockMouse = false;
					SDL_SetWindowGrab(this->m_Window, SDL_FALSE);
					SDL_ShowCursor(1);
				}
				else
				{
					m_HasWarped = true;
					SDL_WarpMouseInWindow(this->m_Window, this->m_Width / 2, this->m_Height / 2);
					m_LockMouse = true;
					SDL_SetWindowGrab(this->m_Window, SDL_TRUE);
					SDL_ShowCursor(0);
				}
				break;
			case SDL_SCANCODE_R:
				m_LockCamera = !m_LockCamera;
				break;
			case SDL_SCANCODE_ESCAPE:
				this->m_IsClosed = true;
				break;
			default:
				break;
			}
		}
		else if (e.type == SDL_MOUSEMOTION)
		{
			if (m_LockMouse && !m_HasWarped)
			{
				float xOffset = e.motion.x - m_LastX;
				float yOffset = e.motion.y - m_LastY;

				this->m_Camera->ProcessMouse(xOffset, yOffset, deltaTime);
				SDL_WarpMouseInWindow(this->m_Window, this->m_Width / 2, this->m_Height / 2);
				m_HasWarped = true;
			}
			if (m_HasWarped)
			{
				m_HasWarped = false;
			}
		}
		else if (e.type == SDL_MOUSEWHEEL)
		{
			this->m_Camera->ProcessScrollWheel(e.wheel.y, deltaTime);
		}
	}
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
