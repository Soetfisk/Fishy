#pragma once
#include "GLUtil.h"
class GLWindow
{
public:
	GLWindow();
	GLWindow(int width, int height, const std::string& title);
	
	~GLWindow();

	void Clear(float r, float g, float b);
	void Update();

	bool IsClosed();
	float GetAspect();
	int GetWidth();
	int GetHeight();
	SDL_Window* GetWindow();
private:

	int WIDTH = 800;
	int HEIGHT = 480;

	int m_Width;
	int m_Height;
	SDL_Window* m_Window;
	SDL_GLContext m_Context;
	bool m_IsClosed;
	bool m_HasWarped;
	float m_LastX, m_LastY;

	void InitWindow(int width, int height, const std::string& title);
};

