#include "Render.h"



Engine::CRender::CRender()
{
}


bool Engine::CRender::OpenGLInit(HWND& _hWnd, int width, int height, int colorDepth) throw (Engine::Error)
{
	if (!_hWnd)
		return false;
	hWnd = _hWnd;
	PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		colorDepth,
		0,0,0,0,0,0,
		0,
		0,
		0,
		0,0,0,0,
		24,
		8,
		0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};
	hDC = GetDC(hWnd);
	if (!hDC)
		throw Engine::DC_ERROR;
	int PixelFormat = ChoosePixelFormat(hDC, &pfd);
	if(PixelFormat == 0)
		throw Engine::NOT_FOUND_PF;
	if (!SetPixelFormat(hDC, PixelFormat, &pfd))
	{
		ReleaseDC(hWnd,hDC);
		throw Engine::PF_SET_ERROR;
	}
	hRC = wglCreateContext(hDC);
	if (!hRC)
	{

		ReleaseDC(hWnd, hDC);
		throw Engine::CONTEXT_C_ERROR;
	}
	if (!wglMakeCurrent(hDC, hRC))
	{
		wglDeleteContext(hRC);
		ReleaseDC(hWnd, hDC);
		throw Engine::CONTEXT_S_ERROR;
	}
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.f, 0.f, 1.f, 1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (!Init())
	{
		wglMakeCurrent(0, 0);
		wglDeleteContext(hRC);
		ReleaseDC(hWnd, hDC);
		return false;
	}
	return true;
}

Engine::CRender::~CRender()
{
}
